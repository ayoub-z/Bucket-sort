#include "include/bucket_sort.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

using std::cout, std::endl;

Bucket_sort::Bucket_sort(vector<float> array, int n){
	vector<float> bucket[10]; // start with a fixed (10) amount of buckets. This fixes a bug that made the code crash.
    this -> array = array;
	this -> negative_array = {};
	this-> size = n;
}

int Bucket_sort::get_digits(int number){ // returns number of digits inside integer
	int digits = 0; do { number /= 10; digits++; } while (number != 0);
	return digits;
}

void Bucket_sort::distribution_pass(int digit_amount, bool number_type, vector<float> current_array){
	int digit_pos = std::pow(10, (digit_amount)); // input digit_amount to the power of 10.
	int array_index = 0;
	int array_size = current_array.size();

    for (int i = 0; i < array_size; i++) {
        float n = current_array[array_index]; // current number
        if (!number_type) { // if negative number
            n = negative_array[array_index] * -1; // convert it to positive number
        }
        int index = int(n / digit_pos * 10) % 10;
        
        if (get_digits(n) >= digit_amount){ 
            bucket[index].push_back(current_array[array_index]);

            if (!number_type){
                negative_array.erase(negative_array.begin() + array_index);
            }
            else{
                array.erase(array.begin() + array_index);
            }
        }
        else{
            array_index++;
        }
    }
}

void Bucket_sort::gathering_pass(bool number_type){ // empty out the buckets to respective array in numeric order
	vector<float> temp_array = {};
	
	for (int i = 0; i < 10; i++){ // for every bucket
		for (int j = 0; j < bucket[i].size(); j++){ // for every number in bucket
			temp_array.push_back(bucket[i][j]);
		}
		bucket[i].clear(); // clear bucket when done with it
	}
	
	// Concat temporary array with the numbers' main array
	if (!number_type){
		negative_array.insert(negative_array.end(), temp_array.begin(), temp_array.end());
	}
	else {
		array.insert(array.end(), temp_array.begin(), temp_array.end());	
	}
    temp_array.clear();
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
		float max_negative_digit = get_digits(*std::min_element(std::begin(negative_array), std::end(negative_array)));
		// float max_negative_digit = get_digits(max_digits_negative);
		for (int i = 0; i < (max_negative_digit + 1); i++){
			distribution_pass(i, 0, negative_array);
			gathering_pass(0);
		}
        
	}
	float max_digit = get_digits(int(*std::max_element(std::begin(array), std::end(array))));

	for (int i = 0; i < (max_digit + 1); i++){ // sort positive numbers
		distribution_pass(i, 1, array);
		gathering_pass(1);
	}
	// first we reverse the list with negative numbers, since we sorted it as if they were positive numbers
	std::reverse(negative_array.begin(),negative_array.end());
	// then we merge the lists
	array.insert(array.begin(), negative_array.begin(), negative_array.end()); 
}

void Bucket_sort::to_string(){ // A "to_string" to output the result
	for (float number: array){
		cout << number << " ";
	}
	cout << endl;
}