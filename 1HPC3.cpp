#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;
int main()
{
  // Declare variables
  int n;
  // Ask the user to input the size of the array
  cout << "Enter the number of elements in the array: ";
  cin >> n;
  // Declare a vector of integers
  vector<int> arr(n);
  // Ask the user to input the elements of the array
  cout << "Enter " << n << " elements:" << endl;
  for (int i = 0; i < n; ++i)
  {
    cin >> arr[i];
  }
  // Variables for the results
  int min_val, max_val, sum_val;
  double average_val;
// Parallel reduction to find Min, Max, Sum, and Average
#pragma omp parallel
  {
// Initialize local variables for the reduction
#pragma omp single
    {
      min_val = arr[0];
      max_val = arr[0];
      sum_val = 0;
    }
// Parallel reduction block
#pragma omp for reduction(min : min_val) reduction(max : max_val) reduction(+ : sum_val)
    for (int i = 0; i < n; i++)
    {
      // Perform Min, Max, and Sum operations
      sum_val += arr[i]; // Sum
      if (arr[i] < min_val)
        min_val = arr[i]; // Min
      if (arr[i] > max_val)
        max_val = arr[i]; // Max
    }
// Compute average after reduction
#pragma omp single
    {
      average_val = static_cast<double>(sum_val) / n;
    }
  }
  // Print the results
  cout << "Min: " << min_val << endl;
  cout << "Max: " << max_val << endl;
  cout << "Sum: " << sum_val << endl;
  cout << "Average: " << average_val << endl;
  return 0;
}
// gcc -o filename -fopenmp filename.cpp
