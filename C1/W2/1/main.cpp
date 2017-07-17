#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

long long merge_sort_and_count_inv(vector<int> &numbers, int start, int end) {
    if (end - start == 0) return 0;
    int a_start = start, a_end = start + (end - start) / 2;
    int b_start = a_end + 1, b_end = end;
    long long inv_a = merge_sort_and_count_inv(numbers, a_start, a_end);
    long long inv_b = merge_sort_and_count_inv(numbers, b_start, b_end);

    long long inv_merge = 0;
    vector<int> result;
    int a_i = a_start, b_i = b_start;

    while (a_i <= a_end && b_i <= b_end) {
        if (numbers.at(b_i) < numbers.at(a_i)) {
            result.push_back(numbers.at(b_i));
            ++b_i;
            // cout << 'm';
            inv_merge += a_end - a_i + 1;
        } else {
            result.push_back(numbers.at(a_i));
            ++a_i;
        }
    }

    while (a_i <= a_end) {
        result.push_back(numbers.at(a_i));
        ++a_i;
    }

    while (b_i <= b_end) {
        result.push_back(numbers.at(b_i));
        ++b_i;
    }

    for (int i = start; i <= end; ++i) {
        numbers.at(i) = result.at(i - start);
    }

    // cout << "start: " << start << "end: " << end << "a: " << inv_a << "b: " << inv_b << "m: " << inv_merge << endl;

    return inv_a + inv_b + inv_merge;
}

int main() {
    fstream fp;
    fp.open("IntegerArray.txt");
    vector<int> numbers;

    while (fp) {
        int n;
        fp >> n;
        if (numbers.size() == 0 || n != numbers.back()) numbers.push_back(n);
    }

    cout << merge_sort_and_count_inv(numbers, 0, numbers.size() - 1);
}
