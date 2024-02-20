#ifndef INCLUDE_GAURD

#define INCLUDE_GAURD 1
#include <stdio.h>
#include <stdlib.h>
#include "StrList.h"
#endif

#define DEFAULT_STRING_LENGTH 20
#define PRINT_COMMANDS 0

char* scan_string() {
    char* string = (char*)malloc(DEFAULT_STRING_LENGTH);
    char character = ' ';
    int name_len = DEFAULT_STRING_LENGTH, j = 0;
    while (character == ' ' || character == '\n') {
        scanf("%c", &character);
    }
    while (character != ' ' && character != '\n' && character != EOF) { // loop until done scanning name
        if (j + 1 >= name_len) { // handles cases of long names (longer than 20 characters). leaves space for '\0'
            // printf("J = %d\n",j); // DEBUG
            name_len *= 2;
            string = (char*)realloc(string, name_len); // allocate more memory for name
        }
        string[j++] = character;
        // printf("CHARA: %c\n", string[j-1]); // DEBUG
        scanf("%c", &character);
    }
    string[j] = '\0';
    return string;
}

int main() {
    if (PRINT_COMMANDS == 1) {
        printf("Program StrList initiated.\n");
    }
    char c = '?';
    StrList* list = NULL;
    while (c != '0' && c != EOF) {
        scanf("%c", &c);
        if (c == '0') {
            break;
        }
        while (c == ' ') {
            scanf("%c", &c);
        }

        if (c == '1') {
            scanf("%c", &c);
            if (c == ' ' || c == '\n') {
                int string_num;
                scanf("%d", &string_num);
                if (string_num < 1) {
                    printf("Invalid number of strings.\n");
                }
                else {
                    StrList_free(list); // frees memory of previous list (if existed)
                    list = StrList_alloc();
                    int counter = 0;
                    char* string;
                    while (counter < string_num) {
                        string = scan_string();
                        StrList_insertLast(list, string);
                        free(string); // frees scanned string memory
                        counter++;
                    }
                    if (PRINT_COMMANDS == 1) {
                        printf("List created.\n");
                    }
                }
            }
            else if (c == '0') {
                StrList_reverse(list);
                if (PRINT_COMMANDS == 1) {
                    printf("Reversed list.\n");
                }
                c = '?';
            }
            else if (c == '1') {
                StrList_free(list);
                list = NULL;
                if (PRINT_COMMANDS == 1) {
                    printf("Deleted the list.\n");
                }
            }
            else if (c == '2') {
                StrList_sort(list);
                if (PRINT_COMMANDS == 1) {
                    printf("Sorted list.\n");
                }
            }
            else if (c == '3') {
                int sorted = StrList_isSorted(list);
                if (sorted == 1) {
                    printf("true\n");
                }
                else {
                    printf("false\n");
                }
            }
        }
        else if (c == '2') {
            int index;
            scanf("%d", &index);
            char* string = scan_string();
            StrList_insertAt(list, string, index);
            if (PRINT_COMMANDS == 1) {
                printf("Inserted '%s' to index %d.\n", string, index);
            }
            free(string); // frees scanned string memory

        }
        else if (c == '3') {
            StrList_print(list);
        }
        else if (c == '4') {
            if (PRINT_COMMANDS == 1) {
                printf("List size: ");
            }
            printf("%zu\n", StrList_size(list));
        }
        else if (c == '5') {
            int index;
            scanf("%d", &index);
            if (PRINT_COMMANDS == 1) {
                printf("String at index %d is: ", index);
            }
            StrList_printAt(list, index);
        }
        else if (c == '6') {
            if (PRINT_COMMANDS == 1) {
                printf("Char number in list: ");
            }
            printf("%d\n", StrList_printLen(list));
        }
        else if (c == '7') {
            char* string = scan_string();
            if (PRINT_COMMANDS == 1) {
                printf("The string '%s' number of appearances in the list: ", string);
            }
            printf("%d\n", StrList_count(list, string));
            free(string);
        }
        else if (c == '8') {
            char* string = scan_string();
            StrList_remove(list, string);
            if (PRINT_COMMANDS == 1) {
                printf("Deleted all instances of the string '%s' from the list.\n", string);
            }
            free(string);
        }
        else if (c == '9') {
            int index;
            scanf("%d", &index);
            StrList_removeAt(list, index);
            if (PRINT_COMMANDS == 1) {
                printf("Removed element in index %d from the list.\n", index);
            }
        }
    }
    free(list);

    return 0;
}
