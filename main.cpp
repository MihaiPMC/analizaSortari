#include <bits/stdc++.h>
#include <ctime>

using namespace std;

void RadixSortBase10(vector<long long> &v, long long n, long long maxim) {
    unsigned long long operations = 0;
    vector<long long> output(n); operations += n;
  
    long long exp = 1; operations++;
  
    while (maxim / exp > 0) {
      operations++; // while condition
      vector<long long> count(10, 0); operations += 10;
  
      for (long long i = 0; i < n; i++) {
        count[(v[i] / exp) % 10]++;
        operations += 4;
      }
  
      for (long long i = 1; i < 10; i++) {
        count[i] += count[i - 1];
        operations += 3;
      }
  
      for (long long i = n - 1; i >= 0; i--) {
        long long digit = (v[i] / exp) % 10; operations += 4;
        output[count[digit] - 1] = v[i]; operations++;
        count[digit]--; operations++;
      }
  
      for (long long i = 0; i < n; i++) {
        v[i] = output[i]; operations += 2;
      }
  
      exp *= 10; operations++;
    }
  
    std::cout << "Radix Sort Base 10 did " << operations << " operations.\n";
  }
  

  void RadixSortBase2pow16(vector<long long> &v, long long n, long long maxim) {
    unsigned long long operations = 0;
    vector<long long> output(n); operations += n;
  
    const long long BASE = 65536; operations++;
  
    long long exp = 1; operations++;
  
    while (maxim / exp > 0) {
      operations++; // while check
      vector<long long> count(BASE, 0); operations += BASE;
  
      for (long long i = 0; i < n; i++) {
        count[(v[i] / exp) % BASE]++;
        operations += 4; // indexing + div + mod + increment
      }
  
      for (long long i = 1; i < BASE; i++) {
        count[i] += count[i - 1];
        operations += 3;
      }
  
      for (long long i = n - 1; i >= 0; i--) {
        long long digit = (v[i] / exp) % BASE; operations += 4;
        output[count[digit] - 1] = v[i]; operations++;
        count[digit]--; operations++;
      }
  
      for (long long i = 0; i < n; i++) {
        v[i] = output[i]; operations += 2;
      }
  
      exp *= BASE; operations++;
    }
  
    std::cout << "Radix Sort Base 2^16 did " << operations << " operations.\n";
  }
  

void MergeSort(vector<long long> &v, long long n) {
    unsigned long long operations = 0;
    vector<long long> output(n); operations += n;

    for (long long width = 1; width < n; width *= 2) {
        operations++;
        for (long long i = 0; i < n; i += 2 * width) {
            operations++;
            long long left = i, mid = min(i + width, n), right = min(i + 2 * width, n);
            operations += 3;

            long long i1 = left, i2 = mid, j = left;

            while (i1 < mid && i2 < right) {
                operations += 2;
                if (v[i1] <= v[i2]) {
                output[j++] = v[i1++]; operations += 3;
                } else {
                output[j++] = v[i2++]; operations += 3;
                }
            }

            while (i1 < mid) {
                output[j++] = v[i1++]; operations += 3;
            }

            while (i2 < right) {
                output[j++] = v[i2++]; operations += 3;
            }

            for (long long k = left; k < right; k++) {
                v[k] = output[k]; operations += 2;
            }
        }
    }

    std::cout << "Merge Sort did " << operations << " operations.\n";
}



void ShellSort(vector<long long> &v, long long n) {
    unsigned long long operations = 0;
  
    for (long long gap = n / 2; gap > 0; gap /= 2) {
      operations++;
      for (long long i = gap; i < n; i++) {
        long long temp = v[i]; operations += 2;
        long long j;
        for (j = i; j >= gap && v[j - gap] > temp; j -= gap) {
          v[j] = v[j - gap]; operations += 3;
        }
        v[j] = temp; operations++;
      }
    }
  
    std::cout << "Shell Sort did " << operations << " operations.\n";
}
  

