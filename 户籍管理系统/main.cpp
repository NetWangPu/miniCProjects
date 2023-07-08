#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * 管理员的密码是admin
 */

// 户籍信息结构体
typedef struct {
    char name[50];       // 姓名
    char id[20];         // 身份证号
    char gender[10];     // 性别
    int age;             // 年龄
    char address[100];   // 住址
    char note[100];      // 备注信息
    char regDate[20];    // 注册日期
} Household;

// 节点结构体
typedef struct Node {
    Household data;      // 数据
    struct Node* next;   // 下一个节点的指针
} Node;

// 头节点
Node* head = NULL;

// 从文件中加载数据到链表
void loadFromFile() {
    // 打开文件
    FILE* file = fopen("C:\\data.txt", "r");  // 打开文件进行读取
    // 判断文件是否打开成功
    if (file == NULL) {
        printf("无法打开文件！\n");
        return;
    }

    // 读取文件中的每一行数据
    while (!feof(file)) {
        // 创建新的户籍信息结构体
        Household newHousehold;
        // 从文件中读取每个字段的值，并存入新的户籍信息结构体
        if (fscanf(file, "%s %s %s %d %s %s %s\n", newHousehold.regDate, newHousehold.name, newHousehold.id,
                   &newHousehold.age, newHousehold.gender, newHousehold.address, newHousehold.note) == 7) {
            // 创建新节点
            Node* newNode = (Node*)malloc(sizeof(Node));
            // 将户籍信息结构体存入新节点
            newNode->data = newHousehold;
            // 将新节点的next指针指向NULL
            newNode->next = NULL;

            // 插入链表
            if (head == NULL) {
                // 如果链表为空，则将新节点作为头节点
                head = newNode;
            } else {
                // 如果链表不为空，则将新节点插入到链表末尾
                Node* current = head;
                // 找到链表末尾
                while (current->next != NULL) {
                    // 将current指针指向下一个节点
                    current = current->next;
                }
                // 将新节点插入到链表末尾
                current->next = newNode;
            }
        }
    }

    fclose(file);  // 关闭文件
}

// 保存链表数据到文件
void saveToFile() {
    // 打开文件
    FILE* file = fopen("C:\\data.txt", "w");  // 打开文件进行写入
    // 判断文件是否打开成功
    if (file == NULL) {
        // 如果文件打开失败，则输出错误信息
        printf("无法打开文件！\n");
        return;
    }

    // 遍历链表
    Node* current = head;
    // 遍历链表中的每个节点
    while (current != NULL) {
        // 将每个字段的值写入文件
        fprintf(file, "%s %s %s %d %s %s %s\n", current->data.regDate, current->data.name, current->data.id,
                current->data.age, current->data.gender, current->data.address, current->data.note);
        // 将current指针指向下一个节点
        current = current->next;
    }

    // 关闭文件
    fclose(file);  // 关闭文件
}

// 注册户籍
void registerHousehold() {
    printf("───────────────────────────────────────────────────────────────────────────────\n");
    // 创建新的户籍信息结构体
    Household newHousehold;

    // 从控制台读取每个字段的值，并存入新的户籍信息结构体
    printf("请输入注册日期：");
    scanf("%s", newHousehold.regDate);

    printf("请输入姓名：");
    scanf("%s", newHousehold.name);

    printf("请输入身份证号：");
    scanf("%s", newHousehold.id);

    printf("请输入性别：");
    scanf("%s", newHousehold.gender);

    printf("请输入年龄：");
    scanf("%d", &newHousehold.age);

    printf("请输入住址：");
    scanf("%s", newHousehold.address);

    printf("请输入备注信息：");
    scanf("%s", newHousehold.note);

    // 创建新节点
    Node* newNode = (Node*)malloc(sizeof(Node));
    // 将户籍信息结构体存入新节点
    newNode->data = newHousehold;
    // 将新节点的next指针指向NULL
    newNode->next = NULL;

    // 插入链表
    if (head == NULL) {
        // 如果链表为空，则将新节点作为头节点
        head = newNode;
    } else {
        // 如果链表不为空，则将新节点插入到链表末尾
        Node* current = head;
        // 找到链表末尾
        while (current->next != NULL) {
            // 将current指针指向下一个节点
            current = current->next;
        }
        // 将新节点插入到链表末尾
        current->next = newNode;
    }

    printf("户籍注册成功！\n");
}

