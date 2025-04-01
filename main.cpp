#include <bits/stdc++.h>
#include <ctime>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

void RadixSortBase10(vector<long long> &v, long long n, long long maxim)
{
    vector<long long> output(n);

    long long exp = 1;

    while (maxim / exp > 0)
    {
        vector<long long> count(10, 0);

        for (long long i = 0; i < n; i++)
            count[(v[i] / exp) % 10]++;

        for (long long i = 1; i < 10; i++)
            count[i] += count[i - 1];

        for (long long i = n - 1; i >= 0; i--)
        {
            output[count[(v[i] / exp) % 10] - 1] = v[i];
            count[(v[i] / exp) % 10]--;
        }

        for (long long i = 0; i < n; i++)
            v[i] = output[i];

        exp *= 10;
    }
}

void RadixSortBase2pow16(vector<long long> &v, long long n, long long maxim)
{
    vector<long long> output(n);

    const long long BASE = 65536;

    long long exp = 1;

    while (maxim / exp > 0)
    {
        vector<long long> count(BASE, 0);

        for (long long i = 0; i < n; i++)
            count[(v[i] / exp) % BASE]++;

        for (long long i = 1; i < BASE; i++)
            count[i] += count[i - 1];

        for (long long i = n - 1; i >= 0; i--)
        {
            output[count[(v[i] / exp) % BASE] - 1] = v[i];
            count[(v[i] / exp) % BASE]--;
        }

        for (long long i = 0; i < n; i++)
            v[i] = output[i];

        exp *= BASE;
    }
}

void MergeSort(vector<long long> &v, long long n) {
    vector<long long> aux(n);

    for (long long width = 1; width < n; width *= 2) {
        for (long long i = 0; i < n; i += 2 * width) {
            long long left = i;
            long long mid = min(i + width, n);
            long long right = min(i + 2 * width, n);
            
            long long i1 = left, i2 = mid, j = left;
            
            while (i1 < mid && i2 < right) {
                if (v[i1] <= v[i2]) {
                    aux[j++] = v[i1++];
                } else {
                    aux[j++] = v[i2++];
                }
            }
            
            while (i1 < mid) {
                aux[j++] = v[i1++];
            }
            
            while (i2 < right) {
                aux[j++] = v[i2++];
            }
            
            for (long long k = left; k < right; k++) {
                v[k] = aux[k];
            }
        }
    }
}

int main()
{
    int testCases;
    fin >> testCases;

    for (int t = 1; t <= testCases; t++)
    {
        long long n, maxim;
        fin >> n >> maxim;

        vector<long long> aux(n);
        srand(time(0) + t);

        for(long long i = 0; i < n; i++) {
            aux[i] = rand() % maxim + 1;
        }

        vector<long long>v = aux;
        
        clock_t begin, end;
        double elapsed_seconds;

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

    }

}

