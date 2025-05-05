#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;

void merge(vector<int> &arr, int left, int mid, int right)
{
  int n1 = mid - left + 1;
  int n2 = right - mid;
  // Create temporary arrays
  vector<int> leftArr(n1), rightArr(n2);
  // Copy data
  for (int i = 0; i < n1; i++)
    leftArr[i] = arr[left + i];
  for (int i = 0; i < n2; i++)
    rightArr[i] = arr[mid + 1 + i];
  // Merge
  int i = 0, j = 0, k = left;
  while (i < n1 && j < n2)
  {
    if (leftArr[i] <= rightArr[j])
    {
      arr[k++] = leftArr[i++];
    }
    else
    {
      arr[k++] = rightArr[j++];
    }
  }
  while (i < n1)
  {
    arr[k++] = leftArr[i++];
  }
  while (j < n2)
  {
    arr[k++] = rightArr[j++];
  }
}

void mergeSort(vector<int> &arr, int left, int right)
{
  if (left < right)
  {
    int mid = left + (right - left) / 2;
// Parallelize recursive calls
#pragma omp parallel sections
    {
#pragma omp section
      mergeSort(arr, left, mid);

#pragma omp section
      mergeSort(arr, mid + 1, right);
    }
    merge(arr, left, mid, right);
  }
}


int main()
{
  int n;
  cout << "Enter the number of elements: ";
  cin >> n;

  vector<int> arr(n); // vector of size n

  cout << "Enter the elements of the array: ";
  for (int i = 0; i < n; i++)
  {
    cin >> arr[i];
  }

  cout << "Unsorted array: ";
  for (int i = 0; i < n; i++)
  {
    cout << arr[i] << " ";
  }
  cout << endl;

  mergeSort(arr, 0, n - 1);

  cout << "Sorted array: ";
  for (int i = 0; i < n; i++)
  {
    cout << arr[i] << " ";
  }
  cout << endl;}
