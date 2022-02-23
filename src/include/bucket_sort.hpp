#include <vector>
#include <string>
#include <array>

using std::vector, std::string;

class Bucket_sort{
	private:
		vector<int> bucket[10];
		vector<int> array;
		int size;


	public:
		Bucket_sort(vector<int> array, int n);
		void distribution_pass(int digit_pos);
		void sort();
		int get_digits(int number);
		void gathering_pass(int digit_pos);
		void fill_array();
		void to_string();
};