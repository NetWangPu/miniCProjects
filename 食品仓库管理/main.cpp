#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>

// 管理员用户名和密码
#define USERNAME "admin"
#define PASSWORD "admin"


// 食品结构体
typedef struct {
    char name[50]; // 食品名称
    char expiration_date[20]; // 保质期
    int quantity; // 数量
} FoodItem;

// 链表节点
typedef struct Node {
    FoodItem data; // 数据域
    struct Node* next;  // 指针域
} Node;

// 全局变量，链表头节点
Node* head = NULL;


//业务逻辑函数声明
//添加食品
void searchItem(char name[50]);
//修改食品数量
void updateQuantity(char name[50], int quantity);
//删除食品
void deleteItem(char name[50]);
//在链表末尾插入食品
void insertItem(FoodItem item);
//保存链表到文件
void saveToFile();
//从文件中加载链表
void loadFromFile();
//打印菜单
void printMenu();
//添加食品
void findAllItem();
//检查食品是否过期
void checkExpirationDate(char date[50]);
//检查临期食品与过期食品
void checkExpirationDate();
//使用介绍
void useIntroduction();
//管理员登录
void login();
//管理员主页
void useIndex();
//清空所有食品
void clearAllItem();

int main() {
    //用户登录
    login();
    //用户登录成功后，加载文件中的数据
    return 0;
}

/**
 * 从文件中加载链表
 */
void loadFromFile() {
    // 打开文件
    FILE* file = fopen("C:\\food_storage.txt", "r");
    // 判断文件是否打开成功
    if (file == NULL) {
        printf("无法打开文件！\n");
        return;
    }
    // 读取文件内容
    char line[100];
    // 逐行读取
    while (fgets(line, sizeof(line), file)) {
        // 将读取到的字符串转换为FoodItem结构体
        FoodItem item;
        // 从字符串中读取数据
        sscanf(line, "%[^,],%[^,],%d\n", item.name, item.expiration_date, &item.quantity);
        // 将食品插入到链表中
        insertItem(item);
    }

    // 关闭文件
    fclose(file);
}

/**
 * 用户登录
 * @return 无
 */
 void login() {
    //用户有三次机会输入用户名和密码 并提示
    int i = 0;
    char username[50];
    char password[50];
    while (i < 3) {
        printf("请输入用户名：");
        scanf("%s", username);
        printf("请输入密码：");
        scanf("%s", password);
        //判断用户名和密码是否正确
        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            printf("登录成功！\n");
            //登录成功后跳转到管理员主页
            useIndex();
            break;
        } else {
            printf("用户名或密码错误！\n");
            printf("您还有%d次机会！\n", 2 - i);
        }
        i++;
    }
}

/**
 * 清空所有食品
 * @return 无
 */
void clearAllItem(){
    //用户确认是否清空
    printf("您确定要清空所有食品吗？\n");
    printf("1.确定\n");
    printf("2.取消\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 2) {
        //取消清空
        return;
    }
    //判断链表是否为空
    if (head == NULL) {
        printf("链表为空！\n");
        return;
    }
    //遍历链表，释放所有节点
    Node* current = head;
    while (current != NULL) {
        //保存下一个节点
        Node* next = current->next;
        //释放当前节点
        free(current);
        //指向下一个节点
        current = next;
    }
    //将头节点置空
    head = NULL;
    printf("清空成功！\n");
    //清空文件
    FILE* file = fopen("C:\\food_storage.txt", "w");
    // 判断文件是否打开成功
    if (file == NULL) {
        printf("无法打开文件！\n");
        return;
    }
    // 关闭文件
    fclose(file);
}


// 将链表保存到文件
void saveToFile() {
    // 打开文件
    FILE* file = fopen("C:\\food_storage.txt", "w");
    // 判断文件是否打开成功
    if (file == NULL) {
        printf("无法打开文件！\n");
        return;
    }

    // 遍历链表，将数据写入文件
    Node* current = head;
    // 逐行写入
    while (current != NULL) {
        // 将FoodItem结构体转换为字符串
        fprintf(file, "%s,%s,%d\n", current->data.name, current->data.expiration_date, current->data.quantity);
        // 指向下一个节点
        current = current->next;
    }

    // 关闭文件
    fclose(file);
}
/**
 * 用户使用介绍
 */
