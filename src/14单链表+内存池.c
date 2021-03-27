/**
 * @file 14单链表+内存池.c
 * @author Nie Yan
 * @brief 
 * 1. 在13单链表的基础上加入内存池
 *    内存池也是一个链表，它的目的是防止程序运行中频繁申请和释放空间造成内存空间碎片化，
 *    通过在程序内部循环使用一部分内存空间，来减少内存的申请与释放。
 * 2. 修改了单链表的交互方式，采用字符命令；修改了读取单个字符的方式，
 *    代码中出现了两种安全读取单个字符的方法，需要理解记忆,
 *    主要理解丢弃输入缓冲区不必要的字符的方法
 * @version 0.1
 * @date 2021-03-27(creat)
 * @date 2021-03-28(last-chage)
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>

// 内存池的容量(以内存块为单位)
#define MAX 2
// 为了方便验证而设置了较小的值，在实际中内存池需要根具实际情况设计大小

/**
 * @brief 链表数据结构
 * 
 */
struct Link
{
  // 序号
  int id;
  // 数据
  int num;
  // 指向下一个链表元素
  struct Link *next;
};

// 内存池
struct Link *pool = NULL;
int count = 0; // 内存池中的内存块数量

void input_data(struct Link *);
struct Link *pull_mem(void);
void add_element_h(struct Link **);
void add_element_t(struct Link **);
struct Link *search_item(int, struct Link *);
void insert_element(int, struct Link **);
void change_item(int, struct Link *);
void push_mem(struct Link **);
void delete_element(int, struct Link **);
void print_element(struct Link *);
void print_all(struct Link *);
void print_help(void);
void release(struct Link **);
void release_pool(void);

/**
 * @brief 输入数据项
 * 
 * @param new_num 新的链表元素
 */
void input_data(struct Link *new_num)
{
  static int id = 1;
  if (new_num->id == 0)
  {
    new_num->id = id;
    id++;
  }
  printf("请输入要存放的数字：\n");
  printf("num = ");
  // 安全读取
  scanf("%d", &(new_num->num));
  while (getchar() != '\n')
    ; // 丢弃缓冲区的回车符
}

/**
 * @brief 分配内存空间。判断内存池中是否有块空间，有则取出作为存放新的链表元素的空间，没有就用calloc新申请
 * 
 * @return struct Link* 新分配的内存空间指针
 */
struct Link *pull_mem(void)
{
  struct Link *new_mem = NULL;
  if (pool != NULL)
  {
    new_mem = pool;
    pool = pool->next;
    count--;
  }
  else
  {
    // 新建的数据不能放在栈空间，要存放在堆空间，否则函数结束值就丢失了
    new_mem = (struct Link *)calloc(1, sizeof(struct Link)); // 使用calloc分配内存并初始化为0
    if (NULL == new_mem)
    {
      printf("内存分配失败，按任意键程序退出...");
      getchar();
      exit(-1);
    }
  }
  return new_mem;
}

/**
 * @brief 头插法添加链表元素
 * 
 * @param head 链表头指针的地址
 */
