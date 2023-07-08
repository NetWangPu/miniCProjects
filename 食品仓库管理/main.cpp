#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>

// ����Ա�û���������
#define USERNAME "admin"
#define PASSWORD "admin"


// ʳƷ�ṹ��
typedef struct {
    char name[50]; // ʳƷ����
    char expiration_date[20]; // ������
    int quantity; // ����
} FoodItem;

// ����ڵ�
typedef struct Node {
    FoodItem data; // ������
    struct Node* next;  // ָ����
} Node;

// ȫ�ֱ���������ͷ�ڵ�
Node* head = NULL;


//ҵ���߼���������
//���ʳƷ
void searchItem(char name[50]);
//�޸�ʳƷ����
void updateQuantity(char name[50], int quantity);
//ɾ��ʳƷ
void deleteItem(char name[50]);
//������ĩβ����ʳƷ
void insertItem(FoodItem item);
//���������ļ�
void saveToFile();
//���ļ��м�������
void loadFromFile();
//��ӡ�˵�
void printMenu();
//���ʳƷ
void findAllItem();
//���ʳƷ�Ƿ����
void checkExpirationDate(char date[50]);
//�������ʳƷ�����ʳƷ
void checkExpirationDate();
//ʹ�ý���
void useIntroduction();
//����Ա��¼
void login();
//����Ա��ҳ
void useIndex();
//�������ʳƷ
void clearAllItem();

int main() {
    //�û���¼
    login();
    //�û���¼�ɹ��󣬼����ļ��е�����
    return 0;
}

/**
 * ���ļ��м�������
 */
void loadFromFile() {
    // ���ļ�
    FILE* file = fopen("C:\\food_storage.txt", "r");
    // �ж��ļ��Ƿ�򿪳ɹ�
    if (file == NULL) {
        printf("�޷����ļ���\n");
        return;
    }
    // ��ȡ�ļ�����
    char line[100];
    // ���ж�ȡ
    while (fgets(line, sizeof(line), file)) {
        // ����ȡ�����ַ���ת��ΪFoodItem�ṹ��
        FoodItem item;
        // ���ַ����ж�ȡ����
        sscanf(line, "%[^,],%[^,],%d\n", item.name, item.expiration_date, &item.quantity);
        // ��ʳƷ���뵽������
        insertItem(item);
    }

    // �ر��ļ�
    fclose(file);
}

/**
 * �û���¼
 * @return ��
 */
 void login() {
    //�û������λ��������û��������� ����ʾ
    int i = 0;
    char username[50];
    char password[50];
    while (i < 3) {
        printf("�������û�����");
        scanf("%s", username);
        printf("���������룺");
        scanf("%s", password);
        //�ж��û����������Ƿ���ȷ
        if (strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            printf("��¼�ɹ���\n");
            //��¼�ɹ�����ת������Ա��ҳ
            useIndex();
            break;
        } else {
            printf("�û������������\n");
            printf("������%d�λ��ᣡ\n", 2 - i);
        }
        i++;
    }
}

/**
 * �������ʳƷ
 * @return ��
 */
void clearAllItem(){
    //�û�ȷ���Ƿ����
    printf("��ȷ��Ҫ�������ʳƷ��\n");
    printf("1.ȷ��\n");
    printf("2.ȡ��\n");
    int choice;
    scanf("%d", &choice);
    if (choice == 2) {
        //ȡ�����
        return;
    }
    //�ж������Ƿ�Ϊ��
    if (head == NULL) {
        printf("����Ϊ�գ�\n");
        return;
    }
    //���������ͷ����нڵ�
    Node* current = head;
    while (current != NULL) {
        //������һ���ڵ�
        Node* next = current->next;
        //�ͷŵ�ǰ�ڵ�
        free(current);
        //ָ����һ���ڵ�
        current = next;
    }
    //��ͷ�ڵ��ÿ�
    head = NULL;
    printf("��ճɹ���\n");
    //����ļ�
    FILE* file = fopen("C:\\food_storage.txt", "w");
    // �ж��ļ��Ƿ�򿪳ɹ�
    if (file == NULL) {
        printf("�޷����ļ���\n");
        return;
    }
    // �ر��ļ�
    fclose(file);
}


// �������浽�ļ�
void saveToFile() {
    // ���ļ�
    FILE* file = fopen("C:\\food_storage.txt", "w");
    // �ж��ļ��Ƿ�򿪳ɹ�
    if (file == NULL) {
        printf("�޷����ļ���\n");
        return;
    }

    // ��������������д���ļ�
    Node* current = head;
    // ����д��
    while (current != NULL) {
        // ��FoodItem�ṹ��ת��Ϊ�ַ���
        fprintf(file, "%s,%s,%d\n", current->data.name, current->data.expiration_date, current->data.quantity);
        // ָ����һ���ڵ�
        current = current->next;
    }

    // �ر��ļ�
    fclose(file);
}
/**
 * �û�ʹ�ý���
 */
