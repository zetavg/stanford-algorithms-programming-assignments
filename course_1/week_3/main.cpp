#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int quick_sort_partition(vector<int> &numbers, int first, int last) {
    int i = first, j = first;

    while (j < last) {
        ++j;

        if (numbers.at(j) < numbers.at(first)) {
            ++i;
            if (i != j) swap(numbers.at(j), numbers.at(i));
        }
    }

    if (first != i) swap(numbers.at(first), numbers.at(i));

    return i;
}

int quick_sort_and_count_comparisons_1(vector<int> &numbers, int first, int last) {
    if (first >= last) return 0;

    int comparisons = last - first;

    int split_point = quick_sort_partition(numbers, first, last);

    comparisons += quick_sort_and_count_comparisons_1(numbers, first, split_point - 1);
    comparisons += quick_sort_and_count_comparisons_1(numbers, split_point + 1, last);

    return comparisons;
}

int quick_sort_and_count_comparisons_2(vector<int> &numbers, int first, int last) {
    if (first >= last) return 0;

    int comparisons = last - first;

    swap(numbers.at(first), numbers.at(last));

    int split_point = quick_sort_partition(numbers, first, last);

    comparisons += quick_sort_and_count_comparisons_2(numbers, first, split_point - 1);
    comparisons += quick_sort_and_count_comparisons_2(numbers, split_point + 1, last);

    return comparisons;
}

int quick_sort_and_count_comparisons_3(vector<int> &numbers, int first, int last) {
    if (first >= last) return 0;

    int comparisons = last - first;

    int middle = (last - first) / 2 + first;

    int median = first;

    if (
        numbers.at(middle) > numbers.at(first) &&
        numbers.at(last) > numbers.at(first)
    ) {
        if (numbers.at(middle) < numbers.at(last)) median = middle;
        else median = last;
    } else if (
        numbers.at(middle) < numbers.at(first) &&
        numbers.at(last) < numbers.at(first)
    ) {
        if (numbers.at(middle) > numbers.at(last)) median = middle;
        else median = last;
    }

    if (first != median) swap(numbers.at(first), numbers.at(median));

    int split_point = quick_sort_partition(numbers, first, last);

    comparisons += quick_sort_and_count_comparisons_3(numbers, first, split_point - 1);
    comparisons += quick_sort_and_count_comparisons_3(numbers, split_point + 1, last);

    return comparisons;
}

int main() {
    fstream fp;
    fp.open("QuickSort.txt");
    vector<int> numbers;

    while (fp) {
        int n;
        fp >> n;
        if (numbers.size() == 0 || n != numbers.back()) numbers.push_back(n);
    }

    vector<int> numbers_1 = numbers;
    cout << quick_sort_and_count_comparisons_1(numbers_1, 0, numbers.size() - 1) << endl;

    vector<int> numbers_2 = numbers;
    cout << quick_sort_and_count_comparisons_2(numbers_2, 0, numbers.size() - 1) << endl;

    vector<int> numbers_3 = numbers;
    cout << quick_sort_and_count_comparisons_3(numbers_3, 0, numbers.size() - 1) << endl;

    return 0;
}
