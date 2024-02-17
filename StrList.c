#ifndef INCLUDE_GAURD

#define INCLUDE_GAURD 1
#include <stdio.h>
#include <stdlib.h>
#include "StrList.h"
#endif

#include <string.h>

////////////////////////// Auxilary Functions ////////////////////////////////

/*
    Prints error regarding memory allocation.
*/
void __printAllocProblem(char* func_name) {
    fprintf(stderr, "ERROR: CAN'T ALLOCATE MEMORY IN '%s'.\n", func_name);
}

/*
    Return 1 if given char* is not empty (or NULL), otherwise 0.
*/
int __is_data_valid(const char* data) {
    if (data == NULL || strlen(data) == 0) {
        fprintf(stderr, "ERROR: INVALID DATA.\n");
        return 0;
    }
    return 1;
}

//////////////////////////////// NODE ///////////////////////////////////////

typedef struct _node {
    char* _data;
    struct _node* _prev;
    struct _node* _next;
} Node;

Node* Node_alloc(char* data, Node* prev, Node* next) {
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL) {
        __printAllocProblem("Node_alloc");
        return NULL;
    }
    p->_data = data;
    p->_prev = prev; // MIGHT NOT WORK
    p->_next = next; // MIGHT NOT WORK
    return p;
}

void Node_free(Node* node) {
    // printf("FREE MEM\n"); // TEST
    free(node->_data);
    free(node);
}

void Node_print(Node* node) {
    if (node != NULL) {
        printf("%s", node->_data);
        return;
    }
    char* null = NULL;
    printf("%s", null);
}

/*
    Clones a Node, doesn't copy pointers _next and _prev, simply deep clones string (_data).
*/
Node* Node_clone(Node* node) {
    size_t length = strlen(node->_data);
    char* new_data = malloc((length + 1) * sizeof(char)); // also allocates space for '\0' in the end of the string
    strcpy(new_data, node->_data);
    return Node_alloc(new_data, NULL, NULL);
}

//////////////////////////////// LIST ///////////////////////////////////////

struct _StrList {
    Node* _head;
    Node* _tail;
    size_t _size;
    size_t _charAmount;
};

/*
    Returns 1 if given list is valid, 0 otherwise.
*/
int __is_list_valid(const StrList* list) {
    if (list == NULL) {
        fprintf(stderr, "ERROR: INVALID LIST.\n");
        return 0;
    }
    return 1;
}

/*
    Returns 1 if given list is empty, 0 otherwise. Assumes list is valid.
*/
int __is_list_empty(const StrList* list) {
    if (list->_size > 0) {
        return 0;
    }
    return 1;
}

/*
    Returns 1 if given index is in range of given list, 0 otherwise.
*/
int is_index_valid(const StrList* list, int index) {
    if (__is_list_valid(list) == 0 || __is_list_empty(list) == 1) {
        return 0;
    }
    if (index < 0 || index >= list->_size) {
        fprintf(stderr, "ERROR: INDEX '%d' IS OUT OF RANGE.\n", index);
        return 0;
    }
    return 1;
}

StrList* StrList_alloc() {
    StrList* p = (StrList*)malloc(sizeof(StrList));
    if (p == NULL) {
        __printAllocProblem("StrList_alloc");
        return NULL;
    }
    p->_head = NULL;
    p->_tail = NULL;
    p->_size = 0;
    p->_charAmount = 0;
    return p;
}

void StrList_free(StrList* list) {
    if (list == NULL) return;
    Node* p1 = list->_head;
    Node* p2;
    while (p1) {
        p2 = p1;
        p1 = p1->_next;
        Node_free(p2);
    }
    free(list);
}

size_t StrList_size(const StrList* list) {
    if (__is_list_valid(list) == 0) {
        return 0;
    }
    return list->_size;
}

void StrList_insertLast(StrList* list, const char* data) {
    StrList_insertAt(list, data, list->_size);
}

