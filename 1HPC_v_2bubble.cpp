
#include <iostream>
#include <omp.h>
#include <vector>
using namespace std;
void bubbleSort(vector<int> &arr, int n)
{
  bool swapped;
  for (int i = 0; i < n - 1; i++)
  {
    swapped = false;
// Parallelize the inner loop using OpenMP, but each thread works independently
#pragma omp parallel for shared(arr) reduction(|| : swapped)
    for (int j = 0; j < n - i - 1; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        // Swap elements
        int temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
        swapped = true;
      }
    }
    // If no two elements were swapped, array is sorted
    if (!swapped)
      break;
  }
}
int main()
{
  int n;
  cout << "Enter the number of elements: ";
  cin >> n;

  vector<int> arr(n);
  // Declare an array of size n
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
  bubbleSort(arr, n);
  cout << "Sorted array: ";
  for (int i = 0; i < n; i++)
  {
    cout << arr[i] << " ";
  }
  cout << endl;
  return 0;
}

