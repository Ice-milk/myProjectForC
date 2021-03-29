/******************************
** 测试本计算机的数据类型大小**
******************************/

#include <stdio.h>

int main()
{
  // C99为类型大小提供%zd转换说明
  int *p = NULL;
  printf("int:    %zd bytes\n", sizeof(int));
  printf("short:  %zd bytes\n", sizeof(short));
  printf("long:   %zd bytes\n", sizeof(long));
  printf("long long: %zd bytes\n", sizeof(long long));
  printf("float:  %zd bytes\n", sizeof(float));
  printf("double: %zd bytes\n", sizeof(double));
  printf("long double: %zd bytes\n", sizeof(long double));
  printf("char:   %zd bytes\n", sizeof(char));
  printf("*p:     %zd bytes\n", sizeof(p));
  return 0;
}
