#include <stdio.h>

int sum(int n);

int main(void)
{
  int n;
  printf("请输入n：\n");
  scanf("%d", &n);
  printf("1+2+3+...+(n-1)+n = %d\n", sum(n));
  return 0;
}

int sum(int n)
{
  int result = 0;
  for(; n>0; n--)
  {
    result += n;
  }
  return result;
}
