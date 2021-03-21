#include <stdio.h>

void quick_sort(int* array, int left, int right);

void quick_sort(int* array, int left, int right)
{
  int i = left, j = right;
  int temp;
  int pivot;

  pivot = array[(left + right) / 2];
  while (i <= j)
  {
    // 从左到右找到大于等于基准点的元素
    while (array[i] < pivot)
    {
      i++;
    }
    // 从右到左找到小于等于基准点的元素
    while (array[j] > pivot)
    {
      j--;
    }
    // 当i == j时，只有一种情况，就是
    // 中间的数字pivot排序后位置不变，此时直接跳过这个数字排序即可
    if (i == j)
    {
      i++;
      j--;
    }
    if (i < j)
    {
      temp = array[i];
      array[i] = array[j];
      array[j] = temp;
      i++;
      j--;
    }
  }
  if (j > left)
  {
    quick_sort(array, left, j);
  }
  if (i < right)
  {
    quick_sort(array, i, right);
  }
}

int main(void)
{
  // 待排序的数组
  int array[] = {9, 0, 4, 4, 3, 6, 7, 2, 8, 1, 5, 10, 5};
  int length;

  length = sizeof(array) / sizeof(array[0]); 
  quick_sort(array, 0, length - 1);

  printf("排序后的结果：\n");
  for(int i=0; i<length; i++)
  {
    printf("%d ", array[i]);
  }
  putchar('\n');

  return 0;
}
