#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <random>
#include <iomanip>
#include <fstream>

using namespace std;

// Function to generate a random 16-bit unsigned integer
unsigned short RandomNum(int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<unsigned short> dis(0, size); // Range for 16-bit unsigned integer (0 to 2^16 - 1)
    return dis(gen);
}

int main() {
	std::ofstream f("output.txt");

    if (!f.is_open()) {
    	cout << "Cannot open the file." << endl;
    	return 0;
    }
    
    f << "#CLA16 Testcases#" << endl;
    for (int i = 0; i < 80; i++) {
		unsigned short A = RandomNum(65535);
    	unsigned short B = RandomNum(65535);
    	unsigned short Cin = RandomNum(1);
    	unsigned short Sum = A + B + Cin;
    	int Cout = (A + B + Cin > Sum) ? 1 : 0;
    
    	f << uppercase << hex << setw(4) << setfill('0') << A << " ";
    	f << uppercase << hex << setw(4) << setfill('0') << B << " ";
    	f << Cin << " ";
    	f << uppercase << hex << setw(4) << setfill('0') << Sum << " ";
    	f << Cout << endl;
	}
	f << endl;
    
    f << "#CLA4 Testcases#" << endl;
    for (int i = 0; i < 80; i++) {
		unsigned short A = RandomNum(15);
    	unsigned short B = RandomNum(15);
    	unsigned short Cin = RandomNum(1);
    	unsigned short Sum = (A + B + Cin) % 16;
    	
    	unsigned short P[4];
		unsigned short G[4];
    	for (int i = 0; i < 4; ++i) {
        	P[i] = ((A | B) >> i) & 1;
        	G[i] = ((A & B) >> i) & 1;
    	}
    	f << uppercase << hex << setw(1) << setfill('0') << A << " ";
    	f << uppercase << hex << setw(1) << setfill('0') << B << " ";
    	f << Cin << " ";
    	f << uppercase << hex << setw(1) << setfill('0') << Sum << " ";
    	f << (P[3] & P[2] & P[1] & P[0]) << " ";
    	f << (G[3] | (P[3] & G[2]) | (P[3] & P[2] & G[1]) | (P[3] & P[2] & P[1] & G[0])) << endl;	
	}
	f << endl;
	
	f << "#LessThan Testcases#" << endl;
	for (int i = 0; i < 80; i++) {
		unsigned short A = RandomNum(65535);
    	unsigned short B = RandomNum(65535);
    	int LT = (A >= B);
    
    	f << uppercase << hex << setw(4) << setfill('0') << A << " ";
    	f << uppercase << hex << setw(4) << setfill('0') << B << " ";
    	f << LT << endl;
	}
	f << endl;
	
	f << "#Mux Testcases#" << endl;
	for (int i = 0; i < 80; i++) {
		unsigned short A = RandomNum(65535);
    	unsigned short B = RandomNum(65535);
    	unsigned short S = RandomNum(1);
    	unsigned short Out = S ? B : A;
    
    	f << uppercase << hex << setw(4) << setfill('0') << A << " ";
    	f << uppercase << hex << setw(4) << setfill('0') << B << " ";
    	f << S << " ";
    	f << uppercase << hex << setw(4) << setfill('0') << Out << " " << endl;
	}
	f << endl;
	
	f << "#Duty Cycle Testcases#" << endl;
	unsigned int clk_period = 1; 
	unsigned int freq = 15;
	for (int i = 0; i < freq / 5; i++) {
		unsigned short A = freq;
		unsigned short B = i * 5;
		unsigned short Out = 1;
		
		//f << "chk_window 0 " << int(B * 400) << " 1 period=" << int(period * A) << " first=5.3" << endl;
		f << dec << double(2.5 + clk_period * A * i) << " "; 
		f << uppercase << hex << setw(4) << setfill('0') << A << " ";
    	f << uppercase << hex << setw(4) << setfill('0') << B << " ";
    	f << "1" << endl;
	}
	f << endl;
	
	f << "#Freq Testcases#" << endl;
	double current_t = 2.5; 
	for (int i = 0; i < 20; i++) {
		unsigned short A = 200 + 50 * i;
		unsigned short B = A * 0.32;
		unsigned short Out = 1;
		
		//f << "chk_window 0 " << int(B * 400) << " 1 period=" << int(period * A) << " first=5.3" << endl;
		f << dec << double(current_t) << " "; 
		f << uppercase << hex << setw(4) << setfill('0') << A << " ";
    	f << uppercase << hex << setw(4) << setfill('0') << B << " ";
    	f << "1" << endl;
    	
    	current_t += clk_period * A;
	}
	
    f.close();
}
