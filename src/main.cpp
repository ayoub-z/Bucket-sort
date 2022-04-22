#include "include/bucket_sort.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>

using std::cout, std::endl;
using namespace std::chrono;

int main(){
	int tests = 10;
	int n = 1000;
	for (int test = 1; test < tests +1; test++){

		auto start = high_resolution_clock::now();

		std::srand(unsigned(std::time(nullptr)));
		std::vector<float> arr(n);
		std::generate(arr.begin(), arr.end(), std::rand);

		cout << "Test: " << test << endl;
		cout << "Vector size: " << arr.size() << endl << endl;

		Bucket_sort b1(arr, arr.size());
		b1.sort();

		auto stop = high_resolution_clock::now();
		milliseconds duration = duration_cast<milliseconds>(stop - start);

		cout << "Total runtime: " << duration.count() << " milliseconds\n" << endl;
		arr.clear();
		n *= 2;
		}
}