void StrList_insertAt(StrList* list, const char* data, int index) {
    if (__is_list_valid(list) == 0 || __is_data_valid(data) == 0) {
        return;
    }
    size_t list_size = list->_size;
    if (index < 0 || index > list_size) {
        fprintf(stderr, "ERROR: INVALID INDEX '%d'.\n", index);
        return;
    }

    size_t length = strlen(data);
    char* new_data = malloc((length + 1) * sizeof(char)); // also allocates space for '\0' in the end of the string
    if (new_data == NULL) {
        __printAllocProblem("StrList_insertAt");
        return;
    }
    strcpy(new_data, data);
    list->_size++;
    list->_charAmount += length;
    Node* new_node;
    if (index == 0) {
        new_node = Node_alloc(new_data, NULL, list->_head);
        if (list_size == 0) {
            list->_head = new_node;
            list->_tail = new_node;
        }
        else {
            list->_head->_prev = new_node;
            list->_head = new_node;
        }
        return;
    }
    else if (index == list_size) {
        new_node = Node_alloc(new_data, list->_tail, NULL);
        list->_tail->_next = new_node;
        list->_tail = new_node;
        return;
    }

    int start = 0;
    Node* n = list->_head;
    if (index <= list_size / 2) {
        while (start < index - 1) {
            n = n->_next;
            start++;
        }
    }
    else {
        start = list_size;
        n = list->_tail;
        while (start > index) {
            n = n->_prev;
            start--;
        }
    }
    // at this point 'n' should be the node that will preceed the future new node (or NULL)
    new_node = Node_alloc(new_data, n, n->_next);
    if (n != NULL) {
        n->_next = new_node;
    }
    if (new_node->_next != NULL) {
        new_node->_next->_prev = new_node;
    }


    // if (n == NULL) {
    //     new_node = Node_alloc(new_data, NULL, NULL);
    // }
    // else 
}

char* StrList_firstData(const StrList* list) {
    if (__is_list_valid(list) == 0 || __is_list_empty(list) == 1) {
        return NULL;
    }
    Node* h = list->_head;
    return h->_data;
}

void StrList_print(const StrList* list) {
    if (__is_list_valid(list) == 0) {
        return;
    }
    Node* n = list->_head;
    Node_print(n);
    n = n->_next;
    while (n != NULL) {
        printf(" ");
        Node_print(n);
        n = n->_next;
    }
    printf("\n");
}

/*
    Given an index and a list, get the string at that index.
*/
Node* get_Node_at(const StrList* list, int index) {
    if (is_index_valid(list, index) == 0) {
        return NULL;
    }
    size_t list_size = list->_size;
    Node* n;
    size_t counter = 0;
    if (index <= list_size / 2) {
        n = list->_head;
        while (counter < index) {
            n = n->_next;
            counter++;
        }
    }
    else {
        n = list->_tail;
        while (list_size - counter - 1 > index) {
            n = n->_prev;
            counter++;
        }
    }
    return n;
}

void StrList_printAt(const StrList* list, int index) {
    if (is_index_valid(list, index) == 0) {
        return;
    }
    Node* n = get_Node_at(list, index);
    Node_print(n);
    printf("\n");
}

int StrList_printLen(const StrList* list) {
    return list->_charAmount;
}

int StrList_count(StrList* list, const char* data) {
    if (__is_list_valid(list) == 0 || __is_list_empty(list) == 1 || __is_data_valid(data) == 0) {
        return 0;
    }

    Node* n = list->_head;
    int counter = 0;
    while (n != NULL) {
        if (strcmp(n->_data, data) == 0) {
            counter++;
        }
        n = n->_next;
    }

    return counter;
}

/*
    Removes a given Node n from a given list. Assumes n is inside the list.
*/
void __remove_node(StrList* list, Node* to_remove) {
    if (to_remove != list->_head && to_remove != list->_tail) {
        Node* prev = to_remove->_prev;
        Node* next = to_remove->_next;
        prev->_next = next;
        next->_prev = prev;
    }
    else {
        if (to_remove == list->_head) {
            list->_head = list->_head->_next;
            if (list->_head != NULL) {
                list->_head->_prev = NULL;
            }
        }
        if (to_remove == list->_tail) {
            list->_tail = list->_tail->_prev;
            if (list->_tail != NULL) {
                list->_tail->_next = NULL;
            }
        }
    }
    list->_size--;
    list->_charAmount -= strlen(to_remove->_data);
    Node_free(to_remove);
}