// 注销户籍
void cancelHousehold() {
    printf("───────────────────────────────────────────────────────────────────────────────\n");
    // 从控制台读取身份证号
    char id[20];
    // 从控制台读取每个字段的值，并存入新的户籍信息结构体
    printf("请输入要注销的身份证号：");
    scanf("%s", id);

    // 遍历链表
    Node* current = head;
    Node* prev = NULL;
    // 遍历链表中的每个节点
    while (current != NULL) {
        // 判断当前节点是否为要注销的户籍
        if (strcmp(current->data.id, id) == 0) {
            // 如果是，则删除当前节点
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            // 释放当前节点的内存
            free(current);
            printf("户籍注销成功！\n");
            return;
        }
        prev = current;
        // 将current指针指向下一个节点
        current = current->next;
    }

    printf("未找到对应身份证号的户籍！\n");
}

// 户籍查询
void searchHousehold() {
    printf("───────────────────────────────────────────────────────────────────────────────\n");
    // 从控制台读取查询关键词
    char keyword[50];
    printf("请输入查询关键词：");
    scanf("%s", keyword);

    // 遍历链表
    Node* current = head;
    int count = 0;

    // 遍历链表中的每个节点
    while (current != NULL) {
        if (strcmp(current->data.name, keyword) == 0 || strcmp(current->data.id, keyword) == 0) {
            printf("姓名：%s\n", current->data.name);
            printf("身份证号：%s\n", current->data.id);
            printf("性别：%s\n", current->data.gender);
            printf("年龄：%d\n", current->data.age);
            printf("住址：%s\n", current->data.address);
            printf("备注信息：%s\n", current->data.note);
            printf("注册日期：%s\n", current->data.regDate);
            printf("------------------------------\n");
            count++;
        }
        // 将current指针指向下一个节点
        current = current->next;
    }

    // 判断是否找到符合条件的户籍
    if (count == 0) {
        printf("未找到符合条件的户籍！\n");
    }
}

