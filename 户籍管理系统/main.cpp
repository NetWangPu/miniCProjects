#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/**
 * ����Ա��������admin
 */

// ������Ϣ�ṹ��
typedef struct {
    char name[50];       // ����
    char id[20];         // ���֤��
    char gender[10];     // �Ա�
    int age;             // ����
    char address[100];   // סַ
    char note[100];      // ��ע��Ϣ
    char regDate[20];    // ע������
} Household;

// �ڵ�ṹ��
typedef struct Node {
    Household data;      // ����
    struct Node* next;   // ��һ���ڵ��ָ��
} Node;

// ͷ�ڵ�
Node* head = NULL;

// ���ļ��м������ݵ�����
void loadFromFile() {
    // ���ļ�
    FILE* file = fopen("C:\\data.txt", "r");  // ���ļ����ж�ȡ
    // �ж��ļ��Ƿ�򿪳ɹ�
    if (file == NULL) {
        printf("�޷����ļ���\n");
        return;
    }

    // ��ȡ�ļ��е�ÿһ������
    while (!feof(file)) {
        // �����µĻ�����Ϣ�ṹ��
        Household newHousehold;
        // ���ļ��ж�ȡÿ���ֶε�ֵ���������µĻ�����Ϣ�ṹ��
        if (fscanf(file, "%s %s %s %d %s %s %s\n", newHousehold.regDate, newHousehold.name, newHousehold.id,
                   &newHousehold.age, newHousehold.gender, newHousehold.address, newHousehold.note) == 7) {
            // �����½ڵ�
            Node* newNode = (Node*)malloc(sizeof(Node));
            // ��������Ϣ�ṹ������½ڵ�
            newNode->data = newHousehold;
            // ���½ڵ��nextָ��ָ��NULL
            newNode->next = NULL;

            // ��������
            if (head == NULL) {
                // �������Ϊ�գ����½ڵ���Ϊͷ�ڵ�
                head = newNode;
            } else {
                // �������Ϊ�գ����½ڵ���뵽����ĩβ
                Node* current = head;
                // �ҵ�����ĩβ
                while (current->next != NULL) {
                    // ��currentָ��ָ����һ���ڵ�
                    current = current->next;
                }
                // ���½ڵ���뵽����ĩβ
                current->next = newNode;
            }
        }
    }

    fclose(file);  // �ر��ļ�
}

// �����������ݵ��ļ�
void saveToFile() {
    // ���ļ�
    FILE* file = fopen("C:\\data.txt", "w");  // ���ļ�����д��
    // �ж��ļ��Ƿ�򿪳ɹ�
    if (file == NULL) {
        // ����ļ���ʧ�ܣ������������Ϣ
        printf("�޷����ļ���\n");
        return;
    }

    // ��������
    Node* current = head;
    // ���������е�ÿ���ڵ�
    while (current != NULL) {
        // ��ÿ���ֶε�ֵд���ļ�
        fprintf(file, "%s %s %s %d %s %s %s\n", current->data.regDate, current->data.name, current->data.id,
                current->data.age, current->data.gender, current->data.address, current->data.note);
        // ��currentָ��ָ����һ���ڵ�
        current = current->next;
    }

    // �ر��ļ�
    fclose(file);  // �ر��ļ�
}

