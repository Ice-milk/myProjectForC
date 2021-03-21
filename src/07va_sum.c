#include <stdio.h>
#include <stdarg.h>

int sum(int n, ...);

int main(void)
{
  printf("sum(3, 1, 2, 3)= %d\n", sum(3, 1, 2, 3));
  printf("sum(4, 1, 2, 3, 4) = %d\n", sum(4, 1, 2, 3, 4));
  return 0;
}

int sum(int n, ...)
{
  int result = 0;
  va_list vap;

  va_start(vap, n);
  for(int i = 0; i<n; i++)
  {
    result += va_arg(vap, int);
  }
  va_end(vap);

  return result;
}
