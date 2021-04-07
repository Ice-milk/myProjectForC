#include <stdio.h>

unsigned long long factorial(int);

unsigned long long factorial(int num)
{
  // 基线条件
  if (num == 1)
  {
    return 1;
  }
  // 递归条件
  return num * factorial(num-1); 
}

int main(void)
{
  int n;
  printf("请输入阶乘n！中n的值：\n");
  input:
  scanf("%d", &n);
  if (n<1)
  {
    printf("请输入一个正整数：\n");
    goto input;
  }
  printf("%d！= %llu\n", n, factorial(n));
  printf("sizeof(long) = %zd\n", sizeof(long));
  printf("sizeof(long long) = %zd\n", sizeof(long long));

  return 0;
}
