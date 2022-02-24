#include "include/bucket_sort.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using std::cout, std::endl;

Bucket_sort::Bucket_sort(vector<float> array, int n){
	vector<float> bucket[n];
	this -> array = array;
	this -> negative_array = {};	
	this-> size = n;
}

int Bucket_sort::get_digits(int number){ // returns number of digits inside integer
	int digits = 0; do { number /= 10; digits++; } while (number != 0);
	return digits;
}

void Bucket_sort::distribution_pass(int digit_pos, string number){
	int digit_position = std::pow(10, (digit_pos)); // input digit_pos to the power of 10.
	int array_index = 0;
	int length_array = array.size();
	int length_neg_array = negative_array.size();

	if (number == "negative"){ // if we're working with negative numbers
		for (int i=0; i<negative_array.size(); i++) {
			float n = negative_array[array_index] * -1; // convert it to positive number
			int index = int(n / digit_position * 10) % digit_pos; // index becomes nth digit. so digit 3 for 124.5 = 1
			if (get_digits(n) == digit_pos){ 
				bucket[index].push_back(n);
				negative_array.erase(negative_array.begin() + array_index);
			}	
			else{ // if we didn't find what we wanted, increment index and look at next number
				array_index++;
			}				
		}
	}
	else{ // if positive numbers
		for (int i=0; i<length_array; i++) {
			int index = int(array[array_index] / digit_position * 10) % 10;
			
			if (get_digits(int(array[array_index])) >= digit_pos){ 
				bucket[index].push_back(array[array_index]);
				array.erase(array.begin() + array_index);
			}
			else{
				array_index++;
			}
		}
	}
}

void Bucket_sort::gathering_pass(string number){ // empty out the buckets to respective array in numeric order
	vector<float> temp_array = {};
	
	for (int i = 0; i < 10; i++){ // for every bucket
		for (int j = 0; j < bucket[i].size(); j++){ // for every number in bucket
			if (number == "negative"){
				temp_array.push_back(bucket[i][j] * -1);
			}
			else{
			temp_array.push_back(bucket[i][j]);
			}
		}
		bucket[i].clear(); // clear bucket when done with it
	}
	
	// Concat temporary array with the numbers' main array
	if (number == "negative"){
		negative_array.insert(negative_array.end(), temp_array.begin(), temp_array.end());
	}
	else if (number == "positive"){
		array.insert(array.end(), temp_array.begin(), temp_array.end());	
	}
}

// fill buckets with each number position, sort them, then insert them to array.
// So first the decimal numbers .0 - .9, then 1-9 etc.
void Bucket_sort::sort(){
	int min_digits = *std::min_element(std::begin(array), std::end(array));
	int index = 0;

	if (min_digits < 0){ // if there are negative numbers
		for (int i = 0; i < size; i++){
			if (array[index] < 0){
				negative_array.push_back(array[index]); // we migrate them to a separate array and sort them separately
				array.erase(array.begin() + index);
			}
			else{
				index++;
			}
		}
	}

	if (min_digits < 0){ // sort negative numbers first
		float max_digits_negative = *std::min_element(std::begin(negative_array), std::end(negative_array));
		float max_digit_negative = get_digits(max_digits_negative);

		for (int i = 0; i < (max_digit_negative + 1); i++){
			distribution_pass(i, "negative");
			gathering_pass("negative");
		}
	}

	float max_digits = *std::max_element(std::begin(array), std::end(array));
	float max_digit = get_digits(int(max_digits));

	for (int i = 0; i < (max_digit + 1); i++){ // sort positive numbers
		distribution_pass(i, "positive");
		gathering_pass("positive");
	}
	// First we reverse the list with negative numbers, since we sorted it as if they were positive numbers
	std::reverse(negative_array.begin(),negative_array.end()); 
	array.insert(array.begin(), negative_array.begin(), negative_array.end()); // merge the lists
}

void Bucket_sort::to_string(){ // to string to output the result
	for (float number: array){
		cout << number << " ";
	}

	cout << endl;
}