// 按照注册日期排序
void sortByDate() {
    // 判断链表是否为空
    if (head == NULL || head->next == NULL) {
        return;
    }

    // 冒泡排序
    int swapped;
    Node* current;
    Node* last = NULL;

    do {
        // 重置swapped标志
        swapped = 0;
        current = head;

        // 遍历链表中的每个节点
        while (current->next != last) {
            //获取当前节点的数据
            Household currentData = current->data;
            Household nextData = current->next->data;
            //将日期字符串转换为int类型再比较
            int currentYear = atoi(currentData.regDate);
            int nextYear = atoi(nextData.regDate);
            // 比较相邻两个节点的注册日期
            if (currentYear > nextYear) {
                // 交换节点数据
                Household temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            // 将current指针指向下一个节点
            current = current->next;
        }
        // 更新last指针
        last = current;
    } while (swapped);
}

// 户籍信息更改
void modifyHousehold() {
    printf("───────────────────────────────────────────────────────────────────────────────\n");
    // 从控制台读取身份证号
    char id[20];
    // 从控制台读取每个字段的值，并存入新的户籍信息结构体
    printf("请输入要更改的户籍的身份证号：");
    scanf("%s", id);

    // 遍历链表
    Node* current = head;

    // 遍历链表中的每个节点
    while (current != NULL) {
        // 判断当前节点是否为要更改的户籍
        if (strcmp(current->data.id, id) == 0) {
            printf("请输入新的姓名：");
            scanf("%s", current->data.name);

            printf("请输入新的性别：");
            scanf("%s", current->data.gender);

            printf("请输入新的年龄：");
            scanf("%d", &(current->data.age));

            printf("请输入新的住址：");
            scanf("%s", current->data.address);

            printf("请输入新的备注信息：");
            scanf("%s", current->data.note);

            printf("户籍信息更改成功！\n");
            return;
        }
        current = current->next;
    }

    printf("未找到对应身份证号的户籍！\n");
}

// 查询所有户籍
void displayAllHouseholds() {
    // 判断链表是否为空
    Node* current = head;
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│                                   户籍信息                                    │\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");

    // 遍历链表中的每个节点
    while (current != NULL) {
        printf("姓名：%s\n", current->data.name);
        printf("身份证号：%s\n", current->data.id);
        printf("性别：%s\n", current->data.gender);
        printf("年龄：%d\n", current->data.age);
        printf("住址：%s\n", current->data.address);
        printf("备注信息：%s\n", current->data.note);
        printf("注册日期：%s\n", current->data.regDate);
        printf("------------------------------\n");

        // 将current指针指向下一个节点
        current = current->next;
    }
}


// 清空所有数据
void clearAllData() {
    printf("───────────────────────────────────────────────────────────────────────────────\n");
    // 从控制台读取管理员密码
    char password[20];
    printf("请输入管理员密码：");
    scanf("%s", password);

    // 假设管理员密码为 "admin"
    if (strcmp(password, "admin") != 0) {
        printf("密码错误，无法删除数据！\n");
        return;
    }

    // 从控制台读取确认信息
    char confirm[10];
    printf("确定要清空所有数据吗？(输入 'yes' 确认): ");
    scanf("%s", confirm);

    // 判断用户输入的确认信息
    if (strcmp(confirm, "yes") != 0) {
        printf("取消清空数据操作。\n");
        return;
    }

    // 遍历链表中的每个节点，释放内存
    Node* current = head;
    Node* next;

    // 遍历链表中的每个节点
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    // 将head指针置为NULL
    head = NULL;
    printf("所有数据已清空！\n");
}



// 使用说明
void printInstructions() {
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│\t\t\t\t户籍管理系统\t\t\t\t│\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│\t该程序实现了一个简单的户籍管理系统。您可以使用以下选项进行相应操作：\t│\n");
    printf("│\t1. 注册户籍：添加新的户籍信息到系统。\t\t\t\t\t│\n");
    printf("│\t2. 注销户籍：从系统中删除指定身份证号的户籍信息。\t\t\t│\n");
    printf("│\t3. 户籍查询：根据姓名或身份证号查询符合条件的户籍信息。\t\t\t│\n");
    printf("│\t4. 按照注册日期排序：对户籍信息按照注册日期进行排序。\t\t\t│\n");
    printf("│\t5. 户籍信息更改：修改指定身份证号的户籍信息。\t\t\t\t│\n");
    printf("│\t6. 查询所有户籍：显示系统中所有的户籍信息。\t\t\t\t│\n");
    printf("│\t7. 清空所有数据：清空系统中所有的户籍信息。\t\t\t\t│\n");
    printf("│\t8. 使用说明：显示该程序的使用说明。\t\t\t\t\t│\n");
    printf("│\t9. 退出系统：退出户籍管理系统。\t\t\t\t\t│\n");
    printf("└───────────────────────────────────────────────────────────────────────────────┘\n");
//    printf("============= 户籍管理系统 =============\n");
//    printf("该程序实现了一个简单的户籍管理系统。\n");
//    printf("您可以使用以下选项进行相应操作：\n");
//    printf("1. 注册户籍：添加新的户籍信息到系统。\n");
//    printf("2. 注销户籍：从系统中删除指定身份证号的户籍信息。\n");
//    printf("3. 户籍查询：根据姓名或身份证号查询符合条件的户籍信息。\n");
//    printf("4. 按照注册日期排序：对户籍信息按照注册日期进行排序。\n");
//    printf("5. 户籍信息更改：修改指定身份证号的户籍信息。\n");
//    printf("6. 查询所有户籍：显示系统中所有的户籍信息。\n");
//    printf("7. 退出：退出户籍管理系统。\n");
//    printf("8. 使用说明：显示该程序的使用说明。\n");
//    printf("9. 清空所有数据：清空系统中所有的户籍信息。\n");
//    printf("=======================================\n");
}

void wecomeUserInfo(){
    // 打印欢迎信息
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│\t\t\t\t欢迎使用户籍管理系统\t\t\t\t│\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
    printf("└───────────────────────────────────────────────────────────────────────────────┘\n");

}


// 管理员登录
bool adminLogin() {
    wecomeUserInfo();
    // 从控制台读取管理员密码
    int remainingAttempts = 3;

    // 最多尝试3次
    while (remainingAttempts > 0) {
        // 从控制台读取管理员密码
        char password[20];
        printf("管理员登录\n");
        printf("请输入密码：");
        scanf("%s", password);

        // 假设管理员密码为 "admin"
        if (strcmp(password, "admin") == 0) {
            // 登录成功
            printf("登录成功！\n");
            return true;
        } else {
            // 登录失败
            printf("密码错误！还有 %d 次尝试机会。\n", remainingAttempts - 1);
            remainingAttempts--;
        }
    }

    // 登录失败
    printf("登录失败！已达到最大尝试次数。\n");
    return false;
}


int main() {
    // 管理员登录
    if (!adminLogin()) {
        return 0;
    }
    system("cls");
    wecomeUserInfo();
    // 将文件中的数据读取到链表中
    loadFromFile();

    int choice;
    int running = 1;
    while (running) {
        printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
        printf("│\t\t\t\t户籍管理系统\t\t\t\t\t│\n");
        printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
        printf("│\t该程序实现了一个简单的户籍管理系统。您可以使用以下选项进行相应操作：\t│\n");
        printf("│\t\t\t\t1. 注册户籍\t\t\t\t\t│\n");
        printf("│\t\t\t\t2. 注销户籍\t\t\t\t\t│\n");
        printf("│\t\t\t\t3. 户籍查询\t\t\t\t\t│\n");
        printf("│\t\t\t\t4. 按照注册日期排序\t\t\t\t│\n");
        printf("│\t\t\t\t5. 户籍信息更改\t\t\t\t\t│\n");
        printf("│\t\t\t\t6. 查询所有户籍\t\t\t\t\t│\n");
        printf("│\t\t\t\t7. 清空数据\t\t\t\t\t│\n");
        printf("│\t\t\t\t8. 使用说明\t\t\t\t\t│\n");
        printf("│\t\t\t\t9. 退出系统\t\t\t\t\t│\n");
        printf("└───────────────────────────────────────────────────────────────────────────────┘\n");
//        printf("户籍管理系统\n");
//        printf("1. 注册户籍\n");
//        printf("2. 注销户籍\n");
//        printf("3. 户籍查询\n");
//        printf("4. 按照注册日期排序\n");
//        printf("5. 户籍信息更改\n");
//        printf("6. 查询所有户籍\n");
//        printf("7. 退出\n");
//        printf("请输入选项序号：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerHousehold();
                break;
            case 2:
                cancelHousehold();
                break;
            case 3:
                searchHousehold();
                break;
            case 4:
                sortByDate();
                printf("户籍排序完成！\n");
                break;
            case 5:
                modifyHousehold();
                break;
            case 6:
                displayAllHouseholds();
                break;
            case 7:
                clearAllData();
                break;
            case 8:
                printInstructions();
                break;
            case 9:
                running = 0;
                break;
            default:
                printf("无效选项！\n");
                break;
        }

        saveToFile(); // 每次操作后保存数据到文件
    }

    return 0;
}
