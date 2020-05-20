#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <chrono>
#include <thread>
#include "LinkedList.h"
#include "BSTree.h"
#include "HashTable.h"

int* readCSV(std::string filename) {
	int* data = new int[40000];
	std::ifstream file (filename);
	if(!file.is_open()) {
		std::cout << "Could not open file " << filename << "." << std::endl;
		return NULL;
	}

	std::string raw; std::getline(file, raw, '\n');

	std::stringstream raw_stream (raw);
	int n=0;
	while(raw_stream.good()) {
		std::string token; std::getline(raw_stream,token,',');
		data[n] = std::stoi(token);
		n++;
	}
	file.close();
	return data;
}

using namespace std::chrono;
microseconds getTime() {
	microseconds ms = duration_cast<microseconds>(system_clock::now().time_since_epoch());
	return ms;
}

void test_LL(int* data, std::string test) {
	LinkedList L;

	float insert[400];
	float search[400];

	int lowerbound = 0; //inclusive
	int upperbound = 100; //exclusive 100
	//run test in hundreds 400 times (multiplies to 40000)
	for(int n=0; n<400; n++) { // n<400
		//insertion test
		float avg_insert = 0;
		for(int i=lowerbound; i<upperbound; i++) {
			microseconds start = getTime();
			L.insert(data[i]);
			microseconds end = getTime();
			microseconds runtime = end-start;
			avg_insert += (runtime.count());
		}
		avg_insert /= 100;
		std::cout << "Avg insert, " << lowerbound << " to " << upperbound << ": " << avg_insert << std::endl;
		insert[n] = avg_insert;

		//search test
		float avg_search = 0;
		for(int i=lowerbound; i<upperbound; i++) {
			int num = rand()%upperbound;
			microseconds start = getTime();
			L.search(data[num]);
			microseconds end = getTime();
			microseconds runtime = end-start;
			avg_search += (runtime.count());
		}
		avg_search /= 100;
		std::cout << "Avg search, 0 to " << upperbound << ": " << avg_search << std::endl;
		search[n] = avg_search;

		//increment lower and upper bounds
		lowerbound += 100;
		upperbound += 100;
	}

	//put data in file
	std::ofstream output ("LLPerformance_" + test + ".csv", std::ofstream::trunc);
	if(!output.good()) {
		std::cout << "Could not open LL output file." << std::endl;
		return;
	}
	output << "entries (x100)";
	for(int n=0; n<400; n++) {
		output << ',' << n;
	}
	output << '\n' << "insertion times";
	for(int n=0; n<400; n++) {
		output << ',' << insert[n];
	}
	output << '\n' << "search times";
	for(int n=0; n<400; n++) {
		output << ',' << search[n];
	}
	output.close();
	std::cout << "Data sent to LLPerformance_" + test + ".csv" << std::endl;
}

void test_BST(int* data, std::string test) {
	BSTree B;

	float insert[400];
	float search[400];

	int lowerbound = 0; //inclusive
	int upperbound = 100; //exclusive 100
	//run test in hundreds 400 times (multiplies to 40000)
	for(int n=0; n<400; n++) { // n<400
		//insertion test
		float avg_insert = 0;
		for(int i=lowerbound; i<upperbound; i++) {
			microseconds start = getTime();
			B.insert(data[i]);
			microseconds end = getTime();
			microseconds runtime = end-start;
			avg_insert += (runtime.count());
		}
		avg_insert /= 100;
		std::cout << "Avg insert, " << lowerbound << " to " << upperbound << ": " << avg_insert << std::endl;
		insert[n] = avg_insert;

		//search test
		float avg_search = 0;
		for(int i=lowerbound; i<upperbound; i++) {
			int num = rand()%upperbound;
			microseconds start = getTime();
			B.search(data[num]);
			microseconds end = getTime();
			microseconds runtime = end-start;
			avg_search += (runtime.count());
		}
		avg_search /= 100;
		std::cout << "Avg search, 0 to " << upperbound << ": " << avg_search << std::endl;
		search[n] = avg_search;

		//increment lower and upper bounds
		lowerbound += 100;
		upperbound += 100;
	}

	//put data in file
	std::ofstream output ("BSTPerformance_" + test + ".csv", std::ofstream::trunc);
	if(!output.good()) {
		std::cout << "Could not open BST output file." << std::endl;
		return;
	}
	output << "entries (x100)";
	for(int n=0; n<400; n++) {
		output << ',' << n;
	}
	output << '\n' << "insertion times";
	for(int n=0; n<400; n++) {
		output << ',' << insert[n];
	}
	output << '\n' << "search times";
	for(int n=0; n<400; n++) {
		output << ',' << search[n];
	}
	output.close();
	std::cout << "Data sent to BSTPerformance_" + test + ".csv" << std::endl;
}