void ShellSortCiura(vector<long long> &v, long long n) {
    unsigned long long operations = 0;
    vector<long long> gaps = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    operations += gaps.size();
  
    while (gaps.back() < n / 2.25) {
      gaps.push_back(gaps.back() * 2.25);
      operations++;
    }
  
    for (int k = gaps.size() - 1; k >= 0; k--) {
      long long gap = gaps[k]; operations++;
      for (long long i = gap; i < n; i++) {
        long long temp = v[i]; operations += 2;
        long long j;
        for (j = i; j >= gap && v[j - gap] > temp; j -= gap) {
          v[j] = v[j - gap]; operations += 3;
        }
        v[j] = temp; operations++;
      }
    }
  
    std::cout << "Shell Sort (Ciura) did " << operations << " operations.\n";
}

void CountSort(vector<long long> &v, long long n, long long maxim) {
    if (maxim > 1e8) {
      cout << "Count Sort is not suitable for this case." << endl;
      return;
    }
  
    unsigned long long operations = 0;
  
    vector<long long> count(maxim + 1, 0); operations += maxim + 1;
    vector<long long> output(n); operations += n;
  
    for (long long i = 0; i < n; i++) {
      count[v[i]]++; operations += 2;
    }
  
    for (long long i = 1; i <= maxim; i++) {
      count[i] += count[i - 1]; operations += 2;
    }
  
    for (long long i = n - 1; i >= 0; i--) {
      output[count[v[i]] - 1] = v[i]; operations += 3;
      count[v[i]]--; operations += 2;
    }
  
    for (long long i = 0; i < n; i++) {
      v[i] = output[i]; operations += 2;
    }
  
    std::cout << "Count Sort did " << operations << " operations.\n";
}

void heapify(vector<long long> &v, long long n, long long i, unsigned long long &operations) {
    long long temp = v[i]; operations += 2;
    long long child;
  
    while ((child = 2 * i + 1) < n) {
      operations += 2;
      if (child + 1 < n && v[child] < v[child + 1]) {
        child++; operations++;
      }
  
      if (temp < v[child]) {
        v[i] = v[child]; i = child; operations += 3;
      } else break;
    }
  
    v[i] = temp; operations++;
}
  
void HeapSort(vector<long long> &v, long long n) {
    unsigned long long operations = 0;
  
    for (long long i = n / 2 - 1; i >= 0; i--) {
      heapify(v, n, i, operations);
      operations++;
    }
  
    for (long long i = n - 1; i > 0; i--) {
      swap(v[0], v[i]); operations += 3;
      heapify(v, i, 0, operations);
    }
  
    std::cout << "Heap Sort did " << operations << " operations.\n";
  }
  

void QuickSortMiddleOps(vector<long long> &v, int left, int right, unsigned long long &operations) {
    if(left < right) {
        operations++;
        int m = (left + right) / 2; operations++;
        long long aux = v[left]; operations += 2;
        v[left] = v[m]; v[m] = aux; operations += 3;

        int i = left, j = right, d = 0; operations += 3;

        while(i < j) {
        operations++;
        if(v[i] > v[j]) {
            aux = v[i]; v[i] = v[j]; v[j] = aux; operations += 4;
            d = 1 - d; operations++;
        }
        i += d; j -= 1 - d; operations += 2;
        }

        QuickSortMiddleOps(v, left, i - 1, operations);
        QuickSortMiddleOps(v, i + 1, right, operations);
    }
}
  
void QuickSortMiddle(vector<long long> &v, int left, int right) {
    unsigned long long operations = 0;
    QuickSortMiddleOps(v, left, right, operations);
    std::cout << "QuickSort (middle) did " << operations << " operations.\n";
}

void QuickSortMedian3Ops(vector<long long> &v, int left, int right, unsigned long long &operations) {
    if(left < right) {
      operations++;
      int m = (left + right) / 2; operations++;
  
      if(v[left] > v[m]) { swap(v[left], v[m]); operations += 3; }
      if(v[m] > v[right]) { swap(v[m], v[right]); operations += 3; }
      if(v[left] > v[m]) { swap(v[left], v[m]); operations += 3; }
  
      swap(v[left], v[m]); operations += 3;
  
      int i = left, j = right, d = 0; operations += 3;
      while(i < j) {
        operations++;
        if(v[i] > v[j]) {
          swap(v[i], v[j]); operations += 3;
          d = 1 - d; operations++;
        }
        i += d; j -= 1 - d; operations += 2;
      }
  
      QuickSortMedian3Ops(v, left, i - 1, operations);
      QuickSortMedian3Ops(v, i + 1, right, operations);
    }
  }
  
