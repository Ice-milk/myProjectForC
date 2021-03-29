#include <stdio.h>
#include <stdlib.h>

#define MAX 1024

int main(void)
{
    FILE *fp1;
    FILE *fp2;
    char str[MAX];

    if((fp1 = fopen("../temp/text.txt", "r")) == NULL)
    {
        fprintf(stderr, "文件打开失败\n");
        exit(-1);
    }
    if((fopen("../temp/text_copy.txt", "w")) == NULL)
    {
        fprintf(stderr, "文件打开失败\n");
        exit(-1);
    }

    while(!feof(fp1))
    {
        fgets(str, MAX, fp1);
        fputs(str, fp2);
    }
    fclose(fp1);
    fclose(fp2);

    return 0;
}