void StrList_remove(StrList* list, const char* data) {
    if (__is_list_valid(list) == 0 || __is_list_empty(list) == 1 || __is_data_valid(data) == 0) {
        return;
    }

    Node* n = list->_head;
    while (n != NULL) {
        if (strcmp(n->_data, data) == 0) {
            Node* temp = n;
            n = n->_next;
            __remove_node(list, temp);
        }
        else {
            n = n->_next;
        }
    }
}

void StrList_removeAt(StrList* list, int index) {
    if (is_index_valid(list, index) == 0) {
        return;
    }
    Node* to_remove = get_Node_at(list, index);
    __remove_node(list, to_remove);
}

int StrList_isEqual(const StrList* list1, const StrList* list2) {
    int valid1 = __is_list_valid(list1), valid2 = __is_list_valid(list2);
    if (valid1 == 0 || valid2 == 0) {
        if (valid1 == 0 && valid2 == 0) {
            return 1;
        }
        return 0;
    }
    int empty1 = __is_list_empty(list1), empty2 = __is_list_empty(list2);
    if (empty1 == 1 || empty2 == 1) {
        if (empty1 == 1 && empty2 == 1) {
            return 1;
        }
        return 0;
    }
    Node* n1 = list1->_head;
    Node* n2 = list2->_head;
    while (n1 != NULL) {
        if (strcmp(n1->_data, n2->_data) != 0) {
            return 0;
        }
        n1 = n1->_next;
        n2 = n2->_next;
    }
    return 1;
}

StrList* StrList_clone(const StrList* list) {
    if (list == NULL) {
        return NULL;
    }
    StrList* list_copy = StrList_alloc();
    list_copy->_size = list->_size;
    list_copy->_charAmount = list->_charAmount;
    list_copy->_head = Node_clone(list->_head);
    if (list->_size <= 1) {
        list_copy->_tail = list_copy->_head;
        return list_copy;
    }

    Node* n1 = list_copy->_head;
    Node* n2 = list->_head->_next;
    while (n2 != NULL) {
        n1->_next = Node_clone(n2);
        n1->_next->_prev = n1;
        n1 = n1->_next;
        n2 = n2->_next;
    }
    list_copy->_tail = n1->_next;
    return list_copy;
}

/*
    Swaps between 2 Nodes in a list. Assumes list and Nodes aren't NULL.
*/
void swap_Nodes(Node* n1, Node* n2) {
    char* temp = n1->_data;
    n1->_data = n2->_data;
    n2->_data = temp;
}

void StrList_reverse(StrList* list) {
    if (__is_list_valid(list) == 0 || list->_size <= 1) {
        return;
    }
    size_t counter = 0;
    size_t num = (list->_size - 1) / 2;
    Node* n1 = list->_head;
    Node* n2 = list->_tail;
    while (counter <= num) {
        n1 = n1->_next;
        n2 = n2->_prev;
        swap_Nodes(n1->_prev, n2->_next);
        counter++;
    }
}

/*
    Partition function to be used in quick sort algorithm.
*/
Node* partition(Node* first, Node* last)
{
    Node* pivot = first;
    Node* front = first;
    while (front != NULL && front != last) {
        if (strcmp(front->_data, last->_data) < 0) {
            pivot = first;
            swap_Nodes(first, front);
            first = first->_next;
        }
        front = front->_next;
    }
    swap_Nodes(first, last);
    return pivot;
}

/*
    Performs quick sort (recursively) on the given linked list. Assumes given Nodes are valid.
*/
void quick_sort(Node* first, Node* last)
{
    if (first == last) {
        return;
    }
    Node* pivot = partition(first, last);

    if (pivot != NULL && pivot->_next != NULL) {
        quick_sort(pivot->_next, last);
    }

    if (pivot != NULL && first != pivot) {
        quick_sort(first, pivot);
    }
}

void StrList_sort(StrList* list) {
    if (__is_list_valid(list) == 0 || list->_size <= 1) {
        return;
    }
    quick_sort(list->_head, list->_tail);
}

int StrList_isSorted(StrList* list) {
    if (__is_list_valid(list) == 0 || list->_size <= 1) {
        return 1;
    }
    Node* n = list->_head->_next;
    while (n != NULL) {
        if (strcmp(n->_prev->_data, n->_data) > 0) {
            return 0;
        }
        n = n->_next;
    }
    return 1;
}