#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
* struct tm
* {
*   int tm_sec;     秒，范围为 0~59，60 的话表示闰秒
*   int tm_min;     分，范围是 0~59
*   int tm_hour;    时，范围是 0~23
*   int tm_mday;    一个月中的第几天，范围是 1~31
*   int tm_mon;     一年中的第几个月，范围是 0~11
*   int tm_year;    自 1900 年往后的第几年
*   int tm_wday;    星期几，自星期天开始计算，范围是 0~6
*   int tm_yday;    一年中的第几天，范围是 0~365
*   int tm_isdst;   指定日光节约时间是否生效，正数表示生效，
*                   0 表示不生效，负数表示该信息不可用
* };
*
*/

int main(void)
{
    FILE *fp;
    struct tm *pt;
    time_t t;

    time(&t);
    pt = localtime(&t);

    if((fp = fopen("../temp/localtime.txt","w")) == NULL)
    {
        fprintf(stderr, "文件打开失败\n");
        exit(-1);
    }
    fprintf(fp, "%d-%d-%d %d:%d:%d", 1900 + pt->tm_year, 1 + pt->tm_mon, pt->tm_mday, pt->tm_hour, pt->tm_min, pt->tm_sec);
    fclose(fp);
    
    int year, month, day, hour, min, sec;
    if((fp = fopen("../temp/localtime.txt","r")) == NULL)
    {
        fprintf(stderr, "文件打开失败\n");
        exit(-1);
    }
    fscanf(fp,"%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &min, &sec);
    printf("%d年%d月%d日 %d:%d:%d\n", year, month, day, hour, min, sec);
    fclose(fp);

    return 0;
}