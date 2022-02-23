#include "include/bucket_sort.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using std::cout, std::endl;

Bucket_sort::Bucket_sort(vector<int> array, int n){
	vector<int> bucket[n];
	this -> array = array;
	this-> size = n;
}

int Bucket_sort::get_digits(int number){ // returns number of digits inside integer
	int digits = 0; do { number /= 10; digits++; } while (number != 0);
	return digits;
}

void Bucket_sort::distribution_pass(int digit_pos){
	int digit_position = std::pow(10, (digit_pos)); // input digit_pos to the power of 10.
	
	int array_index = 0;
	for (int i=0; i<size; i++) {
		int index = (array[array_index]/digit_position * 10) % digit_pos;
		
		// if digits of number is same as digit amount we're working with  
		if (get_digits(array[array_index]) == digit_pos){ 
			bucket[index].push_back(array[array_index]);
			array.erase(array.begin() + array_index);
		}
		else{
			array_index++;
		}
	}
}

void Bucket_sort::gathering_pass(int digit_pos){ // sort buckets and empty out buckets to array
	int max_digits = *std::max_element(std::begin(array), std::end(array));

	for (int i = 0; i < 10; i++){ // for every bucket
		std::sort(bucket[i].begin(), bucket[i].end());
		for (int j = 0; j < bucket[i].size(); j++){ // for every number in bucket
			array.push_back(bucket[i][j]);
		}
		bucket[i].clear(); // clear bucket when done with it
	}
}

// fill buckets with each number position, sort them, then insert them to array.
// (so 1-9 first, then 10-99, etc.)
void Bucket_sort::sort(){ 
	int max_digits = *std::max_element(std::begin(array), std::end(array));
	int max_digit = get_digits(max_digits);

	for (int i = 1; i < (max_digit + 1); i++){
		distribution_pass(i);
		gathering_pass(i);
	}    
}

void Bucket_sort::to_string(){
	for (int number: array){
		cout << number << " ";
	}
	cout << endl;
}