void useIntroduction(){
    //���߿�����
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    //ʹ��˵��
    printf("��\t\t\t\tϵͳʹ��˵��\t\t\t\t\t|\n");
    printf("��                                                                               ��\n");
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("|\t\t��ϵͳ����ʳƷ������Ҫ�����У�\t\t\t\t\t|\n");
    printf("|\t\t1.���ʳƷ\t\t\t\t\t\t\t|\n");
    printf("|\t\t�������ʳƷ�����ơ������ڡ������洢��ϵͳ��\t\t\t\t|\n");
    printf("|\t\t2.��ѯʳƷ\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t���Ը���ʳƷ���Ʋ�ѯʳƷ�ı����ں�����\t\t\t\t\t|\n");
    printf("|\t\t3.�޸�ʳƷ����\t\t\t\t\t\t\t|\n");
    printf("|\t\t���Ը���ʳƷ�����޸�ʳƷ������\t\t\t\t\t\t|\n");
    printf("|\t\t4.ɾ��ʳƷ\t\t\t\t\t\t\t|\n");
    printf("|\t\t���Ը���ʳƷ����ɾ��ʳƷ\t\t\t\t\t\t|\n");
    printf("|\t\t5.���ʳƷ�Ƿ����\t\t\t\t\t\t\t|\n");
    printf("|\t\t���Ը���ʳƷ���Ƽ��ʳƷ�Ƿ����\t\t\t\t\t|\n");
    printf("|\t\t6.�������ʳƷ�����ʳƷ\t\t\t\t\t\t\t|\n");
    printf("|\t\t���Լ��ϵͳ�е�����ʳƷ�����ʳƷ\t\t\t\t\t|\n");
    printf("|\t\t7.�˳�ϵͳ\t\t\t\t\t\t\t|\n");
    printf("|\t\t�����˳�ϵͳ\t\t\t\t\t\t\t|\n");
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("\n");
}



// ������ĩβ����ʳƷ
void insertItem(FoodItem item) {
    // �����½ڵ�
    Node* newNode = (Node*)malloc(sizeof(Node));
    // ��ʳƷ���ݸ�ֵ���½ڵ�
    newNode->data = item;
    // ���½ڵ���뵽����ĩβ
    newNode->next = NULL;

    // �ж������Ƿ�Ϊ��
    if (head == NULL) {
        // ���½ڵ�����Ϊͷ�ڵ�
        head = newNode;
    } else {
        // ���������ҵ����һ���ڵ�
        Node* current = head;
        // ���������ҵ����һ���ڵ�
        while (current->next != NULL) {
            // ָ����һ���ڵ�
            current = current->next;
        }
        // ���½ڵ���뵽����ĩβ
        current->next = newNode;
    }
}

/**
 * ����ʳƷ����ɾ��ʳƷ
 * @param name  ʳƷ����
 */
void deleteItem(char name[50]) {
    // ������������ʳƷ
    Node* current = head;
    // ��¼��һ���ڵ�
    Node* prev = NULL;

    // ��������
    while (current != NULL) {
        // �ж��Ƿ��ҵ�ʳƷ
        if (strcmp(current->data.name, name) == 0) {
            // �ж��Ƿ�Ϊͷ�ڵ�
            if (prev == NULL) {
                // ��ͷ�ڵ�ָ����һ���ڵ�
                head = current->next;
            } else {
                // ����һ���ڵ�ָ����һ���ڵ�
                prev->next = current->next;
            }

            // �ͷ��ڴ�
            free(current);
            // �˳�ѭ��
            printf("ʳƷɾ���ɹ���\n");
            return;
        }

        // ָ����һ���ڵ�
        prev = current;
        // ָ����һ���ڵ�
        current = current->next;
    }

    // ��ӡ��ʾ��Ϣ
    printf("�Ҳ���ʳƷ��\n");
}

/**
 * �޸�ʳƷ����
 * @param name   ʳƷ����
 * @param quantity  ʳƷ����
 */
void updateQuantity(char name[50], int quantity) {
    Node* current = head;

    // ��������
    while (current != NULL) {
        // �ж��Ƿ��ҵ�ʳƷ
        if (strcmp(current->data.name, name) == 0) {
            // �޸�ʳƷ����
            current->data.quantity = quantity;
            // �˳�ѭ��
            printf("ʳƷ�����޸ĳɹ���\n");
            return;
        }

        // ָ����һ���ڵ�
        current = current->next;
    }

    // ��ӡ��ʾ��Ϣ
    printf("�Ҳ�����ʳƷ��\n");
}

// ����ʳƷ���Ʋ���ʳƷ
void searchItem(char name[50]) {
    Node* current = head;

    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            printf("ʳƷ����: %s\n", current->data.name);
            printf("������: %s\n", current->data.expiration_date);
            printf("����: %d\n", current->data.quantity);
            return;
        }

        current = current->next;
    }

    printf("�Ҳ�����ʳƷ��\n");
}

/**
 * ��ӡ����ʳƷ
 * �����������߿�ı��
 */
void findAllItem() {
    Node* current = head;

    //�����ͷ
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("�� ʳƷ����\t\t�� ������\t\t�� ����\t\t\t\t��\n");
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");

    // ��������
    while (current != NULL) {
        // ���ʳƷ��Ϣ
        printf("�� %-20s\t�� %-20s\t�� %-25d\t��\n", current->data.name, current->data.expiration_date, current->data.quantity);

        // ָ����һ���ڵ�
        current = current->next;
        //����ָ���
        printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    }

    //�����β
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
}

