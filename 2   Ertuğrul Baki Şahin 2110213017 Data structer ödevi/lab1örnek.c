#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

// Stack veri yapısı
struct Stack {
    int top;
    char items[MAX_SIZE];
};

// Stack fonksiyonları
void createEmptyStack(struct Stack *stack) {
    stack->top = -1;
}

void push(struct Stack *stack, char item) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack is full.");
    } else {
        stack->top++;
        stack->items[stack->top] = item;
    }
}

char pop(struct Stack *stack) {
    if (stack->top == -1) {
        printf("Stack is empty.");
        return '\0';
    } else {
        char item = stack->items[stack->top];
        stack->top--;
        return item;
    }
}

// Parantez kontrol fonksiyonu
bool isBalanced(char *text) {
    struct Stack stack;
    createEmptyStack(&stack);
    char ch;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] == '(' || text[i] == '{' || text[i] == '[') {
            push(&stack, text[i]);
        } else if (text[i] == ')' || text[i] == '}' || text[i] == ']') {
            if (stack.top == -1) {
                return false;
            }
            ch = pop(&stack);
            if ((ch == '(' && text[i] != ')') || (ch == '{' && text[i] != '}') || (ch == '[' && text[i] != ']')) {
                return false;
            }
        }
    }
    return (stack.top == -1);
}

// Dosyadan okuma ve kontrol işlemleri
int main() {
    FILE *filePointer;
    char filename[] = "kod.txt";
    char character;
    char text[MAX_SIZE];
    int index = 0;

    // Dosyayı okuma
    filePointer = fopen(filename, "r");
    if (filePointer == NULL) {
        perror("Dosya açılırken hata oluştu.\n");
        exit(EXIT_FAILURE);
    }

    // Dosyadaki metni okuma
    while ((character = fgetc(filePointer)) != EOF) {
        text[index++] = character;
    }
    text[index] = '\0';

    // Parantez kontrolü
    if (isBalanced(text)) {
        printf("Parantezler dengeli.\n");
    } else {
        printf("Parantezler dengeli değil.\n");
    }
    fclose(filePointer);
    return 0;
}
