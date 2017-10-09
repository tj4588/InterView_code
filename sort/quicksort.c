#include <iostream>
#include "stdio.h"



void swap(int *a, int *b)
{
  int temp;
  
  temp = *a;
  *a = *b;
  *b = temp;
}

int partition (int *arr, int l, int h)
{
  //std::cout << "test" << std::endl;
  int part = arr[h];
  int i = l - 1;
  
  for (int j = l; j < h - 1; j++)
  {
    if (arr[j] <= part)
    {
      i++;
      swap(&arr[i], &arr[j]);
    }
  }
  i = i+1;
  swap(&arr[h], &arr[i]);
  return(i);
}

void quickSort (int *arr, int l, int h)
{
  int pi;
  if (l < h)
  {
    pi = partition(arr,  l,  h);
    
    quickSort(arr,  l,  pi - 1);
    quickSort(arr,  pi + 1,  h);
  }
 // return;
}


int main()
{
  int array[10]={10,4,5,7,9, 15, 78, 2,1, 3};
  
  quickSort(array, 0, 10);
  
  for (int i = 0; i < 10; i++)
   printf("%d\n", array[i]);
}