void useIntroduction(){
    //带边框的输出
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    //使用说明
    printf("│\t\t\t\t系统使用说明\t\t\t\t\t|\n");
    printf("│                                                                               │\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
    printf("|\t\t本系统用于食品管理，主要功能有：\t\t\t\t\t|\n");
    printf("|\t\t1.添加食品\t\t\t\t\t\t\t|\n");
    printf("|\t\t可以添加食品的名称、保质期、数量存储到系统中\t\t\t\t|\n");
    printf("|\t\t2.查询食品\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t可以根据食品名称查询食品的保质期和数量\t\t\t\t\t|\n");
    printf("|\t\t3.修改食品数量\t\t\t\t\t\t\t|\n");
    printf("|\t\t可以根据食品名称修改食品的数量\t\t\t\t\t\t|\n");
    printf("|\t\t4.删除食品\t\t\t\t\t\t\t|\n");
    printf("|\t\t可以根据食品名称删除食品\t\t\t\t\t\t|\n");
    printf("|\t\t5.检查食品是否过期\t\t\t\t\t\t\t|\n");
    printf("|\t\t可以根据食品名称检查食品是否过期\t\t\t\t\t|\n");
    printf("|\t\t6.检查临期食品与过期食品\t\t\t\t\t\t\t|\n");
    printf("|\t\t可以检查系统中的临期食品与过期食品\t\t\t\t\t|\n");
    printf("|\t\t7.退出系统\t\t\t\t\t\t\t|\n");
    printf("|\t\t可以退出系统\t\t\t\t\t\t\t|\n");
    printf("└───────────────────────────────────────────────────────────────────────────────┘\n");
    printf("\n");
}



// 在链表末尾插入食品
void insertItem(FoodItem item) {
    // 创建新节点
    Node* newNode = (Node*)malloc(sizeof(Node));
    // 将食品数据赋值给新节点
    newNode->data = item;
    // 将新节点插入到链表末尾
    newNode->next = NULL;

    // 判断链表是否为空
    if (head == NULL) {
        // 将新节点设置为头节点
        head = newNode;
    } else {
        // 遍历链表，找到最后一个节点
        Node* current = head;
        // 遍历链表，找到最后一个节点
        while (current->next != NULL) {
            // 指向下一个节点
            current = current->next;
        }
        // 将新节点插入到链表末尾
        current->next = newNode;
    }
}

/**
 * 根据食品名称删除食品
 * @param name  食品名称
 */
void deleteItem(char name[50]) {
    // 遍历链表，查找食品
    Node* current = head;
    // 记录上一个节点
    Node* prev = NULL;

    // 遍历链表
    while (current != NULL) {
        // 判断是否找到食品
        if (strcmp(current->data.name, name) == 0) {
            // 判断是否为头节点
            if (prev == NULL) {
                // 将头节点指向下一个节点
                head = current->next;
            } else {
                // 将上一个节点指向下一个节点
                prev->next = current->next;
            }

            // 释放内存
            free(current);
            // 退出循环
            printf("食品删除成功！\n");
            return;
        }

        // 指向下一个节点
        prev = current;
        // 指向下一个节点
        current = current->next;
    }

    // 打印提示信息
    printf("找不到食品！\n");
}

/**
 * 修改食品数量
 * @param name   食品名称
 * @param quantity  食品数量
 */
void updateQuantity(char name[50], int quantity) {
    Node* current = head;

    // 遍历链表
    while (current != NULL) {
        // 判断是否找到食品
        if (strcmp(current->data.name, name) == 0) {
            // 修改食品数量
            current->data.quantity = quantity;
            // 退出循环
            printf("食品数量修改成功！\n");
            return;
        }

        // 指向下一个节点
        current = current->next;
    }

    // 打印提示信息
    printf("找不到该食品！\n");
}

// 根据食品名称查找食品
void searchItem(char name[50]) {
    Node* current = head;

    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            printf("食品名称: %s\n", current->data.name);
            printf("保质期: %s\n", current->data.expiration_date);
            printf("数量: %d\n", current->data.quantity);
            return;
        }

        current = current->next;
    }

    printf("找不到该食品！\n");
}

/**
 * 打印所有食品
 * 美化输出带外边框的表格
 */
void findAllItem() {
    Node* current = head;

    //输出表头
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│ 食品名称\t\t│ 保质期\t\t│ 数量\t\t\t\t│\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");

    // 遍历链表
    while (current != NULL) {
        // 输出食品信息
        printf("│ %-20s\t│ %-20s\t│ %-25d\t│\n", current->data.name, current->data.expiration_date, current->data.quantity);

        // 指向下一个节点
        current = current->next;
        //输出分割线
        printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
    }

    //输出表尾
    printf("└───────────────────────────────────────────────────────────────────────────────┘\n");
}

/**
 * 检测临期食品
 * @param date  日期
 */
