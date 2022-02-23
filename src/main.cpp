#include "include/bucket_sort.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <chrono>
#include <ctime>

using std::cout, std::endl;
using namespace std::chrono;

int main(){

	int tests = 6;
	int n = 1000;
	for (int test = 1; test < tests +1; test++){
		cout << "Test: " << test << endl;
		cout << "Vector size: " << n << endl;

		auto start = high_resolution_clock::now();

		std::srand(unsigned(std::time(nullptr)));
		std::vector<int> arr(n);
		std::generate(arr.begin(), arr.end(), std::rand);

		Bucket_sort b1(arr, arr.size());
		b1.sort();

		auto stop = high_resolution_clock::now();
		microseconds duration = duration_cast<microseconds>(stop - start);

		cout << "Total runtime: " << duration.count() << " microseconds\n" << endl;

		n *= 2;
		arr.clear();
		}
}


