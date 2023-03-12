#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector> // for store the int array sometime.
using namespace std;

// first we will create a class that
// will be be our shorting container.
class Array {
public:
  vector<int> vec;
  int mid;
  int max;
  int min;
  int count;

  Array(int min) { this->min = min; }

  bool setNum(int num) {
    int mid_i;
    bool firstTime = false;

    if (this->vec.size() == 0) {
      firstTime = true;
    }

    // checking new number for min or not
    if (firstTime && num <= this->min) {
      this->min = num;
      this->vec.push_back(num);
      return true;
    }
    if (!firstTime) {
      this->max = *(this->vec.rbegin());
      this->min = *(this->vec.begin());
      // try to found middle value
      mid_i = this->vec.size() / 2;
      this->mid = this->vec.at(mid_i);
    }
    if (!firstTime && num <= this->min) {
      this->min = num;
      this->vec.insert(vec.begin(), num);
      return true;
    }

    // now insert in last
    if (this->max < num) {
      vec.push_back(num);
      return true;
    }

    this->count++;
    // now setting the value
    if (this->mid > num) {
      // lower half
      vector<int>::iterator it = this->vec.begin();
      for (; it != this->vec.begin() + mid_i; it++) {
        if (*it < num && num <= *(it + 1)) {
          vec.insert((it + 1), num);
          break;
        }
      }

    } else {
      // upper half
      vector<int>::iterator it = this->vec.begin() + mid_i;
      for (; it != this->vec.end(); it++) {
        if (*it < num && num <= *(it + 1)) {
          this->vec.insert((it + 1), num);
          break;
        }
      } // for loop end

    } // else end
    return true;
  } // func end
  void getArray(int *arr) {
    auto it = this->vec.begin();
    int count = 0;
    for (; it != this->vec.end(); it++) {
      arr[count] = *it;
      count++;
    }
  }
};

void display(int *arr, int len) {
  for (int i = 0; i < len; i++) {
    cout << arr[i] << ", ";
  }
  cout << endl;
}

void sortAlgo(int *arr, int len) {
  Array *sortArray = new Array(arr[0]);
  for (int i = 0; i < len; i++) {
    sortArray->setNum(arr[i]);
  }
  sortArray->getArray(arr);
  delete sortArray;
  // This only for debug. To check latency
  cout << "Loop runs: " << sortArray->count << " in " << len << endl;
}

// This function generates random functions
void rand(int *arr, int len) {
  srand(time(0)); // seed the random number generator with the current time
  for (int i = 0; i < len; i++) {
    int random_number =
        rand() % 100 + 1; // generate a random number between 1 and 100
    arr[i] = random_number;
  }
}

int main() {
  // A simple demo of algo
  int len = 9000;
  int *arr = new int[len];
  rand(arr, len);
  // display(arr, len);
  sortAlgo(arr, len);
  // display(arr, len);
  delete[] arr;
}

// To build use g++ main.c -o main (On Linux)
// In terminal, $ ./main
// Benchmarking with hyperfine cmd tool
// Use hyperfine ./main
// For see program output use below cmd
// hyperfine --show-output ./main