void test_HT_chain(int* data, std::string test) {
	HashTable H;

	float insert[400];
	float search[400];

	int lowerbound = 0; //inclusive
	int upperbound = 100; //exclusive 100
	//run test in hundreds 400 times (multiplies to 40000)
	for(int n=0; n<400; n++) { // n<400
		//insertion test
		float avg_insert = 0;
		for(int i=lowerbound; i<upperbound; i++) {
			microseconds start = getTime();
			H.insert(data[i], "chain");
			microseconds end = getTime();
			microseconds runtime = end-start;
			avg_insert += (runtime.count());
		}
		avg_insert /= 100;
		std::cout << "Avg insert, " << lowerbound << " to " << upperbound << ": " << avg_insert << std::endl;
		insert[n] = avg_insert;

		//search test
		float avg_search = 0;
		for(int i=lowerbound; i<upperbound; i++) {
			int num = rand()%upperbound;
			microseconds start = getTime();
			H.search(data[num], "chain");
			microseconds end = getTime();
			microseconds runtime = end-start;
			avg_search += (runtime.count());
		}
		avg_search /= 100;
		std::cout << "Avg search, 0 to " << upperbound << ": " << avg_search << std::endl;
		search[n] = avg_search;

		//increment lower and upper bounds
		lowerbound += 100;
		upperbound += 100;
	}

	//put data in file
	std::ofstream output ("HashPerformance_" + test + ".csv", std::ofstream::trunc);
	if(!output.good()) {
		std::cout << "Could not open HT output file." << std::endl;
		return;
	}
	output << "entries (x100)";
	for(int n=0; n<400; n++) {
		output << ',' << n;
	}
	output << '\n' << "insertion times";
	for(int n=0; n<400; n++) {
		output << ',' << insert[n];
	}
	output << '\n' << "search times";
	for(int n=0; n<400; n++) {
		output << ',' << search[n];
	}
	output.close();
	std::cout << "Data sent to HashPerformance_" + test + ".csv" << std::endl;
}

void test_HT_linear(int* data, std::string test) {
	HashTable H;

	float insert[400];
	float search[400];

	int lowerbound = 0; //inclusive
	int upperbound = 100; //exclusive 100
	//run test in hundreds 400 times (multiplies to 40000)
	for(int n=0; n<400; n++) { // n<400
		//insertion test
		float avg_insert = 0;
		for(int i=lowerbound; i<upperbound; i++) {
			microseconds start = getTime();
			H.insert(data[i], "linear");
			microseconds end = getTime();
			microseconds runtime = end-start;
			avg_insert += (runtime.count());
		}
		avg_insert /= 100;
		std::cout << "Avg insert, " << lowerbound << " to " << upperbound << ": " << avg_insert << std::endl;
		insert[n] = avg_insert;

		//search test
		float avg_search = 0;
		for(int i=lowerbound; i<upperbound; i++) {
			int num = rand()%upperbound;
			microseconds start = getTime();
			H.search(data[num], "linear");
			microseconds end = getTime();
			microseconds runtime = end-start;
			avg_search += (runtime.count());
		}
		avg_search /= 100;
		std::cout << "Avg search, 0 to " << upperbound << ": " << avg_search << std::endl;
		search[n] = avg_search;

		//increment lower and upper bounds
		lowerbound += 100;
		upperbound += 100;
	}

	//put data in file
	std::ofstream output ("HashPerformance_" + test + ".csv", std::ofstream::trunc);
	if(!output.good()) {
		std::cout << "Could not open HT output file." << std::endl;
		return;
	}
	output << "entries (x100)";
	for(int n=0; n<400; n++) {
		output << ',' << n;
	}
	output << '\n' << "insertion times";
	for(int n=0; n<400; n++) {
		output << ',' << insert[n];
	}
	output << '\n' << "search times";
	for(int n=0; n<400; n++) {
		output << ',' << search[n];
	}
	output.close();
	std::cout << "Data sent to HashPerformance_" + test + ".csv" << std::endl;
}

void test_HT_quadratic(int* data, std::string test) {
	HashTable H;

	float insert[400];
	float search[400];

	int lowerbound = 0; //inclusive
	int upperbound = 100; //exclusive 100
	//run test in hundreds 400 times (multiplies to 40000)
	for(int n=0; n<400; n++) { // n<400
		//insertion test
		float avg_insert = 0;
		for(int i=lowerbound; i<upperbound; i++) {
			microseconds start = getTime();
			H.insert(data[i], "quadratic");
			microseconds end = getTime();
			microseconds runtime = end-start;
			avg_insert += (runtime.count());
		}
		avg_insert /= 100;
		std::cout << "Avg insert, " << lowerbound << " to " << upperbound << ": " << avg_insert << std::endl;
		insert[n] = avg_insert;

		//search test
		float avg_search = 0;
		for(int i=lowerbound; i<upperbound; i++) {
			int num = rand()%upperbound;
			microseconds start = getTime();
			H.search(data[num], "quadratic");
			microseconds end = getTime();
			microseconds runtime = end-start;
			avg_search += (runtime.count());
		}
		avg_search /= 100;
		std::cout << "Avg search, 0 to " << upperbound << ": " << avg_search << std::endl;
		search[n] = avg_search;

		//increment lower and upper bounds
		lowerbound += 100;
		upperbound += 100;
	}

	//put data in file
	std::ofstream output ("HashPerformance_" + test + ".csv", std::ofstream::trunc);
	if(!output.good()) {
		std::cout << "Could not open HT output file." << std::endl;
		return;
	}
	output << "entries (x100)";
	for(int n=0; n<400; n++) {
		output << ',' << n;
	}
	output << '\n' << "insertion times";
	for(int n=0; n<400; n++) {
		output << ',' << insert[n];
	}
	output << '\n' << "search times";
	for(int n=0; n<400; n++) {
		output << ',' << search[n];
	}
	output.close();
	std::cout << "Data sent to HashPerformance_" + test + ".csv" << std::endl;
}

int main() {

	int* data_A = readCSV("dataSetA.csv");
	int* data_B = readCSV("dataSetB.csv");
	test_HT_chain(data_A, "Chain_A");
	test_HT_chain(data_B, "Chain_B");
	test_HT_linear(data_A, "Linear_A");
	test_HT_linear(data_B, "Linear_B");
	test_HT_quadratic(data_A, "Quad_A");
	test_HT_quadratic(data_B, "Quad_B");

}
