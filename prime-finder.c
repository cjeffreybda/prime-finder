#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

unsigned long long fastPowerMod(unsigned long long a, unsigned long long b, unsigned long long mod)
{
  unsigned long long orig = b;
  unsigned long long carry = 1;
  unsigned long long ret = 1;
  unsigned long long places = floor(log(b) / log(2)) + 1;

  for (int i = 0; i <= places; i ++)
  {
    carry = (carry * carry) % mod;

    if (i == 0)
    {
      carry = a % mod;
    }

    if (b & 1)
    {
      ret *= carry;
      ret %= mod;
    }

    b = b >> 1;
  }
  ret %= mod;

  return ret;
}

bool witness(unsigned long long n, int w)
{
  unsigned long long d = n - 1;

  int m = 0;
  while (true)
  {
    if (d & 1)
    {
      break;
    }

    d = d >> 1;
    m ++;
  }

  unsigned long long test = fastPowerMod(w, d, n);

  if (test == 1 || test == n - 1)
  {
    return true;
  }

  for (int r = 1; r < m; r ++)
  {
    test *= test;
    test %= n;

    if (test == n - 1)
    {
      return true;
    }
  }
  
  return false;
}

bool isPrime(unsigned long long n)
{
  if (n < 1373653) // 2, 3
  {
    return (witness(n, 2) && witness(n, 3));
  }
  else if (n < 25326001) // 2, 3, 5
  {
    return (witness(n, 2) && witness(n, 3) && witness(n, 5));
  }
  else if (n < 4759123141) // 2, 7, 61
  {
    return (witness(n, 2) && witness(n, 7) && witness(n, 61));
  }
  else if (n < 1122004669633) // 2, 13, 23, 1662803
  {
    return (witness(n, 2) && witness(n, 13) && witness(n, 23) && witness(n, 1662803));
  }
  else
  {
    printf("Outside range");
    return false;
  }
}

int main()
{
  int primesFound = 2;

  //clock_t start, end;
  //double cpu_time_used;

  struct timeval tv;
  mingw_gettimeofday(&tv,NULL);
  long startTime = tv.tv_usec;
      
  //start = clock();

  int lastFound = 0;

  for (unsigned long long i = 1000000000 - 1; i >= 5; i -= 2)
  {
    // int thisIsPrime = isPrime(i);

    if (isPrime(i) == 1)
    {
      //end = clock();
      //cpu_time_used = ((double) (end - start));
      mingw_gettimeofday(&tv,NULL);
      long endTime = tv.tv_usec;

      long deltaTime = endTime - startTime;

      printf("\nLargest prime under 1B: %d (%d us)", i, deltaTime);
      break;
    }

    // printf("%d is prime? %d (%d found)\n", i, thisIsPrime, primesFound);
  }

  

  return 0;
}