// ע�ủ��
void registerHousehold() {
    printf("��������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    // �����µĻ�����Ϣ�ṹ��
    Household newHousehold;

    // �ӿ���̨��ȡÿ���ֶε�ֵ���������µĻ�����Ϣ�ṹ��
    printf("������ע�����ڣ�");
    scanf("%s", newHousehold.regDate);

    printf("������������");
    scanf("%s", newHousehold.name);

    printf("���������֤�ţ�");
    scanf("%s", newHousehold.id);

    printf("�������Ա�");
    scanf("%s", newHousehold.gender);

    printf("���������䣺");
    scanf("%d", &newHousehold.age);

    printf("������סַ��");
    scanf("%s", newHousehold.address);

    printf("�����뱸ע��Ϣ��");
    scanf("%s", newHousehold.note);

    // �����½ڵ�
    Node* newNode = (Node*)malloc(sizeof(Node));
    // ��������Ϣ�ṹ������½ڵ�
    newNode->data = newHousehold;
    // ���½ڵ��nextָ��ָ��NULL
    newNode->next = NULL;

    // ��������
    if (head == NULL) {
        // �������Ϊ�գ����½ڵ���Ϊͷ�ڵ�
        head = newNode;
    } else {
        // �������Ϊ�գ����½ڵ���뵽����ĩβ
        Node* current = head;
        // �ҵ�����ĩβ
        while (current->next != NULL) {
            // ��currentָ��ָ����һ���ڵ�
            current = current->next;
        }
        // ���½ڵ���뵽����ĩβ
        current->next = newNode;
    }

    printf("����ע��ɹ���\n");
}

// ע������
void cancelHousehold() {
    printf("��������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    // �ӿ���̨��ȡ���֤��
    char id[20];
    // �ӿ���̨��ȡÿ���ֶε�ֵ���������µĻ�����Ϣ�ṹ��
    printf("������Ҫע�������֤�ţ�");
    scanf("%s", id);

    // ��������
    Node* current = head;
    Node* prev = NULL;
    // ���������е�ÿ���ڵ�
    while (current != NULL) {
        // �жϵ�ǰ�ڵ��Ƿ�ΪҪע���Ļ���
        if (strcmp(current->data.id, id) == 0) {
            // ����ǣ���ɾ����ǰ�ڵ�
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            // �ͷŵ�ǰ�ڵ���ڴ�
            free(current);
            printf("����ע���ɹ���\n");
            return;
        }
        prev = current;
        // ��currentָ��ָ����һ���ڵ�
        current = current->next;
    }

    printf("δ�ҵ���Ӧ���֤�ŵĻ�����\n");
}

// ������ѯ
void searchHousehold() {
    printf("��������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    // �ӿ���̨��ȡ��ѯ�ؼ���
    char keyword[50];
    printf("�������ѯ�ؼ��ʣ�");
    scanf("%s", keyword);

    // ��������
    Node* current = head;
    int count = 0;

    // ���������е�ÿ���ڵ�
    while (current != NULL) {
        if (strcmp(current->data.name, keyword) == 0 || strcmp(current->data.id, keyword) == 0) {
            printf("������%s\n", current->data.name);
            printf("���֤�ţ�%s\n", current->data.id);
            printf("�Ա�%s\n", current->data.gender);
            printf("���䣺%d\n", current->data.age);
            printf("סַ��%s\n", current->data.address);
            printf("��ע��Ϣ��%s\n", current->data.note);
            printf("ע�����ڣ�%s\n", current->data.regDate);
            printf("------------------------------\n");
            count++;
        }
        // ��currentָ��ָ����һ���ڵ�
        current = current->next;
    }

    // �ж��Ƿ��ҵ����������Ļ���
    if (count == 0) {
        printf("δ�ҵ����������Ļ�����\n");
    }
}

// ����ע����������
void sortByDate() {
    // �ж������Ƿ�Ϊ��
    if (head == NULL || head->next == NULL) {
        return;
    }

    // ð������
    int swapped;
    Node* current;
    Node* last = NULL;

    do {
        // ����swapped��־
        swapped = 0;
        current = head;

        // ���������е�ÿ���ڵ�
        while (current->next != last) {
            //��ȡ��ǰ�ڵ������
            Household currentData = current->data;
            Household nextData = current->next->data;
            //�������ַ���ת��Ϊint�����ٱȽ�
            int currentYear = atoi(currentData.regDate);
            int nextYear = atoi(nextData.regDate);
            // �Ƚ����������ڵ��ע������
            if (currentYear > nextYear) {
                // �����ڵ�����
                Household temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            // ��currentָ��ָ����һ���ڵ�
            current = current->next;
        }
        // ����lastָ��
        last = current;
    } while (swapped);
}

// ������Ϣ����
void modifyHousehold() {
    printf("��������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    // �ӿ���̨��ȡ���֤��
    char id[20];
    // �ӿ���̨��ȡÿ���ֶε�ֵ���������µĻ�����Ϣ�ṹ��
    printf("������Ҫ���ĵĻ��������֤�ţ�");
    scanf("%s", id);

    // ��������
    Node* current = head;

    // ���������е�ÿ���ڵ�
    while (current != NULL) {
        // �жϵ�ǰ�ڵ��Ƿ�ΪҪ���ĵĻ���
        if (strcmp(current->data.id, id) == 0) {
            printf("�������µ�������");
            scanf("%s", current->data.name);

            printf("�������µ��Ա�");
            scanf("%s", current->data.gender);

            printf("�������µ����䣺");
            scanf("%d", &(current->data.age));

            printf("�������µ�סַ��");
            scanf("%s", current->data.address);

            printf("�������µı�ע��Ϣ��");
            scanf("%s", current->data.note);

            printf("������Ϣ���ĳɹ���\n");
            return;
        }
        current = current->next;
    }

    printf("δ�ҵ���Ӧ���֤�ŵĻ�����\n");
}

// ��ѯ���л���
void displayAllHouseholds() {
    // �ж������Ƿ�Ϊ��
    Node* current = head;
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��                                   ������Ϣ                                    ��\n");
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");

    // ���������е�ÿ���ڵ�
    while (current != NULL) {
        printf("������%s\n", current->data.name);
        printf("���֤�ţ�%s\n", current->data.id);
        printf("�Ա�%s\n", current->data.gender);
        printf("���䣺%d\n", current->data.age);
        printf("סַ��%s\n", current->data.address);
        printf("��ע��Ϣ��%s\n", current->data.note);
        printf("ע�����ڣ�%s\n", current->data.regDate);
        printf("------------------------------\n");

        // ��currentָ��ָ����һ���ڵ�
        current = current->next;
    }
}


// �����������
void clearAllData() {
    printf("��������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    // �ӿ���̨��ȡ����Ա����
    char password[20];
    printf("���������Ա���룺");
    scanf("%s", password);

    // �������Ա����Ϊ "admin"
    if (strcmp(password, "admin") != 0) {
        printf("��������޷�ɾ�����ݣ�\n");
        return;
    }

    // �ӿ���̨��ȡȷ����Ϣ
    char confirm[10];
    printf("ȷ��Ҫ�������������(���� 'yes' ȷ��): ");
    scanf("%s", confirm);

    // �ж��û������ȷ����Ϣ
    if (strcmp(confirm, "yes") != 0) {
        printf("ȡ��������ݲ�����\n");
        return;
    }

    // ���������е�ÿ���ڵ㣬�ͷ��ڴ�
    Node* current = head;
    Node* next;

    // ���������е�ÿ���ڵ�
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    // ��headָ����ΪNULL
    head = NULL;
    printf("������������գ�\n");
}



// ʹ��˵��
void printInstructions() {
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��\t\t\t\t��������ϵͳ\t\t\t\t��\n");
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��\t�ó���ʵ����һ���򵥵Ļ�������ϵͳ��������ʹ������ѡ�������Ӧ������\t��\n");
    printf("��\t1. ע�ủ��������µĻ�����Ϣ��ϵͳ��\t\t\t\t\t��\n");
    printf("��\t2. ע����������ϵͳ��ɾ��ָ�����֤�ŵĻ�����Ϣ��\t\t\t��\n");
    printf("��\t3. ������ѯ���������������֤�Ų�ѯ���������Ļ�����Ϣ��\t\t\t��\n");
    printf("��\t4. ����ע���������򣺶Ի�����Ϣ����ע�����ڽ�������\t\t\t��\n");
    printf("��\t5. ������Ϣ���ģ��޸�ָ�����֤�ŵĻ�����Ϣ��\t\t\t\t��\n");
    printf("��\t6. ��ѯ���л�������ʾϵͳ�����еĻ�����Ϣ��\t\t\t\t��\n");
    printf("��\t7. ����������ݣ����ϵͳ�����еĻ�����Ϣ��\t\t\t\t��\n");
    printf("��\t8. ʹ��˵������ʾ�ó����ʹ��˵����\t\t\t\t\t��\n");
    printf("��\t9. �˳�ϵͳ���˳���������ϵͳ��\t\t\t\t\t��\n");
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
//    printf("============= ��������ϵͳ =============\n");
//    printf("�ó���ʵ����һ���򵥵Ļ�������ϵͳ��\n");
//    printf("������ʹ������ѡ�������Ӧ������\n");
//    printf("1. ע�ủ��������µĻ�����Ϣ��ϵͳ��\n");
//    printf("2. ע����������ϵͳ��ɾ��ָ�����֤�ŵĻ�����Ϣ��\n");
//    printf("3. ������ѯ���������������֤�Ų�ѯ���������Ļ�����Ϣ��\n");
//    printf("4. ����ע���������򣺶Ի�����Ϣ����ע�����ڽ�������\n");
//    printf("5. ������Ϣ���ģ��޸�ָ�����֤�ŵĻ�����Ϣ��\n");
//    printf("6. ��ѯ���л�������ʾϵͳ�����еĻ�����Ϣ��\n");
//    printf("7. �˳����˳���������ϵͳ��\n");
//    printf("8. ʹ��˵������ʾ�ó����ʹ��˵����\n");
//    printf("9. ����������ݣ����ϵͳ�����еĻ�����Ϣ��\n");
//    printf("=======================================\n");
}

void wecomeUserInfo(){
    // ��ӡ��ӭ��Ϣ
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("��\t\t\t\t��ӭʹ�û�������ϵͳ\t\t\t\t��\n");
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
    printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");

}


// ����Ա��¼
bool adminLogin() {
    wecomeUserInfo();
    // �ӿ���̨��ȡ����Ա����
    int remainingAttempts = 3;

    // ��ೢ��3��
    while (remainingAttempts > 0) {
        // �ӿ���̨��ȡ����Ա����
        char password[20];
        printf("����Ա��¼\n");
        printf("���������룺");
        scanf("%s", password);

        // �������Ա����Ϊ "admin"
        if (strcmp(password, "admin") == 0) {
            // ��¼�ɹ�
            printf("��¼�ɹ���\n");
            return true;
        } else {
            // ��¼ʧ��
            printf("������󣡻��� %d �γ��Ի��ᡣ\n", remainingAttempts - 1);
            remainingAttempts--;
        }
    }

    // ��¼ʧ��
    printf("��¼ʧ�ܣ��Ѵﵽ����Դ�����\n");
    return false;
}


int main() {
    // ����Ա��¼
    if (!adminLogin()) {
        return 0;
    }
    system("cls");
    wecomeUserInfo();
    // ���ļ��е����ݶ�ȡ��������
    loadFromFile();

    int choice;
    int running = 1;
    while (running) {
        printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��\t\t\t\t��������ϵͳ\t\t\t\t\t��\n");
        printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
        printf("��\t�ó���ʵ����һ���򵥵Ļ�������ϵͳ��������ʹ������ѡ�������Ӧ������\t��\n");
        printf("��\t\t\t\t1. ע�ủ��\t\t\t\t\t��\n");
        printf("��\t\t\t\t2. ע������\t\t\t\t\t��\n");
        printf("��\t\t\t\t3. ������ѯ\t\t\t\t\t��\n");
        printf("��\t\t\t\t4. ����ע����������\t\t\t\t��\n");
        printf("��\t\t\t\t5. ������Ϣ����\t\t\t\t\t��\n");
        printf("��\t\t\t\t6. ��ѯ���л���\t\t\t\t\t��\n");
        printf("��\t\t\t\t7. �������\t\t\t\t\t��\n");
        printf("��\t\t\t\t8. ʹ��˵��\t\t\t\t\t��\n");
        printf("��\t\t\t\t9. �˳�ϵͳ\t\t\t\t\t��\n");
        printf("������������������������������������������������������������������������������������������������������������������������������������������������������������������\n");
//        printf("��������ϵͳ\n");
//        printf("1. ע�ủ��\n");
//        printf("2. ע������\n");
//        printf("3. ������ѯ\n");
//        printf("4. ����ע����������\n");
//        printf("5. ������Ϣ����\n");
//        printf("6. ��ѯ���л���\n");
//        printf("7. �˳�\n");
//        printf("������ѡ����ţ�");
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
                printf("����������ɣ�\n");
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
                printf("��Чѡ�\n");
                break;
        }

        saveToFile(); // ÿ�β����󱣴����ݵ��ļ�
    }

    return 0;
}