void QuickSortMedian3(vector<long long> &v, int left, int right) {
    unsigned long long operations = 0;
    QuickSortMedian3Ops(v, left, right, operations);
    std::cout << "QuickSort (median of 3) did " << operations << " operations.\n";
}

pair<int, int> PartitionEqual(vector<long long> &v, int left, int right, unsigned long long &operations) {
    long long pivot = v[left];
    int lt = left;       
    int gt = right;      
    int i = left + 1;
  
    while(i <= gt) {
      operations++;
      if(v[i] < pivot) {
        swap(v[lt], v[i]); operations += 3;
        lt++; i++;
      } else if(v[i] > pivot) {
        swap(v[i], v[gt]); operations += 3;
        gt--;
      } else {
        i++;
      }
    }
    return {lt, gt}; 
  }
  

  void QuickSortMedian5Ops(vector<long long> &v, int left, int right, unsigned long long &operations) {
    if(left < right) {
      operations++;
      if (right - left >= 4) {
        int i1 = left;
        int i2 = left + (right - left) / 4;
        int i3 = (left + right) / 2;
        int i4 = right - (right - left) / 4;
        int i5 = right;
        operations += 5;
  
        vector<pair<long long, int>> samples = {
          {v[i1], i1}, {v[i2], i2}, {v[i3], i3}, {v[i4], i4}, {v[i5], i5}
        };
        sort(samples.begin(), samples.end()); operations += 5 * log2(5);
  
        swap(v[left], v[samples[2].second]); operations += 3;
      } else {
        int m = (left + right) / 2; operations++;
        if(v[left] > v[m]) { swap(v[left], v[m]); operations += 3; }
        if(v[m] > v[right]) { swap(v[m], v[right]); operations += 3; }
        if(v[left] > v[m]) { swap(v[left], v[m]); operations += 3; }
        swap(v[left], v[m]); operations += 3;
      }
  
      auto [lt, gt] = PartitionEqual(v, left, right, operations);
  
      QuickSortMedian5Ops(v, left, lt - 1, operations);
      QuickSortMedian5Ops(v, gt + 1, right, operations);
    }
  }
  
  
void QuickSortMedian5(vector<long long> &v, int left, int right) {
    unsigned long long operations = 0;
    std::cout << "QuickSort (median of 5) did " << operations << " operations.\n";
}

long long randomNumber(int No, long long min, long long max) {
    random_device rd;  
    mt19937 eng(rd()); 
    uniform_int_distribution<> distr(0, max); 

    long long p10 = 1;
    for (int i = 0; i <= No; i++) {
        p10 *= 10;
    }
    long long rand = distr(eng);
    long long number = (rand * rand + rand + rand / 3 + rand / 7 + 666013) % p10;
    if (number < min)
      number += min;
    return number % max + 1;
}

vector<long long> generateRandomNumbers(int n, long long min, long long max) {
    vector<long long> numbers(n);
    for (int i = 0; i < n; i++) {
        int cif = rand() % 17 + 1;
        numbers[i] = randomNumber(cif, min, max);
    }
    return numbers;
}

vector<long long> generate1Number(int n, long long min, long long max) {
    vector<long long> numbers(n);
    int cif = rand() % 14 + 5;
    long long number = randomNumber(cif, min, max);
    for (int i = 0; i < n; i++) {
        numbers[i] = number;
    }
    return numbers;
}

vector<long long> generateIncreasing(int n, long long min, long long max) {
  vector<long long> numbers(n);
  for (int i = 0; i < n; i++) {
      int cif = rand() % 14 + 1;
      numbers[i] = randomNumber(cif, min, max);
  }
  sort(numbers.begin(), numbers.end()); // Optional, but set already gives increasing
  return numbers;
}

vector<long long> generateAlmostIncreasing(int n, long long min, long long max, int alpha) {
  vector<long long> numbers = generateIncreasing(n, min, max);
  int swaps = ((100 - alpha) * n) / 100;
  for(int i = 0; i < swaps; i++) {
    int pos1 = rand() % n;
    int pos2 = rand() % n;
    swap(numbers[pos1], numbers[pos2]);
  }
  return numbers;
}

vector<long long> generateDecreasing(int n, long long min, long long max) {
  vector<long long> numbers(n);
  for (int i = 0; i < n; i++) {
    int cif = rand() % 14 + 1;
    numbers[i] = randomNumber(cif, min, max);
  }
  sort(numbers.begin(), numbers.end(), greater<long long>());
  return numbers;
}

