#include <stdio.h>

int count = 0; // 汉诺塔移动次数

// 汉诺塔解法递归函数，n表示汉诺塔的层数
// x表示要移动的塔位，y表示借助的塔位，z表示移动目的地塔位
void haloi(int n, char x, char y, char z);

void haloi(int n, char x, char y, char z)
{
  // 基线条件
  if (n == 1)
  {
    printf("%c --> %c\n", x, z); //将最上层圆盘移动到z
    count++;
  }
  // 递归条件
  else
  {
    // 要将n个圆盘从x借助y移动到z
    haloi(n-1, x, z, y); // 先将n-1个圆盘从x借助z移动到y
    printf("%c --> %c\n", x, z); // 将最下层圆盘移动到z
    haloi(n-1, y, x, z); // 再将这n-1个圆盘从y借助x移动到z
    count++;
  }
}

int main(void)
{
  int n;

  printf("请输入汉诺塔的层数：\n");
input:
  scanf("%d", &n);
  if (n<1)
  {
    printf("请输入一个正整数：\n");
    goto input;
  }
  haloi(n, 'X', 'Y', 'Z');
  printf("共%d步\n", count);
  return 0;
}
