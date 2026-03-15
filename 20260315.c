#include<stdio.h>

// 移动函数：增加空格分隔步骤，更易读
void move(char a, char b)
{
    printf("%c->%c ", a, b); // 末尾加空格分隔每一步
}

// 汉诺塔核心递归函数
// n：盘子数量，src：源柱，tmp：辅助柱，tgt：目标柱
void Hanoi(int n, char src, char tmp, char tgt)
{
    if(n == 1)
    {
        // 只有1个盘子时，直接从源柱移到目标柱
        move(src, tgt);
    }
    else
    {
        // 步骤1：把n-1个盘子从src移到tmp（借助tgt）
        Hanoi(n-1, src, tgt, tmp);
        // 步骤2：把第n个盘子从src移到tgt
        move(src, tgt);
        // 步骤3：把n-1个盘子从tmp移到tgt（借助src）
        Hanoi(n-1, tmp, src, tgt); // 修复：n-2 → n-1
    }
}

int main()
{
    // 测试不同数量的盘子
    printf("n=1时的移动步骤：");
    Hanoi(1, 'A', 'B', 'C');
    printf("\n");

    printf("n=2时的移动步骤：");
    Hanoi(2, 'A', 'B', 'C');
    printf("\n");

    printf("n=3时的移动步骤：");
    Hanoi(3, 'A', 'B', 'C');
    printf("\n");

    return 0;
}