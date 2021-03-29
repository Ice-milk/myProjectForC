/**
 * @file 14.2函数指针计算器typedef.c
 * @author Nie Yan
 * @brief 
 * typedef可以简化复杂的表达式，特别是这种函数指针，会让函数更容易理解
 * @version 0.1
 * @date 2021-03-28
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>

typedef int (*P_FUNC)(int, int);

// 方法：加
int add(int, int);
// 方法：减
int sub(int, int);
// 使用方法计算两个数的值，输入函数指针和两个数，输出计算结果。
int calc(P_FUNC, int, int);
// 根据输入的字符判断使用的方法，返回函数指针
P_FUNC select(char);

int add(int a, int b)
{
  return a+b;
}

int sub(int a, int b)
{
  return a-b;
}

int calc(P_FUNC fp, int a, int b)
{
  return (*fp)(a, b);
}

P_FUNC select(char op)
{
  switch(op)
  {
    case '+':
      return add;
    case '-':
      return sub;
    default:
      return NULL;
  }
}

int main(void)
{
  int num1, num2;
  char op;
  P_FUNC fp;

  printf("请输入一个算式，例如1+2:\n");
  scanf("%d%c%d", &num1, &op, &num2);

  fp = select(op);
  if (fp == NULL)
  {
    printf("不支持该运算符\n");
    return -1;
  }
  printf("%d %c %d = %d\n", num1, op , num2, calc(fp, num1, num2));

  return 0;
}
