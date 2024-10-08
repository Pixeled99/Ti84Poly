#include <tice.h>
#include <stdlib.h>
#include <math.h>

void int_to_str(int num, char *str) {
    int i = 0;
    int is_negative = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (num < 0) {
        is_negative = 1;
        num = -num;
    }

    while (num != 0) {
        str[i++] = (num % 10) + '0';
        num /= 10;
    }

    if (is_negative) {
        str[i++] = '-';
    }

    str[i] = '\0';

    for (int j = 0; j < i / 2; j++) {
        char temp = str[j];
        str[j] = str[i - j - 1];
        str[i - j - 1] = temp;
    }
}

struct Node {
    int value;
    struct Node *next;
};

struct Node* add(struct Node* current, int value){
    current->value = value;
    struct Node *new = malloc(sizeof(struct Node)); 
    new->value = 0;
    new->next = NULL;
    current->next = new;
    return new;
}

int get(struct Node* head, int index){
    int iterations = 0;
    while (head->next != NULL || iterations != index){
        iterations++;
        head = head->next;
    }
    return head->value;
}

struct Node* find_factors(int number){
    struct Node *head = malloc(sizeof(struct Node));
    struct Node *next = head;
    int max_divisor = sqrt(number);
    for (int divisor = 1; divisor < max_divisor+1; divisor++){
        if (number % divisor == 0){
            next = add(next, divisor);
            next = add(next, -divisor);
            next = add(next, number / divisor);
            next = add(next, -number / divisor);
            
        }
    }
    return head;

};

int main(void) {
    struct Node *head = malloc(sizeof(struct Node));
    struct Node *next = head;
    os_ClrHome();
    
    int size = 0;
    char input[5];
    char terms[2];
    char str[12];

    os_PutStrFull("How many terms?");
    os_NewLine();
    os_GetStringInput("",terms,2);
    os_NewLine();
    
    for (int i = 0; i < terms[0] - '0'; i++){
        int number = 0;
        int negative = 1;
        os_PutStrFull("Term X^");
        int_to_str(i, str);
        os_PutStrFull(str);
        os_PutStrFull(":");
        os_GetStringInput("",input,5);
        os_NewLine();
        for (int j = 0; j < 5; j++){
            if (input[j] == '\0'){
                size = j-1;
                break;
            }
        }
        for (int j = 0; j <= size; j++){
            if ((int) input[j] == 26){
                negative = -1;
            }
            else{
                number += ((int) (input[j] - '0'))*((int) (pow(10,size-j)+0.1));
            }
        }
        next = add(next, number * negative);
    }

    struct Node* options = find_factors(head->value);
    while (options->next != NULL){
        int power = 0;
        int result = 0;
        next = head;
        while (next->next != NULL){
            result += next->value * ((int) round(pow(options->value,power)));
            next = next->next;
            power++;
        }
        if (result == 0){
            os_ClrHome();
            int_to_str(options->value, str);
            os_PutStrFull(str);
            while (!os_GetCSC()){}
            return 0; 
        }
        options = options->next;
    }
    os_ClrHome();
    os_PutStrFull("Idk");
    while (!os_GetCSC()){}

    return 0;
}