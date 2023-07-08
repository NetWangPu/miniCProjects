#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 宏定义
#define MAX_NAME_LENGTH 50

// 老人信息结构体
typedef struct Elderly {
    char name[MAX_NAME_LENGTH]; // 姓名
    int age; // 年龄
    char address[MAX_NAME_LENGTH]; // 地址
    float balance; // 余额
    struct Elderly* next; // 下一个老人信息
} Elderly;

// 全局变量
Elderly* elderlyList = NULL;  // 老人信息链表
int loginAttempts = 0;  // 登录尝试次数

// 函数声明
//加载数据库文件到链表
void loadDatabase();
//将链表保存到数据库文件
void saveDatabase();
//显示菜单选项
void displayMenu();
//主页
int mainIndex();
//登录
void login();
//添加老人信息
void addElderly();
//删除老人信息
void removeElderly();
//更新老人信息
void updateElderly();
//查找老人信息
void searchElderly();
//显示所有老人信息
void displayElderly();
//释放内存
void freeMemory();
//消费
void consume();
//充值
void recharge();
//将老人金额进行排序
void sortByBalance();

// 加载数据库文件到链表
void loadDatabase() {
    FILE* file = fopen("D:\\database.txt", "r");
    if (file == NULL) {
        printf("无法打开数据库文件。\n");
        return;
    }

    // 逐行读取文件内容
    char line[100];
    // fgets()函数用于从指定的流 stream 读取一行，并把它存储在 str 所指向的字符串内。
    while (fgets(line, sizeof(line), file)) {
        // 将读取到的一行内容转换为老人信息结构体
        Elderly* elderly = (Elderly*)malloc(sizeof(Elderly));
        // sscanf()函数从字符串中读取格式化输入
        sscanf(line, "%s %d %s %f", elderly->name, &elderly->age, elderly->address, &elderly->balance);
        elderly->next = NULL;

        // 将新的老人信息添加到链表尾部
        if (elderlyList == NULL) {
            elderlyList = elderly;
        } else {
            Elderly* current = elderlyList;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = elderly;
        }
    }

    fclose(file);
}

/**
 * 按照余额从大到小排序
 */
