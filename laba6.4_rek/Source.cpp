
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void Input(double a[], int n, int i = 0) // введення масиву
{
    if (i >= n)
        return;

    cin >> a[i];

    Input(a, n, i + 1);
}

void Print(const double a[], int n, int i = 0) // виведення масиву
{
    if (i >= n)
    {
        cout << endl;
        return;
    }

    cout << setw(10) << fixed << setprecision(2) << a[i];

    Print(a, n, i + 1);
}

int Max(const double a[], int n, int i = 1, int index = 0) // пошук індексу максимального за модулем елемента
{
    if (i >= n)
        return index;

    if (abs(a[i]) > abs(a[index]))
    {
        index = i;
    }

    return Max(a, n, i + 1, index);
}

int Find(const double a[], int n, int i = 0) // пошук першого додатного елемента
{
    if (i >= n)
        return -1; // якщо не нашли

    if (a[i] > 0) // перше додатнє
        return i;

    return Find(a, n, i + 1);
}

double Add(const double a[], int n, int i) // додавання елементів
{
    if (i >= n)
        return 0;

    return a[i] + Add(a, n, i + 1);
}

double Sum(const double a[], int n) // сума елементів після першого додатного
{
    int index = Find(a, n); // знаходим перше додатне

    if (index == -1) // якщо немає
    {
        return 0;
    }

    return Add(a, n, index + 1);
}

bool Check(double x, int low, int high) // перевірка цілої частини числа на належність інтервалу
{
    int c = (int)x; // x в ціле число

    return c >= low && c <= high;
}

void Move(const double a[], double b[], int n, int low, int high, bool selected, int& k, int i = 0) // перенесення елементів 
{
    if (i >= n)
        return;

    if (Check(a[i], low, high) == selected) // перевірка чи переносити число , які входять в інтервал і які не входять
    {
        b[k] = a[i]; // переносим число в б
        k++;
    }

    Move(a, b, n, low, high, selected, k, i + 1);
}

void Copy(double a[], const double b[], int n, int i = 0) // копірування з б в а
{
    if (i >= n)
        return;

    a[i] = b[i];

    Copy(a, b, n, i + 1);
}

void Change(double a[], int n, int low, int high) // переставляння елементів масиву
{
    double* b = new double[n]; // // спочатку записать потрібний рядок в б, а потім в а
    int k = 0;

    Move(a, b, n, low, high, true, k); // переносим числа які підходять

    Move(a, b, n, low, high, false, k) ;// переносим всі інші числа які не підходять до інтервалу

    Copy(a, b, n); // копірування з б в а

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
    Input(a, n);

    cout << "Original array:" << endl;
    Print(a, n);

    cout << "Max abs index = " << Max(a, n) << endl;

    cout << "Sum after first positive = " << Sum(a, n) << endl;

    Change(a, n, low, high);

    cout << "Modified array:" << endl;
    Print(a, n);

    delete[] a;

    return 0;
}
