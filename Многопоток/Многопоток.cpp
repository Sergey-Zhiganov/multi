#include <iostream>
#include <vector>
#include <thread>

using namespace std;

class MergeSort {
public:
    void Sort(vector<int>& arr) {
        if (arr.size() <= 1) return;

        vector<int> left(arr.begin(), arr.begin() + arr.size() / 2);
        vector<int> right(arr.begin() + arr.size() / 2, arr.end());

        thread leftThread(&MergeSort::Sort, this, ref(left));
        thread rightThread(&MergeSort::Sort, this, ref(right));

        leftThread.join();
        rightThread.join();

        merge(arr, left, right);
    }

private:
    void merge(vector<int>& arr, const vector<int>& left, const vector<int>& right) {
        size_t i = 0, j = 0, k = 0;

        while (i < left.size() && j < right.size()) {
            if (left[i] < right[j]) {
                arr[k++] = left[i++];
            }
            else {
                arr[k++] = right[j++];
            }
        }

        while (i < left.size()) {
            arr[k++] = left[i++];
        }

        while (j < right.size()) {
            arr[k++] = right[j++];
        }
    }
};

int main() {
    setlocale(LC_ALL, "ru");

    vector<int> arr(10);

    cout << "Введите 10 чисел: ";
    for (int& num : arr) {
        cin >> num;
    }

    MergeSort mergeSort;

    thread sortThread([&mergeSort, &arr]() {
        mergeSort.Sort(arr);
        });

    sortThread.join();

    cout << "Сортированный массив: ";
    for (const int& num : arr) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
