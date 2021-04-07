#include <stdio.h>

int main(void)
{
  char array[2][17] = {
      "Hello, world!",
      "Hello, computer!"};
  char(*p)[17] = array;

  printf("%s\n%s\n", *p, *(p + 1));
  printf("array        = %p\n", array);
  printf("array[0]     = %p\n", array[0]);
  printf("&array[0][0] = %p\n", &array[0][0]);
  printf("p            = %p\n", p);

  printf("\n");

  printf("array[1]     = \"%s\" %p\n", array[1], array[1]);
  printf("p+1          = \"%s\" %p\n", *(p + 1), p + 1);
  printf("&array[1][7] = %c %p\n", array[1][7], &array[1][7]);
  printf("*(p+1)+7     = %c %p\n", *(*(p + 1) + 7), *(p + 1) + 7);

  printf("结论：数组是顺序存储结构，多维数组维度之间通过计算获得地址，\n"
         "而不是通过指针链接地址。\n");
  return 0;
}
