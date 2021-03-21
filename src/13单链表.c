/*
 * 用结构体实现一个单链表，存放一串数字。
 * 注意指针的使用，记住一点，在main函数中的变量，需要在子函数中操作并改变，子函数中一定要通过指针来操作。
 * 例如在子函数中释放main函数中nums结构的内存，就需要用main函数中nums指针的地址来操作。
 * */
#include <stdio.h>
#include <stdlib.h>

struct Link
{
  int count;
  int num;
  struct Link *next;
};

// 增
//录入数据，以数据元素为单位，头插法或尾插法录入
void input(struct Link *);
void add_num_h(struct Link **);
void add_num_t(struct Link **);
// 插入数据

// 改

// 删

// 查，输入数据，查询含有相同数据项的所有数据元素并返回其指针
struct Link *search_num(int, struct Link *);

/*输出*/
// 打印某一个数据元素
void print_num(struct Link *);
// 打印整个数据结构中的所有元素
void print_nums(struct Link *);

/*释放内存*/
void release(struct Link **);

// 输入数据
void input(struct Link *new_num)
{
  static int count = 0;
  new_num->count = count;
  count++;
  printf("请输入要存放的数字：\n");
  printf("num = ");
  scanf("%d", &(new_num->num));
  //丢弃一个回车符
  getchar();
}

// 头插法
void add_num_h(struct Link **head)
{
  struct Link *new_num = NULL, *temp = NULL; // 新建链表元素和缓存

  // 新建的数据不能放在栈空间，要存放在堆空间，否则函数结束值就丢失了
  new_num = (struct Link *)malloc(sizeof(struct Link));
  if (NULL == new_num)
  {
    printf("内存分配失败，按任意键程序退出...");
    getchar();
    exit(-1);
  }

  //输入数据
  input(new_num);

  if (NULL == *head)
  {
    *head = new_num;
    new_num->next = NULL;
  }
  else 
  {
    // temp = *head;
    // *head = new_num;
    // new_num->next = temp;
    new_num->next = *head;
    *head = new_num;
  }
}

// 尾插法
void add_num_t(struct Link **nums)
{
  struct Link *new_num = NULL;
  static struct Link *tail = NULL;
  new_num = (struct Link *)malloc(sizeof(struct Link));
  if(NULL == new_num)
  {
    printf("内存分配失败，按任意键退出...\n");
    getchar();
    exit(-1);
  }

  input(new_num);

  if(NULL == *nums)
  {
    *nums = new_num;
    new_num->next = NULL;
  }
  else
  {
     tail->next = new_num;
     new_num->next = NULL;
  }
  tail = new_num;
};

struct Link *search_num(int key, struct Link *nums)
{
  struct Link *temp = nums;
  while(NULL != temp)
  {
    if(temp->count == key || temp->num == key)
    {
      return temp;
    }
    temp = temp->next;
  }
  
  printf("没有对应的信息\n");
  return NULL;
}

// 输出数据
void print_nums(struct Link *nums)
{
  struct Link *temp = nums;
  while(temp != NULL)
  {
    printf("%d : %d\n", temp->count, temp->num);
    temp = temp->next;
  }
}

// 释放内存
void release(struct Link **nums)
{
  struct Link *temp = NULL;
  while(*nums != NULL)
  {
    temp = *nums;
    *nums = (*nums)->next;// 对地址赋值，操作地址本身
    free(temp);
  }
}

int main(void)
{
  struct Link *nums = NULL;
  while(1)
  {
    printf("是否需要添加新的元素？y or n\n");
    char c = getchar();
    // 丢弃一个回车符
    getchar();
    if(c == 'y' || c == 'Y')
    {
      // 因为函数中要修改的是head指针本身的值，所以需要传head指针的地址
      // add_num_h(&nums);
      add_num_t(&nums);
    }
    else if(c == 'n' || c == 'N')
    {
      break;
    }
    else
    {
      printf("请输入y或者n\n");
    }
  }

  int key;
  struct Link *search = nums;
  printf("输入查询的值：\n");
  scanf("%d", &key);
  getchar();
  while(NULL != (search = search_num(key, search)))
  {
    printf("查询到的信息为：\n %d : %d", search->count, search->num);
    search = search->next;
  }

  while(1)
  {
    printf("是否需要打印链表内容？y ro n\n");
    char c = getchar();
    // 丢弃一个回车符
    getchar();
    if(c == 'y' || c == 'Y')
    {
      print_nums(nums);
    }
    else if(c == 'n' || c== 'N')
    {
      break;
    }
    else
    {
      printf("请输入y或者n\n");
    }
  }
  // 因为释放内存需要操作nums地址本身，所以还是要传入nums指针的地址
  release(&nums);

  return 0;
}
