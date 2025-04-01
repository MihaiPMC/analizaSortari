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
    vector<long long> output(n);

    for (long long width = 1; width < n; width *= 2) {
        for (long long i = 0; i < n; i += 2 * width) {
            long long left = i;
            long long mid = min(i + width, n);
            long long right = min(i + 2 * width, n);

            long long i1 = left, i2 = mid, j = left;

            while (i1 < mid && i2 < right) {
                if (v[i1] <= v[i2]) {
                    output[j++] = v[i1++];
                } else {
                    output[j++] = v[i2++];
                }
            }

            while (i1 < mid) {
                output[j++] = v[i1++];
            }

            while (i2 < right) {
                output[j++] = v[i2++];
            }

            for (long long k = left; k < right; k++) {
                v[k] = output[k];
            }
        }
    }
}

void ShellSort(vector<long long> &v, long long n)
{
    for (long long gap = n / 2; gap > 0; gap /= 2)
    {
        for (long long i = gap; i < n; i++)
        {
            long long temp = v[i];
            
            long long j;
            for (j = i; j >= gap && v[j - gap] > temp; j -= gap)
            {
                v[j] = v[j - gap];
            }
            
            v[j] = temp;
        }
    }
}

void CountSort(vector<long long> &v, long long n, long long maxim)
{
    vector<long long> count(maxim + 1, 0);
    vector<long long> output(n);

    for (long long i = 0; i < n; i++)
        count[v[i]]++;

    for (long long i = 1; i <= maxim; i++)
        count[i] += count[i - 1];

    for (long long i = n - 1; i >= 0; i--)
    {
        output[count[v[i]] - 1] = v[i];
        count[v[i]]--;
    }

    for (long long i = 0; i < n; i++)
        v[i] = output[i];
}

void heapify(vector<long long> &v, long long n, long long i) {
    long long largest = i;
    long long left = 2 * i + 1;
    long long right = 2 * i + 2;

    if (left < n && v[left] > v[largest])
        largest = left;

    if (right < n && v[right] > v[largest])
        largest = right;

    if (largest != i) {
        swap(v[i], v[largest]);
        heapify(v, n, largest);
    }
}

void HeapSort(vector<long long> &v, long long n)
{
    for (long long i = n / 2 - 1; i >= 0; i--)
        heapify(v, n, i);

    for (long long i = n - 1; i > 0; i--) {
        swap(v[0], v[i]);
        heapify(v, i, 0);
    }
}

void QuickSortMiddle(vector<long long> &v, int left, int right)
{
    if(left < right)
    {
        int m = (left + right) / 2;
        int aux = v[left];
        v[left] = v[m];
        v[m] = aux;
        int i = left , j = right, d = 0;
        while(i < j)
        {
            if(v[i] > v[j])
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
                d = 1 - d;
            }
            i += d;
            j -= 1 - d;
        }
        QuickSortMiddle(v, left , i - 1);
        QuickSortMiddle(v, i + 1 , right);
    }
}

void QuickSortMedian3(vector<long long> &v, int left, int right)
{
    if(left < right)
    {
        int m = (left + right) / 2;

        if(v[left] > v[m]) swap(v[left], v[m]);
        if(v[m] > v[right]) swap(v[m], v[right]);
        if(v[left] > v[m]) swap(v[left], v[m]);

        swap(v[left], v[m]);

        int i = left , j = right, d = 0;
        while(i < j)
        {
            if(v[i] > v[j])
            {
                swap(v[i], v[j]);
                d = 1 - d;
            }
            i += d;
            j -= 1 - d;
        }
        QuickSortMedian3(v, left , i - 1);
        QuickSortMedian3(v, i + 1 , right);
    }
}

void QuickSortMedian5(vector<long long> &v, int left, int right)
{
    if(left < right)
    {
        if (right - left >= 4) {
            int i1 = left;
            int i2 = left + (right - left) / 4;
            int i3 = (left + right) / 2;
            int i4 = right - (right - left) / 4;
            int i5 = right;

            vector<pair<long long, int>> samples = {
                {v[i1], i1}, {v[i2], i2}, {v[i3], i3}, {v[i4], i4}, {v[i5], i5}
            };
            sort(samples.begin(), samples.end());

            swap(v[left], v[samples[2].second]);
        } else {
            int m = (left + right) / 2;
            if(v[left] > v[m]) swap(v[left], v[m]);
            if(v[m] > v[right]) swap(v[m], v[right]);
            if(v[left] > v[m]) swap(v[left], v[m]);
            swap(v[left], v[m]);
        }

        int i = left , j = right, d = 0;
        while(i < j)
        {
            if(v[i] > v[j])
            {
                swap(v[i], v[j]);
                d = 1 - d;
            }
            i += d;
            j -= 1 - d;
        }
        QuickSortMedian5(v, left , i - 1);
        QuickSortMedian5(v, i + 1 , right);
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

        v = aux;
        //shell sort
        begin = clock();
        ShellSort(v, n);
        end = clock();
        elapsed_seconds = double(end - begin) / CLOCKS_PER_SEC;
        cout << "Time taken for Shell Sort in test case " << t << ": " << elapsed_seconds << " seconds" << endl;

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
    }

}