void add_element_h(struct Link **head)
{
  /**
   * @param new_num 新建链表元素和缓存
   * @param temp 链表指针缓存
   */
  struct Link *new_num = NULL, *temp = NULL;

  // 分配内存空间
  new_num = pull_mem();

  //输入数据
  input_data(new_num);
  print_element(new_num);

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

/**
 * @brief 尾插法添加元素
 * 
 * @param head 链表头指针的地址
 */
void add_element_t(struct Link **head)
{
  struct Link *new_num = NULL;
  static struct Link *tail = NULL; // 用静态变量记录链表尾部
  if (*head != NULL)
  {
    struct Link *temp = *head;
    while (temp->next != NULL)
    {
      temp = temp->next;
    }
    tail = temp;
  }

  // 分配内存空间
  new_num = pull_mem();

  input_data(new_num);
  print_element(new_num);

  if (NULL == *head)
  {
    *head = new_num;
  }
  else
  {
    tail->next = new_num;
  }
  new_num->next = NULL;
  tail = new_num; // 尾指针始终指向链表尾部
};

/**
 * @brief 输入数据，查询含有相同数据项的所有数据元素并返回其指针
 * @param key 查询的数据
 * @param head 链表头指针
 * @return struct Link* 返回查询到的链表元素指针
 */
struct Link *search_item(int key, struct Link *head)
{
  struct Link *temp = head;
  while (NULL != temp)
  {
    if (temp->id == key || temp->num == key)
    {
      return temp;
    }
    temp = temp->next;
  }

  printf("完毕\n");
  return NULL;
}

/**
 * @brief 在id号前插入元素
 * 
 * @param id 链表元素序号
 * @param head 链表头指针
 */
void insert_element(int id, struct Link **head)
{
  struct Link *prev = NULL;
  struct Link *curr = *head;
  struct Link *new;

  while (NULL != curr && curr->id != id)
  {
    prev = curr;
    curr = curr->next;
  }

  // 分配内存空间
  new = pull_mem();

  input_data(new);

  if (curr == NULL)
  {
    printf("没有对应id的元素，将在链表末尾插入新的值\n");
  }

  if (prev == NULL)
  {
    *head = new;
  }
  else
  {
    prev->next = new;
  }
  new->next = curr;

  printf("插入成功！新插入元素为：\nprev:");
  print_element(prev);
  printf("new :");
  print_element(new);
  printf("curr:");
  print_element(curr);
}

/**
 * @brief 改变某个元素的值
 * 
 * @param id 元素id
 * @param head 链表头指针
 */
void change_item(int id, struct Link *head)
{
  struct Link *temp = head;
  while (temp != NULL && temp->id != id)
  {
    temp = temp->next;
  }
  if (temp == NULL)
  {
    printf("没有找到对应的元素\n");
    return;
  }
  printf("原元素的值为：\n");
  print_element(temp);
  printf("请输入新的值：\n");
  input_data(temp);
  printf("修改完毕，元素已改为：");
  print_element(temp);
}

/**
 * @brief 回收内存。判断内存池是否有空间，有就使用头插法将删除的元素放入内存池，没有就free内存
 * 
 * @param curr 要回收的内存的指针的指针，因为可能要释放内存指针本身，所以要操作其地址
 */
void push_mem(struct Link **curr)
{
  struct Link *temp = *curr;
  // 将curr的id初始化为0
  temp->id = 0;
  if (count < MAX)
  {
    if (pool == NULL)
    {
      pool = temp;
      temp->next = NULL;
    }
    else
    {
      temp->next = pool;
      pool = temp;
    }
    count++;
    printf("删除成功，放入内存池\n");
  }
  else
  {
    free(*curr);
    printf("删除成功，释放内存\n");
  }
}

/**
 * @brief 删除id对应的元素
 * 
 * @param id 元素id
 * @param head 链表首地址
 */
void delete_element(int id, struct Link **head)
{
  struct Link *prev = NULL;
  struct Link *curr = *head;

  while (curr != NULL && curr->id != id)
  {
    prev = curr;
    curr = curr->next;
  }

  if (curr == NULL)
  {
    printf("没有找到id对应的数据\n");
    return;
  }

  if (prev == NULL)
  {
    *head = curr->next;
  }
  else
  {
    prev->next = curr->next;
  }

  push_mem(&curr);
}

/**
 * @brief 打印单个元素内容
 * 
 * @param element 链表某个元素的指针
 */
void print_element(struct Link *element)
{
  if (NULL == element)
  {
    printf("NULL\n");
  }
  else
  {
    printf("%p: {%3d : %-6d} -> %p \n", element, element->id, element->num, element->next);
  }
}

/**
 * @brief 输出整个链表
 * 
 * @param head 链表头指针
 */
void print_all(struct Link *head)
{
  struct Link *temp = head;
  while (temp != NULL)
  {
    print_element(temp);
    temp = temp->next;
  }
}

/**
 * @brief 打印命令帮助信息
 * 
 */
void print_help(void)
{
  printf("\
          a 添加新元素（头插法）\n\
          t 添加新元素（尾插法）\n\
          i 插入元素\n\
          c 更改某个元素的数据项\n\
          d 删除某个元素\n\
          s 查询数据项\n\
          p 打印整个链表\n\
          h 查看帮助\n\
          q 退出程序\n");
}

/**
 * @brief 释放整个链表内存
 * 
 * @param head 链表头指针的地址
 */
void release(struct Link **head)
{
  struct Link *temp = NULL;
  while (*head != NULL)
  {
    temp = (*head)->next; // ->优先级比*高，所以要括起来
    free(*head);
    *head = temp; // 对地址赋值，操作main函数中地址本身
  }
}

/**
 * @brief 释放内存池空间
 * 
 */
void release_pool(void)
{
  struct Link *temp = NULL;
  while (pool != NULL)
  {
    temp = pool->next;
    free(pool);
    pool = temp;
  }
}

int main(void)
{
  struct Link *head = NULL; // @brief 链表头指针
  // 链表头指针不使用全局变量是因为全局变量容易被修改，不安全。
  while (1)
  {
    char com; // 命令
    printf("请输入功能对应字符:(h查看帮助)");
    // 读取单个字符最安全的方法，输入缓冲区会被清空，以免干扰后续输入
    scanf("%c", &com); // scanf只读取第一个字符，其他字符被留在缓冲区，包括换行符等
    while (getchar() != '\n')
      ; // 通过循环丢弃换行符及其之前的其他字符，以免影响后面输入

    switch (com)
    {
    // 帮助
    case 'h':
      print_help();
      break;
    // 退出程序
    case 'q':
      // 因为释放内存需要操作nums地址本身，所以还是要传入nums指针的地址
      release(&head);
      release_pool();
      return 0;
    // 头插法
    case 'a':
      while (1)
      {
        // 因为函数中要修改的是head指针本身的值，所以需要传head指针的地址
        add_element_h(&head);

        char c;
        printf("是否继续添加新的元素？(y or n):");
        // 这是另一种安全的读取单个字符的方法，但是如果循环条件太长就会比较繁琐
        do
        {
          c = getchar();
        } while ('y' != c && 'Y' != c && 'n' != c && 'N' != c);
        while (getchar() != '\n')
          ; // 丢弃缓冲区的回车符

        if (c == 'y' || c == 'Y')
        {
          continue;
        }
        else
        {
          break;
        }
      }
      break;

    // 尾插法
    case 't':
      while (1)
      {
        // 因为函数中要修改的是head指针本身的值，所以需要传head指针的地址
        add_element_t(&head);

        char c;
        printf("是否继续添加新的元素？(y or n):");
        do
        {
          c = getchar();
        } while ('y' != c && 'Y' != c && 'n' != c && 'N' != c);
        while (getchar() != '\n')
          ; // 丢弃缓冲区的回车符

        if (c == 'y' || c == 'Y')
        {
          continue;
        }
        else
        {
          break;
        }
      }
      break;

    // 插入数据
    case 'i':
      while (1)
      {
        int id;
        printf("在id位置前插入数据，请输入id：");
        scanf("%d", &id);
        getchar();
        insert_element(id, &head);

        char c;
        printf("是否继续插入元素？(y or n):");
        do
        {
          c = getchar();
        } while ('y' != c && 'Y' != c && 'n' != c && 'N' != c);
        while (getchar() != '\n')
          ; // 丢弃缓冲区的回车符

        if (c == 'y' || c == 'Y')
        {
          continue;
        }
        else
        {
          break;
        }
      }
      break;

    // 更改元素
    case 'c':
      while (1)
      {
        int id;
        printf("请输入要更改的元素id：");
        scanf("%d", &id);
        getchar();
        change_item(id, head);

        char c;
        printf("是否继续更改元素？(y or n):");
        do
        {
          c = getchar();
        } while ('y' != c && 'Y' != c && 'n' != c && 'N' != c);
        while (getchar() != '\n')
          ; // 丢弃缓冲区的回车符

        if (c == 'y' || c == 'Y')
        {
          continue;
        }
        else
        {
          break;
        }
      }

      break;

    // 删除元素
    case 'd':
      while (1)
      {
        int id;
        printf("请输入要删除的元素id：");
        scanf("%d", &id);
        getchar();
        delete_element(id, &head);

        char c;
        printf("是否继续删除元素？(y or n):");
        do
        {
          c = getchar();
        } while ('y' != c && 'Y' != c && 'n' != c && 'N' != c);
        while (getchar() != '\n')
          ; // 丢弃缓冲区的回车符

        if (c == 'y' || c == 'Y')
        {
          continue;
        }
        else
        {
          break;
        }
      }
      break;

    // 查询元素
    case 's':
      while (1)
      {
        int key; // 查询的值
        struct Link *search = head;
        printf("输入查询的值：\n");
        scanf("%d", &key);
        getchar();
        if (NULL == (search = search_item(key, search)))
        {
          printf("没有对应的信息\n");
        }
        else
        {
          printf("查询到的信息为：\n");
          print_element(search);
          search = search->next;
          while (NULL != (search = search_item(key, search)))
          {
            print_element(search);
            search = search->next;
          }
        }

        char c;
        printf("是否继续查询？(y or n):");
        do
        {
          c = getchar();
        } while ('y' != c && 'Y' != c && 'n' != c && 'N' != c);
        while (getchar() != '\n')
          ; // 丢弃缓冲区的回车符

        if (c == 'y' || c == 'Y')
        {
          continue;
        }
        else
        {
          break;
        }
      }
      break;

    // 打印整个链表
    case 'p':
      printf("打印链表：\n");
      print_all(head);
      printf("按Enter继续...");
      while (getchar() != '\n')
        ; // 暂停并丢弃缓冲区的回车符
      break;

    default:
      continue;
    }
  }

  return 0;
}
