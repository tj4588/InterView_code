#include "stdio.h"
/*
 * Is the number prime?
 * Args : int N = integer 0 - 2^16
 * return : 0 if not prime
 *          1 if prime
 */
int isPrime (int N)
{
   int retVal = 1;
   for (int i = 2; i < N-1; i++)
   {
     if ((N % i) == 0)
     {
       retVal = 0;
       return retVal;
     }
   }
  return retVal;
}

/*
 * Fibonacci numbers. 0,1,1,2,3,5,8..
 * 0,1,1 : are special case in our requirement.
 * divisible by 15 FizzBuzz
 * divisible by 3 Buzz
 * div by 5 Fizz
 * prime BuzzFizz
 * else print number
 */
void fibSeries(int N)
{
  int a[N];
  if (N == 0)
  {
    printf("0\n");
    return;
  }
  if (N == 1)
  {
    printf("0\n1\n");
    return;
  }
  if (N==2)
  {
    printf("0\n1\n1\n");
    return;
  }
  a[0] = 0;
  a[1] = 1;
  a[2] = 1;
  printf("0\n1\n1\n"); // 0 and 1 are not prime
  for(int i=3; i<(N); i++)
  {
    a[i] = a[i-1] + a[i-2];
    
    if (a[i] % 15 == 0)
      printf("FizzBuzz\n");
    else if (a[i] % 3 == 0)
      printf("Buzz\n");
    else if (a[i] % 5 == 0)
      printf("Fizz\n");
    else if ( isPrime(a[i]))
      printf("BuzzFizz\n");
    else
      printf("%d\n", a[i]);
  }
}

int main ()
{
  int N;
  printf("Enter an integer\n");
  scanf("%d", &N);
  fibSeries(N);
  return 0;
}
             
    
