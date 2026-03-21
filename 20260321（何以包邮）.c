#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

// 比较函数：仅用于qsort排序（标准库要求，这里无法完全避开指针，但不影响核心逻辑）
int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

int main() {
    // 1. 定义固定大小的数组（避免动态分配/指针）
    // 最多30本书，2^15=32768是半数组的最大子集和数量，足够覆盖n≤30的情况
    int prices[30];          // 存储每本书的价格
    int left_sums[32768];    // 左半部分所有子集和
    int right_sums[32768];   // 右半部分所有子集和
    int left_count = 0;      // 左半部分子集和的实际数量
    int right_count = 0;     // 右半部分子集和的实际数量

    // 2. 输入数据
    int n, x;
    scanf("%d %d", &n, &x);
    for (int i = 0; i < n; i++) {
        scanf("%d", &prices[i]); // 直接存入数组下标
    }

    // 3. 分割数组：把prices分成左右两半
    int mid = n / 2; // 分割点（前mid个为左半，剩余为右半）

    // 4. 枚举左半部分所有子集和（纯数组下标操作）
    int left_len = mid;
    int left_total = 1 << left_len; // 左半部分子集总数（2^left_len）
    for (int mask = 0; mask < left_total; mask++) {
        int current_sum = 0;
        // 遍历左半部分的每一本书，判断是否选中
        for (int i = 0; i < left_len; i++) {
            if (mask & (1 << i)) { // 选中第i本
                current_sum += prices[i]; // 直接取数组下标i的值
            }
        }
        left_sums[left_count++] = current_sum; // 存入左半和数组
    }

    // 5. 枚举右半部分所有子集和（纯数组下标操作）
    int right_len = n - mid;
    int right_total = 1 << right_len; // 右半部分子集总数
    for (int mask = 0; mask < right_total; mask++) {
        int current_sum = 0;
        // 遍历右半部分的每一本书，判断是否选中
        for (int i = 0; i < right_len; i++) {
            if (mask & (1 << i)) { // 选中第i本
                current_sum += prices[mid + i]; // 右半部分从mid下标开始
            }
        }
        right_sums[right_count++] = current_sum; // 存入右半和数组
    }

    // 6. 对右半部分和数组排序（方便后续二分查找）
    qsort(right_sums, right_count, sizeof(int), cmp);

    // 7. 找最小满足条件的总和
    int min_cost = INT_MAX; // 初始化最小花费为极大值
    for (int i = 0; i < left_count; i++) {
        int cur_left = left_sums[i]; // 取左半部分第i个和
        // 情况1：左半部分单独就满足包邮条件
        if (cur_left >= x) {
            if (cur_left < min_cost) {
                min_cost = cur_left;
            }
            continue;
        }
        // 情况2：需要结合右半部分，找最小的右半和使得总和≥x
        int target = x - cur_left;
        int low = 0, high = right_count - 1;
        int best_right = -1;
        // 二分查找：在right_sums数组中找第一个≥target的值
        while (low <= high) {
            int mid_idx = (low + high) / 2; // 数组中间下标
            if (right_sums[mid_idx] >= target) {
                best_right = mid_idx; // 记录符合条件的下标
                high = mid_idx - 1;   // 找更小的下标（更小的和）
            } else {
                low = mid_idx + 1;
            }
        }
        // 如果找到符合条件的右半和，计算总和并更新最小值
        if (best_right != -1) {
            int total = cur_left + right_sums[best_right];
            if (total < min_cost) {
                min_cost = total;
            }
        }
    }

    // 8. 输出结果
    printf("%d\n", min_cost);

    return 0;
}