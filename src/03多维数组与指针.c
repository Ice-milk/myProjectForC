#include <stdio.h>

int main(void)
{
  int array[2][3] = {{1,2,3},{4,5,6}};
  int (*p)[3] = array;

  printf("array = %p\n", array);
  printf("array[0] = %p\n", array[0]);
  printf("&array[0][0] = %p\n", &array[0][0]);
  printf("p = %p\n", p);
  printf("*p = %p\n", *p);

  printf("\n");

  printf("array[1] = %p\n", array[1]);
  printf("&array[0][1] = %p\n", &array[0][1]);
  printf("p+1 = %p\n", p+1);
  printf("*p+1 = %p\n", *p+1);

  printf("结论：数组是顺序存储结构，多维数组维度之间通过计算获得地址，\n"
      "而不是通过指针链接地址。\n");
  return 0;
}
