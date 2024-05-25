#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[100];
} element;

typedef struct listNode {
    element data;
    struct listNode* link;
} ListNode;

ListNode* insert_first(ListNode* h, element value) {
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    if (p == NULL) {
        printf("Memory allocation error\n");
        return h;
    }
    p->data = value;
    p->link = h;
    h = p;
    return h;
}

ListNode* insert(ListNode* head, ListNode* pre, element value) {
    if (pre == NULL) {
        printf("Error: pre is NULL\n");
        return head;
    }
    ListNode* p = (ListNode*)malloc(sizeof(ListNode));
    if (p == NULL) {
        printf("Memory allocation error\n");
        return head;
    }
    p->data = value;
    p->link = pre->link;    //순서<1>
    pre->link = p;          //<2>
    return head;
}

void print_list(ListNode* h) {
    while (h != NULL) {
        printf("%s -> ", h->data.name);
        h = h->link;
    }
    printf("NULL\n");
}

ListNode* delete_first(ListNode* head, ListNode** delete_list) {
    if (head == NULL)
        return NULL;
    ListNode* remove = head;
    head = remove->link;
    *delete_list = insert_first(*delete_list, remove->data);
    free(remove);
    return head;
}

ListNode* delete(ListNode* head, ListNode* pre, ListNode** delete_list) {
    if (pre == NULL || pre->link == NULL) {
        printf("Error: invalid node to delete\n");
        return head;
    }
    ListNode* remove = pre->link;
    pre->link = remove->link;
    *delete_list = insert_first(*delete_list, remove->data);
    free(remove);
    return head;
}

ListNode* search_list(ListNode* head, char* name) {
    ListNode* p = head;
    while (p != NULL) {
        if (strcmp(p->data.name, name) == 0)
            return p;
        p = p->link;
    }
    return NULL;
}

int main() {
    ListNode* head = NULL;
    ListNode* delete_list = NULL;
    element data;
    int choice;
    char input[100];

    // 초기 과일 목록
    char* fruits[] = { "Peach", "Banana", "Raspberry", "Guava", "Plum", "Cherry", "Grape", "Apple", "Orange", "Mango" };
    for (int i = 0; i < 10; i++) {
        strcpy(data.name, fruits[i]);
        head = insert_first(head, data);
    }

    while (1) {
        printf("\n메뉴:\n");
        printf("1. 새로운 과일 추가\n");
        printf("2. 리스트 내 과일 삭제\n");
        printf("3. 삭제한 과일 목록 출력\n");
        printf("4. 프로그램 종료\n");
        printf("선택하세요: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            print_list(head);
            printf("삽입할 과일 이름을 입력하세요: ");
            scanf("%s", input);
            strcpy(data.name, input);

            if (search_list(head, input) == NULL) {
                head = insert_first(head, data);
            }
            else {
                printf("입력한 과일은 이미 존재합니다.\n");
            }
            print_list(head);
            break;
        case 2:
            printf("삭제할 과일 이름을 입력하세요: ");
            scanf("%s", input);
            ListNode* delete_fruit = search_list(head, input);
            if (delete_fruit != NULL) {
                if (delete_fruit == head) {
                    head = delete_first(head, &delete_list);
                }
                else {
                    ListNode* prev = head;
                    while (prev->link != delete_fruit) {
                        prev = prev->link;
                    }
                    head = delete(head, prev, &delete_list);
                }
                printf("과일이 삭제되었습니다.\n");
            }
            else {
                printf("해당 과일은 없습니다.\n");
            }
            print_list(head);
            break;
        case 3:
            printf("삭제한 과일 목록: ");
            print_list(delete_list);
            break;
        case 4:
            printf("프로그램 종료\n");
            return 0;
        default:
            printf("유효하지 않은 선택입니다.\n");
        }
    }
    return 0;
}