void checkExpirationDate(char date[50]){
    Node* current = head;

    //输出表头
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│ 食品名称\t\t│ 保质期\t\t│ 数量\t\t\t\t│\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");

    // 遍历链表
    while (current != NULL) {
        // 判断是否为临期食品
        /**
         * strcmp()函数比较两个字符串 str1 和 str2。函数返回值如下：
         * 如果返回值 < 0，则表示 str1 小于 str2。
         * 如果返回值 > 0，则表示 str2 小于 str1。
         * 如果返回值 = 0，则表示 str1 等于 str2。
         */
         //将他们都转化为数字比较
         int date1 = atoi(current->data.expiration_date);
         int date2 = atoi(date);
        if (date1 < date2) {
            // 输出食品信息
            printf("│ %-20s\t│ %-20s\t│ %-25d\t│\n", current->data.name, current->data.expiration_date, current->data.quantity);
            //输出分割线
            printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
        }

        // 指向下一个节点
        current = current->next;
    }

    //输出表尾
    printf("└───────────────────────────────────────────────────────────────────────────────┘\n");

}

/**
 * 检测临期视频 获取当前日期并调用比较
 * 用户输入
 * 并给出示例 2024-01-01 输入20240101
 * 输入的时间向前后一个月
 */
void checkExpirationDate(){
    //获取当前日期
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);
    int year = lt->tm_year + 1900;
    int month = lt->tm_mon + 1;
    int day = lt->tm_mday;
    //将当前日期转换为整型
    int date = year * 10000 + month * 100 + day;
    //将当前日期转换为字符串
    char str[50];
    sprintf(str, "%d", date);
    //将当前日期向后推一个月
    date = date + 100;
    //将日期转换为字符串
    char str2[50];
    sprintf(str2, "%d", date);
    //打印出当前日期
    printf("当前日期为：%s\n", str);
    //调用检测临期食品函数
    checkExpirationDate(str2);
}



// 打印菜单
void printMenu() {
    //设置颜色
    system("color a");
    // 打印菜单
    printf("┌───────────────────────────────────────────────────────────────────────────────┐\n");
    printf("│\t\t\t\t\t\t\t\t\t\t│\n");
    printf("│\t\t\t欢迎使用食品库存管理系统\t\t\t\t│\n");
    printf("│\t\t\t\t\t\t\t\t\t\t│\n");
    printf("├───────────────────────────────────────────────────────────────────────────────┤\n");
    printf("│\t\t\t\t\t\t\t\t\t\t│\n");
    printf("│\t\t\t1. 添加食品\t\t\t\t\t\t│\n");
    printf("│\t\t\t2. 删除食品\t\t\t\t\t\t│\n");
    printf("│\t\t\t3. 修改食品数量\t\t\t\t\t\t│\n");
    printf("│\t\t\t4. 查找食品\t\t\t\t\t\t│\n");
    printf("│\t\t\t5. 查看所有食品\t\t\t\t\t\t│\n");
    printf("│\t\t\t6. 使用说明\t\t\t\t\t\t│\n");
    printf("│\t\t\t7. 检临期期食品\t\t\t\t\t\t│\n");
    //清空所有食品
    printf("│\t\t\t8. 清空所有食品\t\t\t\t\t\t│\n");
    printf("│\t\t\t9. 退出系统\t\t\t\t\t\t│\n");
    printf("│\t\t\t\t\t\t\t\t\t\t│\n");
    printf("└───────────────────────────────────────────────────────────────────────────────┘\n");
    printf("请输入操作编号：");
}

void useIndex() {
    //将文件中的内容读取到链表中
    loadFromFile();

    int choice;
    char name[50];
    int quantity;
    char expiration_date[20];

    do {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("请输入食品名称：");
                scanf("%s", name);
                printf("请输入保质期：");
                scanf("%s", expiration_date);
                printf("请输入数量：");
                scanf("%d", &quantity);

                FoodItem newItem;
                strcpy(newItem.name, name);
                strcpy(newItem.expiration_date, expiration_date);
                newItem.quantity = quantity;

                insertItem(newItem);
                saveToFile();
                printf("食品添加成功！\n");
                break;

            case 2:
                printf("请输入要删除的食品名称：");
                scanf("%s", name);
                deleteItem(name);
                saveToFile();
                break;

            case 3:
                printf("请输入要修改数量的食品名称：");
                scanf("%s", name);
                printf("请输入新的数量：");
                scanf("%d", &quantity);
                updateQuantity(name, quantity);
                saveToFile();
                break;

            case 4:
                printf("请输入要查找的食品名称：");
                scanf("%s", name);
                searchItem(name);
                break;

            case 5:
                findAllItem();
                break;
            case 6:
                useIntroduction();
                break;
            case 7:
                checkExpirationDate();
                break;
            case 8:
                clearAllItem();
                break;
            case 9:
                printf("再见！\n");
                break;

            default:
                printf("无效的选择！\n");
                break;
        }
    } while (choice != 9);
    //检测到用户输入9时退出循环
}
