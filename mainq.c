// Максимова Дарья
// ИУ4-32Б
// Реализация односвязанного списка

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

typedef struct node {
    int val;
    struct node * next;
} node_t;

// Добавление элемента в начало списка
void push(node_t **head, int data) {
    node_t *tmp = (node_t*) malloc(sizeof(node_t));
    tmp->val = data;
    tmp->next = (*head);
    (*head) = tmp;
}


//Удаление элемента в начале списка
int pop(node_t **head) {
    node_t * prev = NULL;
    int val;
    if (head == NULL) {
        exit(-1);
    }
    prev = (*head);
    val = prev->val;
    (*head) = (*head)->next;
    free(prev);
    return val;
}

//Получение указателя на n-ный элемент
node_t * getNth(node_t * head, int n) {
    int counter = 0;
    while (counter < n && head) {
        head = head->next;
        counter++;
    }
    return head;
}

//Получение указателя на последний элемент
node_t * getLast(node_t *head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->next) {
        head = head->next;
    }
    return head;
}

//Получение указателя на предпоследний элемент
node_t * getLastButOne(node_t * head) {
    if (head == NULL) {
        exit(-2);
    }
    if (head->next == NULL) {
        return NULL;
    }
    while (head->next->next) {
        head = head->next;
    }
    return head;
}

//Добавление элемента в конец списка
void pushBack(node_t *head, int value) {
    node_t *last = getLast(head);
    node_t *tmp = (node_t *) malloc(sizeof(node_t));
    tmp->val = value;
    tmp->next = NULL;
    last->next = tmp;
}

//Вывод всего списка
void printLinkedList(const node_t *head) {
    while (head) {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

//Удаление элемента с конца списка
void popBack(node_t **head) {
    node_t *lastbn = NULL;
    //Получили NULL
    if (!head) {
        exit(-1);
    }
    //Список пуст
    if (!(*head)) {
        exit(-1);
    }
    lastbn = getLastButOne(*head);
    //Если в списке один элемент
    if (lastbn == NULL) {
        free(*head);
        *head = NULL;
    } else {
        free(lastbn->next);
        lastbn->next = NULL;
    }
}

//Добавление элемента на определенную позицию в списке
void insert(node_t *head, unsigned n, int val) {
    unsigned i = 0;
    node_t *tmp = NULL;
    //Находим нужный элемент. Если вышли за пределы списка, то выходим из цикла,
    //ошибка выбрасываться не будет, произойдёт вставка в конец
    while (i < n && head->next) {
        head = head->next;
        i++;
    }
    tmp = (node_t *) malloc(sizeof(node_t));
    tmp->val = val;
    //Если это не последний элемент, то next перекидываем на следующий узел
    if (head->next) {
        tmp->next = head->next;
        //иначе на NULL
    } else {
        tmp->next = NULL;
    }
    head->next = tmp;
}

//Формирование списка из массива элементов
void fromArray(node_t **head, int *arr, size_t size) {
    size_t i = size - 1;
    if (arr == NULL || size == 0) {
        return;
    }
    do {
        push(head, arr[i]);
    } while(i--!=0);
}

//Удаление элемента под определенным номером
int deleteNth(node_t **head, int n) {
    if (n == 0) {
        return pop(head);
    } else {
        node_t *prev = getNth(*head, n-1);
        node_t *elm  = prev->next;
        int val = elm->val;

        prev->next = elm->next;
        free(elm);
        return val;
    }
}

//Удаление всего списка
void deleteList(node_t **head) {
    node_t * prev = NULL;
    while ((*head)->next) {
        prev = (*head);
        (*head) = (*head)->next;
        free(prev);
    }
    free(*head);
}

int main() {

    setlocale(LC_ALL, "Russian");
    node_t * head = NULL;
    int arr[] = {1,2,3,4,5,6,7,8,9,10};

    printf("Создаём список из массива [1:10]");
    fromArray(&head, arr, 10);
    //
    printLinkedList(head);
    //
    printf("Вставляем узел со значением 333 после 4-го элемента (станет пятым)");
    insert(head, 4, 333);
    printLinkedList(head);
    //
    printf("Добавляем в конец элементы с 11 по 14");
    pushBack(head, 11);
    pushBack(head, 12);
    pushBack(head, 13);
    pushBack(head, 14);
    printLinkedList(head);
    //
    printf("Удаляем элемент в начале");
    pop(&head);
    printLinkedList(head);
    printf("Удаляем эелемент в конце");
    popBack(&head);
    printLinkedList(head);
    //
    printf("Удаляем пятый элемент (индексация с нуля)");
    deleteNth(&head, 4);
    printLinkedList(head);
    printf("Удаляем весь список. Конец программы...");
    deleteList(&head);
    //
    return 0;

}