vector<long long> generateAlmostDecreasing(int n, long long min, long long max, int alpha) {
  vector<long long> numbers = generateDecreasing(n, min, max);
  int swaps = ((100 - alpha) * n) / 100;
  for(int i = 0; i < swaps; i++) {
    int pos1 = rand() % n;
    int pos2 = rand() % n;
    swap(numbers[pos1], numbers[pos2]);
  }
  return numbers;
}


int main() {
    int t = 1;
    long long n = 1e6;
    long long maxim = 2e14;
    vector<long long> aux, v;
    srand(time(0) + 1);

    // aux = generateAlmostDecreasing(1e7, 1, maxim, 90);
    clock_t begin, end;
    double elapsed_seconds;

    begin = clock();
    aux = generateRandomNumbers(1e6, 1, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken to generate random numbers: " << elapsed_seconds << " seconds" << endl;
    cout << "Generated " << n << " random numbers from" << 1 << " to " << maxim << endl;


    v = aux;  
    // Radix Sort Base 10
    begin = clock();
    RadixSortBase10(v, n, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Radix Sort Base 10 in test case " << t << ": " << elapsed_seconds << " seconds" << endl;


    v = aux;
    // Radix Sort Base 2^16
    begin = clock();
    RadixSortBase2pow16(v, n, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Radix Sort Base 2^16 in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    // Merge Sort
    begin = clock();
    MergeSort(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Merge Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    //shell sort
    begin = clock();
    ShellSort(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Shell Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    // Shell Sort with Ciura sequence
    begin = clock();
    ShellSortCiura(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Shell Sort (Ciura) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    //count sort
    begin = clock();
    CountSort(v, n, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Count Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    // Heap Sort
    begin = clock();
    HeapSort(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Heap Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    // QuickSort with middle pivot (original)
    v = aux;
    begin = clock();
    QuickSortMiddle(v, 0, n-1);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for QuickSort (middle pivot) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    // QuickSort with median of 3
    v = aux;
    begin = clock();
    QuickSortMedian3(v, 0, n-1);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for QuickSort (median of 3) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    // QuickSort with median of 5
    v = aux;
    begin = clock();
    QuickSortMedian5(v, 0, n-1);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for QuickSort (median of 5) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;


    ////////////////////////////////// TEST CASE 2 /////////////////////////////////////////

    cout << endl << "TEST CASE 2" << endl;
    t = 2;

    begin = clock();
    aux = generate1Number(1e6, 1, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken to generate random numbers: " << elapsed_seconds << " seconds" << endl;
    cout << "Generated 1 random number reapeted for" << n << " times "<< endl;


    v = aux;  
    // Radix Sort Base 10
    begin = clock();
    RadixSortBase10(v, n, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Radix Sort Base 10 in test case " << t << ": " << elapsed_seconds << " seconds" << endl;


    v = aux;
    // Radix Sort Base 2^16
    begin = clock();
    RadixSortBase2pow16(v, n, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Radix Sort Base 2^16 in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    // Merge Sort
    begin = clock();
    MergeSort(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Merge Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    //shell sort
    begin = clock();
    ShellSort(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Shell Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    // Shell Sort with Ciura sequence
    begin = clock();
    ShellSortCiura(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Shell Sort (Ciura) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    //count sort
    begin = clock();
    CountSort(v, n, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Count Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    // Heap Sort
    begin = clock();
    HeapSort(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Heap Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    // QuickSort with middle pivot (original)
    v = aux;
    begin = clock();
    QuickSortMiddle(v, 0, n-1);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for QuickSort (middle pivot) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    // QuickSort with median of 3
    v = aux;
    begin = clock();
    QuickSortMedian3(v, 0, n-1);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for QuickSort (median of 3) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    // QuickSort with median of 5
    v = aux;
    begin = clock();
    QuickSortMedian5(v, 0, n-1);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for QuickSort (median of 5) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    ////////////////////////////////// TEST CASE 3 /////////////////////////////////////////

    cout << endl << "TEST CASE 3" << endl;
    t = 3;

    begin = clock();
    aux = generateIncreasing(1e6, 1, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken to generate random numbers: " << elapsed_seconds << " seconds" << endl;
    cout << "Generated " << n << " increasing random numbers from 1 to" << maxim << endl;


    v = aux;  
    // Radix Sort Base 10
    begin = clock();
    RadixSortBase10(v, n, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Radix Sort Base 10 in test case " << t << ": " << elapsed_seconds << " seconds" << endl;


    v = aux;
    // Radix Sort Base 2^16
    begin = clock();
    RadixSortBase2pow16(v, n, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Radix Sort Base 2^16 in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    // Merge Sort
    begin = clock();
    MergeSort(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Merge Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    //shell sort
    begin = clock();
    ShellSort(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Shell Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    // Shell Sort with Ciura sequence
    begin = clock();
    ShellSortCiura(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Shell Sort (Ciura) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    //count sort
    begin = clock();
    CountSort(v, n, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Count Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    // Heap Sort
    begin = clock();
    HeapSort(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Heap Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    // QuickSort with middle pivot (original)
    v = aux;
    begin = clock();
    QuickSortMiddle(v, 0, n-1);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for QuickSort (middle pivot) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    // QuickSort with median of 3
    v = aux;
    begin = clock();
    QuickSortMedian3(v, 0, n-1);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for QuickSort (median of 3) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    // QuickSort with median of 5
    v = aux;
    begin = clock();
    QuickSortMedian5(v, 0, n-1);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for QuickSort (median of 5) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

     ////////////////////////////////// TEST CASE 4 /////////////////////////////////////////

     cout << endl << "TEST CASE 4" << endl;
     t = 4;
 
     begin = clock();
     aux = generateAlmostIncreasing(1e6, 1, maxim, 85);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken to generate random numbers: " << elapsed_seconds << " seconds" << endl;
     cout << "Generated " << n << " increasing random numbers from 1 to" << maxim << endl;
     cout << "Alpha = 85 (sorted coefficient)" << endl;
 
 
     v = aux;  
     // Radix Sort Base 10
     begin = clock();
     RadixSortBase10(v, n, maxim);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for Radix Sort Base 10 in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
 
     v = aux;
     // Radix Sort Base 2^16
     begin = clock();
     RadixSortBase2pow16(v, n, maxim);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for Radix Sort Base 2^16 in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
     v = aux;
     // Merge Sort
     begin = clock();
     MergeSort(v, n);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for Merge Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
     v = aux;
     //shell sort
     begin = clock();
     ShellSort(v, n);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for Shell Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
     v = aux;
     // Shell Sort with Ciura sequence
     begin = clock();
     ShellSortCiura(v, n);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for Shell Sort (Ciura) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
     v = aux;
     //count sort
     begin = clock();
     CountSort(v, n, maxim);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for Count Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
     v = aux;
     // Heap Sort
     begin = clock();
     HeapSort(v, n);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for Heap Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
     // QuickSort with middle pivot (original)
     v = aux;
     begin = clock();
     QuickSortMiddle(v, 0, n-1);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for QuickSort (middle pivot) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
     // QuickSort with median of 3
     v = aux;
     begin = clock();
     QuickSortMedian3(v, 0, n-1);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for QuickSort (median of 3) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
     // QuickSort with median of 5
     v = aux;
     begin = clock();
     QuickSortMedian5(v, 0, n-1);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for QuickSort (median of 5) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

         ////////////////////////////////// TEST CASE 5 /////////////////////////////////////////

    cout << endl << "TEST CASE 5" << endl;
    t = 5;

    begin = clock();
    aux = generateDecreasing(1e6, 1, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken to generate random numbers: " << elapsed_seconds << " seconds" << endl;
    cout << "Generated " << n << " decreasing random numbers from 1 to" << maxim << endl;


    v = aux;  
    // Radix Sort Base 10
    begin = clock();
    RadixSortBase10(v, n, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Radix Sort Base 10 in test case " << t << ": " << elapsed_seconds << " seconds" << endl;


    v = aux;
    // Radix Sort Base 2^16
    begin = clock();
    RadixSortBase2pow16(v, n, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Radix Sort Base 2^16 in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    // Merge Sort
    begin = clock();
    MergeSort(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Merge Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    //shell sort
    begin = clock();
    ShellSort(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Shell Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    // Shell Sort with Ciura sequence
    begin = clock();
    ShellSortCiura(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Shell Sort (Ciura) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    //count sort
    begin = clock();
    CountSort(v, n, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Count Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    // Heap Sort
    begin = clock();
    HeapSort(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Heap Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    // QuickSort with middle pivot (original)
    v = aux;
    begin = clock();
    QuickSortMiddle(v, 0, n-1);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for QuickSort (middle pivot) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    // QuickSort with median of 3
    v = aux;
    begin = clock();
    QuickSortMedian3(v, 0, n-1);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for QuickSort (median of 3) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    // QuickSort with median of 5
    v = aux;
    begin = clock();
    QuickSortMedian5(v, 0, n-1);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for QuickSort (median of 5) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

     

     ////////////////////////////////// TEST CASE 6 /////////////////////////////////////////

     cout << endl << "TEST CASE 6" << endl;
     t = 6;
 
     begin = clock();
     aux = generateAlmostIncreasing(1e6, 1, maxim, 85);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken to generate random numbers: " << elapsed_seconds << " seconds" << endl;
     cout << "Generated " << n << " decreasing random numbers from 1 to" << maxim << endl;
     cout << "Alpha = 85 (sorted coefficient)" << endl;
 
 
     v = aux;  
     // Radix Sort Base 10
     begin = clock();
     RadixSortBase10(v, n, maxim);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for Radix Sort Base 10 in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
 
     v = aux;
     // Radix Sort Base 2^16
     begin = clock();
     RadixSortBase2pow16(v, n, maxim);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for Radix Sort Base 2^16 in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
     v = aux;
     // Merge Sort
     begin = clock();
     MergeSort(v, n);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for Merge Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
     v = aux;
     //shell sort
     begin = clock();
     ShellSort(v, n);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for Shell Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
     v = aux;
     // Shell Sort with Ciura sequence
     begin = clock();
     ShellSortCiura(v, n);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for Shell Sort (Ciura) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
     v = aux;
     //count sort
     begin = clock();
     CountSort(v, n, maxim);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for Count Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
     v = aux;
     // Heap Sort
     begin = clock();
     HeapSort(v, n);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for Heap Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
     // QuickSort with middle pivot (original)
     v = aux;
     begin = clock();
     QuickSortMiddle(v, 0, n-1);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for QuickSort (middle pivot) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
     // QuickSort with median of 3
     v = aux;
     begin = clock();
     QuickSortMedian3(v, 0, n-1);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for QuickSort (median of 3) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
 
     // QuickSort with median of 5
     v = aux;
     begin = clock();
     QuickSortMedian5(v, 0, n-1);
     end = clock();
     elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
     cout << "Time taken for QuickSort (median of 5) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;


         ////////////////////////////////// TEST CASE 7 /////////////////////////////////////////

    cout << endl << "TEST CASE 7" << endl;
    t = 7;
    maxim = 100;

    begin = clock();
    aux = generateRandomNumbers(1e6, 1, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken to generate random numbers: " << elapsed_seconds << " seconds" << endl;
    cout << "Generated " << n << " increasing random numbers from 1 to" << maxim << endl;


    v = aux;  
    // Radix Sort Base 10
    begin = clock();
    RadixSortBase10(v, n, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Radix Sort Base 10 in test case " << t << ": " << elapsed_seconds << " seconds" << endl;


    v = aux;
    // Radix Sort Base 2^16
    begin = clock();
    RadixSortBase2pow16(v, n, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Radix Sort Base 2^16 in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    // Merge Sort
    begin = clock();
    MergeSort(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Merge Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    //shell sort
    begin = clock();
    ShellSort(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Shell Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    // Shell Sort with Ciura sequence
    begin = clock();
    ShellSortCiura(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Shell Sort (Ciura) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    //count sort
    begin = clock();
    CountSort(v, n, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Count Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    v = aux;
    // Heap Sort
    begin = clock();
    HeapSort(v, n);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Heap Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    // QuickSort with middle pivot (original)
    v = aux;
    begin = clock();
    QuickSortMiddle(v, 0, n-1);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for QuickSort (middle pivot) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    // QuickSort with median of 3
    v = aux;
    begin = clock();
    QuickSortMedian3(v, 0, n-1);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for QuickSort (median of 3) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

    // QuickSort with median of 5
    v = aux;
    begin = clock();
    QuickSortMedian5(v, 0, n-1);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for QuickSort (median of 5) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
  return 0;
}