/**
 * �������ʳƷ
 * @param date  ����
 */
void checkExpirationDate(char date[50]){
    Node* current = head;

    //�����ͷ
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("�� ʳƷ����\t\t�� ������\t\t�� ����\t\t\t\t��\n");
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");

    // ��������
    while (current != NULL) {
        // �ж��Ƿ�Ϊ����ʳƷ
        /**
         * strcmp()�����Ƚ������ַ��� str1 �� str2����������ֵ���£�
         * �������ֵ < 0�����ʾ str1 С�� str2��
         * �������ֵ > 0�����ʾ str2 С�� str1��
         * �������ֵ = 0�����ʾ str1 ���� str2��
         */
         //�����Ƕ�ת��Ϊ���ֱȽ�
         int date1 = atoi(current->data.expiration_date);
         int date2 = atoi(date);
        if (date1 < date2) {
            // ���ʳƷ��Ϣ
            printf("�� %-20s\t�� %-20s\t�� %-25d\t��\n", current->data.name, current->data.expiration_date, current->data.quantity);
            //����ָ���
            printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
        }

        // ָ����һ���ڵ�
        current = current->next;
    }

    //�����β
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");

}

/**
 * ���������Ƶ ��ȡ��ǰ���ڲ����ñȽ�
 * �û�����
 * ������ʾ�� 2024-01-01 ����20240101
 * �����ʱ����ǰ��һ����
 */
void checkExpirationDate(){
    //��ȡ��ǰ����
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);
    int year = lt->tm_year + 1900;
    int month = lt->tm_mon + 1;
    int day = lt->tm_mday;
    //����ǰ����ת��Ϊ����
    int date = year * 10000 + month * 100 + day;
    //����ǰ����ת��Ϊ�ַ���
    char str[50];
    sprintf(str, "%d", date);
    //����ǰ���������һ����
    date = date + 100;
    //������ת��Ϊ�ַ���
    char str2[50];
    sprintf(str2, "%d", date);
    //��ӡ����ǰ����
    printf("��ǰ����Ϊ��%s\n", str);
    //���ü������ʳƷ����
    checkExpirationDate(str2);
}



// ��ӡ�˵�
void printMenu() {
    //������ɫ
    system("color a");
    // ��ӡ�˵�
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��\t\t\t\t\t\t\t\t\t\t��\n");
    printf("��\t\t\t��ӭʹ��ʳƷ������ϵͳ\t\t\t\t��\n");
    printf("��\t\t\t\t\t\t\t\t\t\t��\n");
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��\t\t\t\t\t\t\t\t\t\t��\n");
    printf("��\t\t\t1. ���ʳƷ\t\t\t\t\t\t��\n");
    printf("��\t\t\t2. ɾ��ʳƷ\t\t\t\t\t\t��\n");
    printf("��\t\t\t3. �޸�ʳƷ����\t\t\t\t\t\t��\n");
    printf("��\t\t\t4. ����ʳƷ\t\t\t\t\t\t��\n");
    printf("��\t\t\t5. �鿴����ʳƷ\t\t\t\t\t\t��\n");
    printf("��\t\t\t6. ʹ��˵��\t\t\t\t\t\t��\n");
    printf("��\t\t\t7. ��������ʳƷ\t\t\t\t\t\t��\n");
    //�������ʳƷ
    printf("��\t\t\t8. �������ʳƷ\t\t\t\t\t\t��\n");
    printf("��\t\t\t9. �˳�ϵͳ\t\t\t\t\t\t��\n");
    printf("��\t\t\t\t\t\t\t\t\t\t��\n");
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("�����������ţ�");
}

void useIndex() {
    //���ļ��е����ݶ�ȡ��������
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
                printf("������ʳƷ���ƣ�");
                scanf("%s", name);
                printf("�����뱣���ڣ�");
                scanf("%s", expiration_date);
                printf("������������");
                scanf("%d", &quantity);

                FoodItem newItem;
                strcpy(newItem.name, name);
                strcpy(newItem.expiration_date, expiration_date);
                newItem.quantity = quantity;

                insertItem(newItem);
                saveToFile();
                printf("ʳƷ��ӳɹ���\n");
                break;

            case 2:
                printf("������Ҫɾ����ʳƷ���ƣ�");
                scanf("%s", name);
                deleteItem(name);
                saveToFile();
                break;

            case 3:
                printf("������Ҫ�޸�������ʳƷ���ƣ�");
                scanf("%s", name);
                printf("�������µ�������");
                scanf("%d", &quantity);
                updateQuantity(name, quantity);
                saveToFile();
                break;

            case 4:
                printf("������Ҫ���ҵ�ʳƷ���ƣ�");
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
                printf("�ټ���\n");
                break;

            default:
                printf("��Ч��ѡ��\n");
                break;
        }
    } while (choice != 9);
    //��⵽�û�����9ʱ�˳�ѭ��
}
