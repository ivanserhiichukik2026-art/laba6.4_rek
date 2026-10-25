#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void readArray(double a[], int n, int i = 0)
{
    if (i >= n)
    {
        return;
    }

    cin >> a[i];

    readArray(a, n, i + 1);
}

void printArray(const double a[], int n, int i = 0)
{
    if (i >= n)
    {
        cout << endl;
        return;
    }

    cout << setw(10) << fixed
        << setprecision(2) << a[i];

    printArray(a, n, i + 1);
}

int maxAbsIndex(const double a[], int n, int i = 1, int index = 0)
{
    if (i >= n)
    {
        return index;
    }

    if (fabs(a[i]) > fabs(a[index]))
    {
        index = i;
    }

    return maxAbsIndex(a, n, i + 1, index);
}

int firstPositiveIndex(const double a[], int n, int i = 0)
{
    if (i >= n)
    {
        return -1;
    }

    if (a[i] > 0)
    {
        return i;
    }

    return firstPositiveIndex(a, n, i + 1);
}

double sumElements(const double a[], int n, int i)
{
    if (i >= n)
    {
        return 0;
    }

    return a[i] + sumElements(a, n, i + 1);
}

double sumAfterPositive(const double a[], int n)
{
    int index = firstPositiveIndex(a, n);

    if (index == -1)
    {
        return 0;
    }

    return sumElements(a, n, index + 1);
}

bool belongs(double x, int low, int high)
{
    int part = (int)x;

    return part >= low && part <= high;
}

void collectElements(const double a[], double b[], int n,
    int low, int high, bool selected,
    int& k, int i = 0)
{
    if (i >= n)
    {
        return;
    }

    if (belongs(a[i], low, high) == selected)
    {
        b[k] = a[i];
        k++;
    }

    collectElements(a, b, n, low, high, selected, k, i + 1);
}

void copyArray(double a[], const double b[], int n, int i = 0)
{
    if (i >= n)
    {
        return;
    }

    a[i] = b[i];

    copyArray(a, b, n, i + 1);
}

void rearrange(double a[], int n, int low, int high)
{
    double* b = new double[n];
    int k = 0;

    collectElements(a, b, n, low, high, true, k);
    collectElements(a, b, n, low, high, false, k);

    copyArray(a, b, n);

    delete[] b;
}

int main()
{
    int n;
    int low, high;

    cout << "Enter n: ";
    cin >> n;

    if (!cin || n <= 0)
    {
        return 1;
    }

    cout << "Enter a and b: ";
    cin >> low >> high;

    if (!cin || low > high)
    {
        return 1;
    }

    double* a = new double[n];

    cout << "Enter array elements:" << endl;
    readArray(a, n);

    cout << "Original array:" << endl;
    printArray(a, n);

    cout << "Max abs index = "
        << maxAbsIndex(a, n) << endl;

    cout << "Sum after first positive = "
        << sumAfterPositive(a, n) << endl;

    rearrange(a, n, low, high);

    cout << "Modified array:" << endl;
    printArray(a, n);

    delete[] a;

    return 0;
}