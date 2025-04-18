#include <bits/stdc++.h>
#include <ctime>

using namespace std;

// Structure to store sorting algorithm results
struct SortResult {
    string name;
    double time;
    unsigned long long operations;
    unsigned long long comparisons;
};


// Function to generate CSV file for a test case
void generateCSV(const vector<SortResult>& results, int testCase) {
    string filename = "test_case_" + to_string(testCase) + "_results.csv";
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    // Write header
    outFile << "Algorithm,Time (seconds),Operations,Comparisons" << endl;

    // Write data
    for (const auto& result : results) {
        outFile << result.name << ","
                << result.time << ","
                << result.operations << ","
                << result.comparisons << endl;
    }

    outFile.close();
    cout << "CSV file generated: " << filename << endl;
}

void generateConsolidatedCSV(vector<vector<SortResult>>& allResults, const vector<string>& testDescriptions) {
    string filename = "all_test_results.csv";
    ofstream outFile(filename);

    if (!outFile.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    // Write header with test case columns
    outFile << "Algorithm";
    for (size_t i = 0; i < testDescriptions.size(); i++) {
        outFile << ",Test " << (i+1) << " Time";
    }
    outFile << endl;

    // Get all algorithm names
    set<string> algorithmNames;
    for (const auto& results : allResults) {
        for (const auto& result : results) {
            algorithmNames.insert(result.name);
        }
    }

    // Write data for each algorithm across all tests
    for (const auto& algoName : algorithmNames) {
        outFile << algoName;

        for (const auto& results : allResults) {
            // Find this algorithm in the current test results
            auto it = find_if(results.begin(), results.end(),
                             [&algoName](const SortResult& r) { return r.name == algoName; });

            if (it != results.end()) {
                outFile << "," << it->time;
            } else {
                outFile << ",";  // Empty if algorithm wasn't run in this test
            }
        }
        outFile << endl;
    }

    outFile.close();
    cout << "Consolidated CSV file generated: " << filename << endl;
}


void RadixSortBase10(vector<long long> &v, long long n, long long maxim, unsigned long long &operations, unsigned long long &comparisons) {
    vector<long long> output(n); operations += n;

    long long exp = 1; operations++;

    while (maxim / exp > 0) {
      comparisons++;
      vector<long long> count(10, 0); operations += 10;

      for (long long i = 0; i < n; i++) {
        comparisons++;
        count[(v[i] / exp) % 10]++;
        operations += 4;
      }

      for (long long i = 1; i < 10; i++) {
        comparisons++;
        count[i] += count[i - 1];
        operations += 3;
      }

      for (long long i = n - 1; i >= 0; i--) {
        comparisons++;
        long long digit = (v[i] / exp) % 10; operations += 4;
        output[count[digit] - 1] = v[i]; operations++;
        count[digit]--; operations++;
      }

      for (long long i = 0; i < n; i++) {
        comparisons++;
        v[i] = output[i]; operations += 2;
      }

      exp *= 10; operations++;
    }

    std::cout << "Radix Sort Base 10 did " << operations << " operations and " << comparisons << " comparisons.\n";
}

void RadixSortBase2pow16(vector<long long> &v, long long n, long long maxim,unsigned long long &operations,unsigned long long &comparisons) {
    vector<long long> output(n); operations += n;

    const long long BASE = 65536; operations++;

    long long exp = 1; operations++;

    while (maxim / exp > 0) {
      comparisons++;
      vector<long long> count(BASE, 0); operations += BASE;

      for (long long i = 0; i < n; i++) {
        comparisons++;
        count[(v[i] / exp) % BASE]++;
        operations += 4;
      }

      for (long long i = 1; i < BASE; i++) {
        comparisons++;
        count[i] += count[i - 1];
        operations += 3;
      }

      for (long long i = n - 1; i >= 0; i--) {
        comparisons++;
        long long digit = (v[i] / exp) % BASE; operations += 4;
        output[count[digit] - 1] = v[i]; operations++;
        count[digit]--; operations++;
      }

      for (long long i = 0; i < n; i++) {
        comparisons++;
        v[i] = output[i]; operations += 2;
      }

      exp *= BASE; operations++;
    }

    std::cout << "Radix Sort Base 2^16 did " << operations << " operations and " << comparisons << " comparisons.\n";
}

void MergeSort(vector<long long> &v, long long n, unsigned long long &operations, unsigned long long &comparisons) {
    vector<long long> output(n); operations += n;

    for (long long width = 1; width < n; width *= 2) {
        comparisons++;
        operations++;
        for (long long i = 0; i < n; i += 2 * width) {
            comparisons++;
            operations++;
            long long left = i, mid = min(i + width, n), right = min(i + 2 * width, n);
            operations += 3;

            long long i1 = left, i2 = mid, j = left;

            while (i1 < mid && i2 < right) {
                comparisons += 2;
                if (v[i1] <= v[i2]) {
                    comparisons++;
                    output[j++] = v[i1++]; operations += 3;
                } else {
                    output[j++] = v[i2++]; operations += 3;
                }
            }

            while (i1 < mid) {
                comparisons++;
                output[j++] = v[i1++]; operations += 3;
            }

            while (i2 < right) {
                comparisons++;
                output[j++] = v[i2++]; operations += 3;
            }

            for (long long k = left; k < right; k++) {
                comparisons++;
                v[k] = output[k]; operations += 2;
            }
        }
    }

    std::cout << "Merge Sort did " << operations << " operations and " << comparisons << " comparisons.\n";
}

void ShellSort(vector<long long> &v, long long n, unsigned long long &operations, unsigned long long &comparisons) {

    for (long long gap = n / 2; gap > 0; gap /= 2) {
      comparisons++;
      operations++;
      for (long long i = gap; i < n; i++) {
        comparisons++;
        long long temp = v[i]; operations += 2;
        long long j;
        for (j = i; j >= gap && v[j - gap] > temp; j -= gap) {
          comparisons += 2;
          v[j] = v[j - gap]; operations += 3;
        }
        comparisons++;
        v[j] = temp; operations++;
      }
    }

    std::cout << "Shell Sort did " << operations << " operations and " << comparisons << " comparisons.\n";
}

void ShellSortCiura(vector<long long> &v, long long n, unsigned long long &operations, unsigned long long &comparisons) {
    vector<long long> gaps = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    operations += gaps.size();

    while (gaps.back() < n / 2.25) {
      comparisons++;
      gaps.push_back(gaps.back() * 2.25);
      operations++;
    }

    for (int k = gaps.size() - 1; k >= 0; k--) {
      comparisons++;
      long long gap = gaps[k]; operations++;
      for (long long i = gap; i < n; i++) {
        comparisons++;
        long long temp = v[i]; operations += 2;
        long long j;
        for (j = i; j >= gap && v[j - gap] > temp; j -= gap) {
          comparisons += 2;
          v[j] = v[j - gap]; operations += 3;
        }
        comparisons++;
        v[j] = temp; operations++;
      }
    }

    std::cout << "Shell Sort (Ciura) did " << operations << " operations and " << comparisons << " comparisons.\n";
}

void CountSort(vector<long long> &v, long long n, long long maxim, unsigned long long &operations, unsigned long long &comparisons) {
    if (maxim > 1e9) {
      cout << "Count Sort is not suitable for this case." << endl;
      return;
    }


    vector<long long> count(maxim + 1, 0); operations += maxim + 1;
    vector<long long> output(n); operations += n;

    for (long long i = 0; i < n; i++) {
      comparisons++;
      count[v[i]]++; operations += 2;
    }

    for (long long i = 1; i <= maxim; i++) {
      comparisons++;
      count[i] += count[i - 1]; operations += 2;
    }

    for (long long i = n - 1; i >= 0; i--) {
      comparisons++;
      output[count[v[i]] - 1] = v[i]; operations += 3;
      count[v[i]]--; operations += 2;
    }

    for (long long i = 0; i < n; i++) {
      comparisons++;
      v[i] = output[i]; operations += 2;
    }

    std::cout << "Count Sort did " << operations << " operations and " << comparisons << " comparisons.\n";
}

void heapify(vector<long long> &v, long long n, long long i, unsigned long long &operations, unsigned long long &comparisons) {
    long long temp = v[i]; operations += 2;
    long long child;

    while ((child = 2 * i + 1) < n) {
      comparisons++;
      operations += 2;
      if (child + 1 < n && v[child] < v[child + 1]) {
        comparisons += 2;
        child++; operations++;
      }

      if (temp < v[child]) {
        comparisons++;
        v[i] = v[child]; i = child; operations += 3;
      } else {
        comparisons++;
        break;
      }
    }

    v[i] = temp; operations++;
}

void HeapSort(vector<long long> &v, long long n, unsigned long long &operations, unsigned long long &comparisons) {

    for (long long i = n / 2 - 1; i >= 0; i--) {
      comparisons++;
      heapify(v, n, i, operations, comparisons);
      operations++;
    }

    for (long long i = n - 1; i > 0; i--) {
      comparisons++;
      swap(v[0], v[i]); operations += 3;
      heapify(v, i, 0, operations, comparisons);
    }

}

void QuickSortMiddle(vector<long long>& v, int low, int high, unsigned long long &operations, unsigned long long &comparisons) {
    operations++;
    comparisons++;
    if(low < high) {
        int i = low, j = high; operations += 2;
        long long pivot = v[(low + high) / 2]; operations++;
        while(i <= j) {
            comparisons++;
            while(v[i] < pivot) {
                comparisons++;
                i++; operations++;
            }
            while(v[j] > pivot) {
                comparisons++;
                j--; operations++;
            }
            comparisons++;
            if(i <= j) {
                swap(v[i], v[j]); operations += 3;
                i++; j--; operations += 2;
            }
        }
        comparisons++; if(low < j) QuickSortMiddle(v, low, j, operations, comparisons);
        comparisons++; if(i < high) QuickSortMiddle(v, i, high, operations, comparisons);
    }
}

void QuickSortMedian3(vector<long long>& v, int low, int high, unsigned long long &operations, unsigned long long &comparisons) {
    operations++;
    comparisons++;
    if(low < high) {
        int mid = low + (high - low) / 2; operations++;

        comparisons++;
        if(v[low] > v[mid]) { swap(v[low], v[mid]); operations += 3; }

        comparisons++;
        if(v[low] > v[high]) { swap(v[low], v[high]); operations += 3; }

        comparisons++;
        if(v[mid] > v[high]) { swap(v[mid], v[high]); operations += 3; }

        long long pivot = v[mid]; operations++;

        int i = low, j = high; operations += 2;
        while(i <= j) {
            comparisons++;
            while(v[i] < pivot) {
                comparisons++;
                i++; operations++;
            }
            while(v[j] > pivot) {
                comparisons++;
                j--; operations++;
            }
            comparisons++;
            if(i <= j) {
                swap(v[i], v[j]); operations += 3;
                i++; j--; operations += 2;
            }
        }
        comparisons++; if(low < j) QuickSortMedian3(v, low, j, operations, comparisons);
        comparisons++; if(i < high) QuickSortMedian3(v, i, high, operations, comparisons);
    }
}

void QuickSortMedian5(vector<long long>& v, int low, int high, unsigned long long &operations, unsigned long long &comparisons) {
    operations++;
    comparisons++;
    if(low < high) {
        int idx1 = low;
        int idx2 = low + (high - low) / 4;
        int idx3 = low + (high - low) / 2;
        int idx4 = low + 3 * (high - low) / 4;
        int idx5 = high;
        vector<pair<long long,int>> samples = {
            {v[idx1], idx1},
            {v[idx2], idx2},
            {v[idx3], idx3},
            {v[idx4], idx4},
            {v[idx5], idx5}
        };
        operations += 10;

        sort(samples.begin(), samples.end(), [](auto &a, auto &b) {
            return a.first < b.first;
        });
        operations += 10;
        comparisons += 10;

        int medianIdx = samples[2].second; operations++;
        long long pivot = v[medianIdx]; operations++;

        int i = low, j = high; operations += 2;
        while(i <= j) {
            comparisons++;
            while(v[i] < pivot) {
                comparisons++;
                i++; operations++;
            }
            while(v[j] > pivot) {
                comparisons++;
                j--; operations++;
            }
            comparisons++;
            if(i <= j) {
                swap(v[i], v[j]); operations += 3;
                i++; j--; operations += 2;
            }
        }
        comparisons++; if(low < j) QuickSortMedian5(v, low, j, operations, comparisons);
        comparisons++; if(i < high) QuickSortMedian5(v, i, high, operations, comparisons);
    }
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


void runAllSorts(vector<long long>& aux, long long n, long long maxim, int t) {
    vector<long long> v;
    clock_t begin, end;
    double elapsed_seconds;
    unsigned long long operations, comparisons;
    vector<SortResult> results;

    v = aux;
    operations = 0;
    comparisons = 0;
    // Radix Sort Base 10
    begin = clock();
    RadixSortBase10(v, n, maxim, operations, comparisons);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Radix Sort Base 10 in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
    std::cout << "Radix Sort Base 10 did " << operations << " operations and " << comparisons << " comparisons.\n";
    results.push_back({"Radix Sort Base 10", elapsed_seconds, operations, comparisons});

    v = aux;
    operations = 0;
    comparisons = 0;
    // Radix Sort Base 2^16
    begin = clock();
    RadixSortBase2pow16(v, n, maxim, operations, comparisons);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Radix Sort Base 2^16 in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
    std::cout << "Radix Sort Base 2^16 did " << operations << " operations and " << comparisons << " comparisons.\n";
    results.push_back({"Radix Sort Base 2^16", elapsed_seconds, operations, comparisons});

    v = aux;
    operations = 0;
    comparisons = 0;
    // Merge Sort
    begin = clock();
    MergeSort(v, n, operations, comparisons);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Merge Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
    std::cout << "Merge Sort did " << operations << " operations and " << comparisons << " comparisons.\n";
    results.push_back({"Merge Sort", elapsed_seconds, operations, comparisons});

    v = aux;
    operations = 0;
    comparisons = 0;
    // Shell Sort
    begin = clock();
    ShellSort(v, n, operations, comparisons);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Shell Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
    std::cout << "Shell Sort did " << operations << " operations and " << comparisons << " comparisons.\n";
    results.push_back({"Shell Sort", elapsed_seconds, operations, comparisons});

    v = aux;
    operations = 0;
    comparisons = 0;
    // Shell Sort with Ciura sequence
    begin = clock();
    ShellSortCiura(v, n, operations, comparisons);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Shell Sort (Ciura) in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
    std::cout << "Shell Sort (Ciura) did " << operations << " operations and " << comparisons << " comparisons.\n";
    results.push_back({"Shell Sort (Ciura)", elapsed_seconds, operations, comparisons});

    v = aux;
    operations = 0;
    comparisons = 0;
    // Count Sort
    begin = clock();
    CountSort(v, n, maxim, operations, comparisons);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Count Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
    std::cout << "Count Sort did " << operations << " operations and " << comparisons << " comparisons.\n";
    results.push_back({"Count Sort", elapsed_seconds, operations, comparisons});

    v = aux;
    operations = 0;
    comparisons = 0;
    // Heap Sort
    begin = clock();
    HeapSort(v, n, operations, comparisons);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken for Heap Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;
    std::cout << "Heap Sort did " << operations << " operations and " << comparisons << " comparisons.\n";
    results.push_back({"Heap Sort", elapsed_seconds, operations, comparisons});

    // QuickSort with middle pivot
    v = aux;
    operations = 0;
    comparisons = 0;
    begin = clock();
    QuickSortMiddle(v, 0, n-1, operations, comparisons);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "QuickSort (middle pivot) did " << operations << " operations and " << comparisons << " comparisons.\n";
    std::cout << "Time taken for QuickSort (middle pivot) in test case " << t << ": " << elapsed_seconds << " seconds" << std::endl;
    results.push_back({"QuickSort (middle pivot)", elapsed_seconds, operations, comparisons});

    // QuickSort with median of 3
    v = aux;
    operations = 0;
    comparisons = 0;
    begin = clock();
    QuickSortMedian3(v, 0, n-1, operations, comparisons);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "QuickSort (median of 3) did " << operations << " operations and " << comparisons << " comparisons.\n";
    std::cout << "Time taken for QuickSort (median of 3) in test case " << t << ": " << elapsed_seconds << " seconds" << std::endl;
    results.push_back({"QuickSort (median of 3)", elapsed_seconds, operations, comparisons});

    // QuickSort with median of 5
    v = aux;
    operations = 0;
    comparisons = 0;
    begin = clock();
    QuickSortMedian5(v, 0, n-1, operations, comparisons);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "QuickSort (median of 5) did " << operations << " operations and " << comparisons << " comparisons.\n";
    std::cout << "Time taken for QuickSort (median of 5) in test case " << t << ": " << elapsed_seconds << " seconds" << std::endl;
    results.push_back({"QuickSort (median of 5)", elapsed_seconds, operations, comparisons});

    // Generate CSV file for this test case
    generateCSV(results, t);
}


int main() {
    int t = 1;
    long long n = 1e6;
    long long maxim = 2e14;
    vector<long long> aux;
    clock_t begin, end;
    double elapsed_seconds;
    vector<vector<SortResult>> allTestResults;
    vector<string> testDescriptions;

    srand(time(nullptr) + 1);

    ////////////////////////////////// TEST CASE 1 /////////////////////////////////////////
    cout << "TEST CASE 1" << endl;
    t = 1;
    testDescriptions.push_back("Random numbers");

    begin = clock();
    aux = generateRandomNumbers(1e6, 1, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken to generate random numbers: " << elapsed_seconds << " seconds" << endl;
    cout << "Generated " << n << " random numbers from " << 1 << " to " << maxim << endl << endl;

    runAllSorts(aux, n, maxim, t);

    ////////////////////////////////// TEST CASE 2 /////////////////////////////////////////
    cout << endl << "TEST CASE 2" << endl;
    t = 2;
    testDescriptions.push_back("One repeated number");

    begin = clock();
    aux = generate1Number(1e6, 1, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken to generate random numbers: " << elapsed_seconds << " seconds" << endl;
    cout << "Generated 1 random number repeated " << n << " times" << endl << endl;

    runAllSorts(aux, n, maxim, t);

    ////////////////////////////////// TEST CASE 3 /////////////////////////////////////////
    cout << endl << "TEST CASE 3" << endl;
    t = 3;
    testDescriptions.push_back("Increasing order");

    begin = clock();
    aux = generateIncreasing(1e6, 1, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken to generate random numbers: " << elapsed_seconds << " seconds" << endl;
    cout << "Generated " << n << " increasing random numbers from 1 to " << maxim << endl << endl;

    runAllSorts(aux, n, maxim, t);

    ////////////////////////////////// TEST CASE 4 /////////////////////////////////////////
    cout << endl << "TEST CASE 4" << endl;
    t = 4;
    testDescriptions.push_back("Almost increasing order");

    begin = clock();
    aux = generateAlmostIncreasing(1e6, 1, maxim, 85);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken to generate random numbers: " << elapsed_seconds << " seconds" << endl;
    cout << "Generated " << n << " almost increasing random numbers from 1 to " << maxim << endl;
    cout << "Alpha = 85 (sorted coefficient)" << endl << endl;

    runAllSorts(aux, n, maxim, t);

    ////////////////////////////////// TEST CASE 5 /////////////////////////////////////////
    cout << endl << "TEST CASE 5" << endl;
    t = 5;
    testDescriptions.push_back("Decreasing order");

    begin = clock();
    aux = generateDecreasing(1e6, 1, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken to generate random numbers: " << elapsed_seconds << " seconds" << endl;
    cout << "Generated " << n << " decreasing random numbers from 1 to " << maxim << endl << endl;

    runAllSorts(aux, n, maxim, t);

    ////////////////////////////////// TEST CASE 6 /////////////////////////////////////////
    cout << endl << "TEST CASE 6" << endl;
    t = 6;
    testDescriptions.push_back("Almost decreasing order");

    begin = clock();
    aux = generateAlmostDecreasing(1e6, 1, maxim, 85);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken to generate random numbers: " << elapsed_seconds << " seconds" << endl;
    cout << "Generated " << n << " almost decreasing random numbers from 1 to " << maxim << endl;
    cout << "Alpha = 85 (sorted coefficient)" << endl << endl;

    runAllSorts(aux, n, maxim, t);

    ////////////////////////////////// TEST CASE 7 /////////////////////////////////////////
    cout << endl << "TEST CASE 7" << endl;
    t = 7;
    maxim = 100;
    testDescriptions.push_back("Small range random numbers");

    begin = clock();
    aux = generateRandomNumbers(1e6, 1, maxim);
    end = clock();
    elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time taken to generate random numbers: " << elapsed_seconds << " seconds" << endl;
    cout << "Generated " << n << " random numbers with small range from 1 to " << maxim << endl << endl;

    runAllSorts(aux, n, maxim, t);

    // Generate consolidated CSV with results from all tests
    generateConsolidatedCSV(allTestResults, testDescriptions);

    cout << "\nAll CSV files have been generated. You can now create graphs using these files." << endl;
    cout << "For individual test graphs, use test_case_X_results.csv files." << endl;
    cout << "For a comparison across all tests, use all_test_results.csv." << endl;

    return 0;
}

