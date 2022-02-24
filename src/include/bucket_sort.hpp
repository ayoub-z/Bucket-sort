#include <vector>
#include <string>
#include <array>

using std::vector, std::string;

class Bucket_sort{
	private:
		vector<float> bucket[10];
		vector<float> array;
		vector<float> negative_array;
		int size;

	public:
		Bucket_sort(vector<float> array, int n);
		void distribution_pass(int digit_pos, string number);
		void sort();
		int get_digits(int number);
		void gathering_pass(string number);
		void to_string();
};