/*

union

联合体: 保存不同类型和长度对象的变量。

定义:
    union unionName {
        strict {
            int type;
        };
        int ival;
        float fval;
    }
声明:
    union unionName{...} u;
    union unionName u;
初始化:

使用:
    联合名.成员
    联合名->成员
# 区别于结构体，联合体的字段项中 只有一个字段处于“活动状态”。
# 具体实现中，联合体实际分配的内存长度应能容下最大长度的数据类型
*/
