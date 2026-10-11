#include <stdio.h>
#include <string.h>

#define MAX_TRANSACTIONS 1000
#define DATE 11
#define CATEGORY 30

char dates[MAX_TRANSACTIONS][DATE];
char categories[MAX_TRANSACTIONS][CATEGORY];
float amounts[MAX_TRANSACTIONS];
int incomes[MAX_TRANSACTIONS];

int transCount = 0;

void addTrans() {
    if (transCount >= MAX_TRANSACTIONS) {
        printf("Transaction limit reached.\n");
        return 0;
    }

    printf("Enter date (YYYY-MM-DD): ");
    scanf("%10s", *(dates + transCount));

    printf("Enter Category: ");
    scanf("%29s", *(categories + transCount));

    printf("Enter amount: ");
    scanf("%f", *(amounts + transCount));

    printf("Is this Income? (1 for YES, 0 for NO): ");
    scanf("%d", *(incomes + transCount));

    transCount++;
    printf("Transaction added successfully.\n");
}