void sortByBalance() {
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    //使用说明
    printf("│\t\t\t\t排序老人账户\t\t\t\t\t|\n");
    printf("│                                                                               │\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
    printf("└───────────────────────────────────────────────────────────────────────────────┘\n");
    // 选择排序
    Elderly* current = elderlyList;
    while (current != NULL) {
        Elderly* max = current;
        Elderly* temp = current->next;
        while (temp != NULL) {
            if (temp->balance > max->balance) {
                max = temp;
            }
            temp = temp->next;
        }
        // 交换数据
        char name[MAX_NAME_LENGTH];
        strcpy(name, current->name);
        strcpy(current->name, max->name);
        strcpy(max->name, name);

        int age = current->age;
        current->age = max->age;
        max->age = age;

        char address[MAX_NAME_LENGTH];
        strcpy(address, current->address);
        strcpy(current->address, max->address);
        strcpy(max->address, address);

        float balance = current->balance;
        current->balance = max->balance;
        max->balance = balance;

        current = current->next;
    }
}

/**
 * 消费
 */
void consume() {
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    //使用说明
    printf("│\t\t\t\t老人账户消费\t\t\t\t\t|\n");
    printf("│                                                                               │\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
    printf("└───────────────────────────────────────────────────────────────────────────────┘\n");
    char name[MAX_NAME_LENGTH];
    float amount;

    printf("请输入老人姓名：");
    scanf("%s", name);
    printf("请输入消费金额：");
    scanf("%f", &amount);

    Elderly* current = elderlyList;
    // 遍历链表，查找老人信息
    while (current != NULL) {
        // 如果找到老人信息，则进行消费
        if (strcmp(current->name, name) == 0) {
            // 如果余额小于消费金额，则提示余额不足
            if (current->balance < amount) {
                printf("余额不足，无法消费。\n");
            } else {
                // 如果余额大于消费金额，则进行消费
                current->balance -= amount;
                printf("消费成功，余额为：%.2f\n", current->balance);
            }
            return;
        }
        // 遍历下一个节点
        current = current->next;
    }

    printf("未找到该老人信息。\n");
}

/**
 * 充值
 */
void recharge() {
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    //使用说明
    printf("│\t\t\t\t老人账户充值\t\t\t\t\t|\n");
    printf("│                                                                               │\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
    printf("└───────────────────────────────────────────────────────────────────────────────┘\n");
    char name[MAX_NAME_LENGTH];
    float amount;

    printf("请输入老人姓名：");
    scanf("%s", name);
    printf("请输入充值金额：");
    scanf("%f", &amount);

    Elderly* current = elderlyList;
    // 遍历链表，查找老人信息
    while (current != NULL) {
        // 如果找到老人信息，则进行充值
        if (strcmp(current->name, name) == 0) {
            current->balance += amount;
            printf("充值成功，余额为：%.2f\n", current->balance);
            return;
        }
        // 遍历下一个节点
        current = current->next;
    }

    printf("未找到该老人信息。\n");
}



// 将链表保存到数据库文件
void saveDatabase() {
    // w：写入模式打开文件，如果文件不存在则创建，如果文件存在则清空文件内容
    FILE* file = fopen("D:\\database.txt", "w");
    if (file == NULL) {
        printf("无法打开数据库文件。\n");
        return;
    }

    // 逐行写入文件内容
    Elderly* current = elderlyList;
    // 遍历链表，将每个节点的信息写入文件
    while (current != NULL) {
        fprintf(file, "%s %d %s %f\n", current->name, current->age, current->address, current->balance);
        // fprintf()函数用于格式化输出到指定文件
        current = current->next;
    }

    fclose(file);
}

// 显示菜单选项
void displayMenu() {
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    //使用说明
    printf("│\t\t\t\t欢迎使用本系统\t\t\t\t\t|\n");
    printf("│                                                                               │\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│\t\t\t\t1.添加老人信息\t\t\t\t\t│\n");
    printf("│\t\t\t\t2.删除老人信息\t\t\t\t\t│\n");
    printf("│\t\t\t\t3.更新老人信息\t\t\t\t\t│\n");
    printf("│\t\t\t\t4.查找老人信息\t\t\t\t\t│\n");
    printf("│\t\t\t\t5.显示所有老人信息\t\t\t\t│\n");
    printf("│\t\t\t\t6.账户充值\t\t\t\t\t│\n");
    printf("│\t\t\t\t7.账户消费\t\t\t\t\t│\n");
    printf("│\t\t\t\t8.按照余额从大到小排序\t\t\t\t│\n");
    printf("│\t\t\t\t9.退出系统\t\t\t\t\t│\n");
    printf("└───────────────────────────────────────────────────────────────────────────────┘\n");
    printf("请选择操作：");
//    printf("\n=============== 养老院信息管理系统 ===============\n");
//    printf("1. 登录\n");
//    printf("2. 添加老人信息\n");
//    printf("3. 删除老人信息\n");
//    printf("4. 更新老人信息\n");
//    printf("5. 查找老人信息\n");
//    printf("6. 显示所有老人信息\n");
//    printf("7. 退出\n");
//    printf("=================================================\n");
//    printf("请选择操作：");
}

// 登录
int main() {
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    //使用说明
    printf("│\t\t\t\t欢迎使用本系统\t\t\t\t\t|\n");
    printf("│                                                                               │\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
    login ();

    return 0;
}

void login(){
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    //使用说明
    printf("│\t\t\t\t登录系统\t\t\t\t\t|\n");
    printf("│                                                                               │\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
    printf("└───────────────────────────────────────────────────────────────────────────────┘\n");
    char username[20];
    char password[20];
    printf("请输入用户名：");
    scanf("%s", username);
    printf("请输入密码：");
    scanf("%s", password);

    // 如果用户名和密码都正确，则登录成功
    if (strcmp(username, "admin") == 0&& strcmp(password, "admin123") == 0) {
        printf("登录成功！\n");
        // 登录成功后，重置登录失败次数
        loginAttempts = 0;
        // 进入主界面
        mainIndex();
    } else {
        // 登录失败后，登录失败次数加1
        loginAttempts++;
        // 如果登录失败次数小于3，则重新登录
        printf("登录失败！\n");
        if (loginAttempts < 3) {
            printf("您还有 %d 次登录机会。\n", 3 - loginAttempts);
            login();
        } else {
            printf("登录失败次数过多，程序退出。\n");
            freeMemory();
            exit(0);
        }
    }
}

// 添加老人信息
void addElderly() {
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    //使用说明
    printf("│\t\t\t\t添加老人信息\t\t\t\t\t|\n");
    printf("│                                                                               │\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
    printf("└───────────────────────────────────────────────────────────────────────────────┘\n");
    // 为新节点分配内存
    Elderly* elderly = (Elderly*)malloc(sizeof(Elderly));

    printf("请输入老人姓名：");
    scanf("%s", elderly->name);
    printf("请输入老人年龄：");
    scanf("%d", &elderly->age);
    printf("请输入老人地址：");
    scanf("%s", elderly->address);
    printf("请输入老人余额：");
    scanf("%f", &elderly->balance);

    elderly->next = NULL;

    // 如果链表为空，则直接将新节点赋值给链表
    if (elderlyList == NULL) {
        // 将新节点赋值给链表
        elderlyList = elderly;
    } else {
        // 如果链表不为空，则将新节点添加到链表的末尾
        Elderly* current = elderlyList;
        // 遍历链表，找到最后一个节点
        while (current->next != NULL) {
            current = current->next;
        }
        // 将新节点添加到链表的末尾
        current->next = elderly;
    }

    printf("老人信息添加成功！\n");
    // 保存数据到文件
    saveDatabase();
}

// 删除老人信息
void removeElderly() {
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    //使用说明
    printf("│\t\t\t\t删除老人信息\t\t\t\t\t|\n");
    printf("│                                                                               │\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
    printf("└───────────────────────────────────────────────────────────────────────────────┘\n");
    char name[MAX_NAME_LENGTH];

    printf("请输入要删除的老人姓名：");
    scanf("%s", name);

    // 如果链表为空，则直接返回
    Elderly* current = elderlyList;
    Elderly* previous = NULL;

    // 遍历链表，查找要删除的老人信息
    while (current != NULL) {
        // 如果找到要删除的老人信息，则删除
        if (strcmp(current->name, name) == 0) {
            // 如果要删除的老人信息是第一个节点
            if (previous == NULL) {
                // 将第二个节点赋值给链表
                elderlyList = current->next;
            } else {
                // 如果要删除的老人信息不是第一个节点，则将上一个节点的 next 指向要删除的老人信息的下一个节点
                previous->next = current->next;
            }
            // 释放要删除的老人信息节点的内存
            free(current);
            printf("老人信息删除成功！\n");
            saveDatabase();
            return;
        }
        // 如果没有找到要删除的老人信息，则继续遍历链表
        previous = current;
        current = current->next;
    }

    printf("找不到要删除的老人信息。\n");
}

// 更新老人信息
void updateElderly() {
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    //使用说明
    printf("│\t\t\t\t更新老人信息\t\t\t\t\t|\n");
    printf("│                                                                               │\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
    printf("└───────────────────────────────────────────────────────────────────────────────┘\n");
    char name[MAX_NAME_LENGTH];

    printf("请输入要更新的老人姓名：");
    scanf("%s", name);

    // 如果链表为空，则直接返回
    Elderly* current = elderlyList;

    // 遍历链表，查找要更新的老人信息
    while (current != NULL) {
        // 如果找到要更新的老人信息，则更新
        if (strcmp(current->name, name) == 0) {
            printf("请输入新的老人姓名：");
            scanf("%s", current->name);
            printf("请输入新的老人年龄：");
            scanf("%d", &current->age);
            printf("请输入新的老人地址：");
            scanf("%s", current->address);
            printf("请输入新的老人余额：");
            scanf("%f", &current->balance);

            printf("老人信息更新成功！\n");
            // 保存数据到文件
            saveDatabase();
            return;
        }
        // 如果没有找到要更新的老人信息，则继续遍历链表
        current = current->next;
    }

    printf("找不到要更新的老人信息。\n");
}

// 查找老人信息
void searchElderly() {
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    //使用说明
    printf("│\t\t\t\t查找老人信息\t\t\t\t\t|\n");
    printf("│                                                                               │\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
    printf("└───────────────────────────────────────────────────────────────────────────────┘\n");
    char name[MAX_NAME_LENGTH];

    printf("请输入要查找的老人姓名：");
    scanf("%s", name);

    // 如果链表为空，则直接返回
    Elderly* current = elderlyList;

    // 遍历链表，查找要查找的老人信息
    while (current != NULL) {
        // 如果找到要查找的老人信息，则显示
        if (strcmp(current->name, name) == 0) {
            printf("姓名：%s\n", current->name);
            printf("年龄：%d\n", current->age);
            printf("地址：%s\n", current->address);
            printf("余额：%.2f\n", current->balance);
            return;
        }
        // 如果没有找到要查找的老人信息，则继续遍历链表
        current = current->next;
    }

    printf("找不到要查找的老人信息。\n");
}

// 显示所有老人信息
void displayElderly() {
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    //使用说明
    printf("│\t\t\t\t显示老人信息\t\t\t\t\t|\n");
    printf("│                                                                               │\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
    printf("└───────────────────────────────────────────────────────────────────────────────┘\n");
    if (elderlyList == NULL) {
        printf("暂无老人信息。\n");
        return;
    }

    // 如果链表不为空，则显示所有老人信息
    Elderly* current = elderlyList;

    // 遍历链表，显示所有老人信息
    printf("所有老人信息：\n");
    while (current != NULL) {
        printf("姓名：%s\n", current->name);
        printf("年龄：%d\n", current->age);
        printf("地址：%s\n", current->address);
        printf("余额：%.2f\n", current->balance);
        printf("----------------------------\n");

        current = current->next;
    }
}

// 释放链表内存
void freeMemory() {
    // 如果链表为空，则直接返回
    Elderly* current = elderlyList;
    // 遍历链表，释放所有节点的内存
    while (current != NULL) {
        // 保存下一个节点的指针
        Elderly* next = current->next;
        // 释放当前节点的内存
        free(current);
        // 将下一个节点的指针赋值给当前节点
        current = next;
    }
}

int mainIndex() {
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    //使用说明
    printf("│\t\t\t\t登录成功\t\t\t\t\t|\n");
    printf("│                                                                               │\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
    printf("└───────────────────────────────────────────────────────────────────────────────┘\n");
    loadDatabase();

    while (1) {
        displayMenu();

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // 添加老人信息
                addElderly();
                break;
            case 2:
                // 删除老人信息
                removeElderly();
                break;
            case 3:
                // 更新老人信息
                updateElderly();
                break;
            case 4:
                // 查找老人信息
                searchElderly();
                break;
            case 5:
                // 显示所有老人信息
                displayElderly();
                break;
            case 6:
                // 消费
                consume();
                break;
            case 7:
                // 充值
                recharge();
                break;
            case 8:
                // 将老人金额进行排序
                sortByBalance();
                break;
            case 9:
                // 退出系统
                // 保存数据到文件
                saveDatabase();
                freeMemory();
                exit(0);
            default:
                printf("无效的选择。\n");
        }
    }

    return 0;
}
