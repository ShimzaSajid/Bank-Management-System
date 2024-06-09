#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct acc_detail {
    char acc_num[20];
    char name[50];
    char password[10];
    float balance;
};

int main() {
    struct acc_detail user, user1;
    int choice;
    FILE *fp;
    char fileName[30];
    char enter_acc[30], enter_pass[10];
    float amount;

    printf("\n What do you want to do?");
    printf("\n1. Create an account");
    printf("\n2. Login to an account");
    printf("\n\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        system("cls");
        printf("Enter the account number: ");
        scanf("%s", user.acc_num);
        printf("Enter your name: ");
        scanf("%s", user.name);
        printf("Create your password: ");
        scanf("%s", user.password);
        user.balance = 0;

        strcpy(fileName, user.acc_num);
        fp = fopen(strcat(fileName, ".dat"), "w");

        if (fp != NULL) {
            fwrite(&user, sizeof(struct acc_detail), 1, fp);
            fclose(fp);
            printf("\n\nAccount Created!");
        } else {
            printf("Error!! Something went wrong");
        }
    } else if (choice == 2) {
        system("cls");
        printf("\nEnter account number to login: ");
        scanf("%s", enter_acc);
        printf("\nEnter password to login: ");
        scanf("%s", enter_pass);

        strcpy(fileName, enter_acc);
        fp = fopen(strcat(fileName, ".dat"), "r");

        if (fp == NULL) {
            printf("\nAccount is not present");
        } else {
            fread(&user, sizeof(struct acc_detail), 1, fp);
            fclose(fp);

            if (!strcmp(enter_pass, user.password)) {
                do {
                    system("cls");
                    printf("1) Enter 1 to check balance\n");
                    printf("2) Enter 2 to deposit money\n");
                    printf("3) Enter 3 to transfer money\n");
                    printf("4) Enter 4 to withdraw money\n");
                    printf("5) Enter 5 to check transaction history\n");
                    printf("6) Enter 6 to check account detail\n");
                    printf("7) Enter 7 to exit program\n");
                    printf("Enter choice: ");
                    scanf("%d", &choice);

                    switch (choice) {
                        case 1:
                            printf("Your current balance is Rs.%.2f", user.balance);
                            break;
                        case 2:
                            printf("Enter the deposited amount: ");
                            scanf("%f", &amount);
                            user.balance += amount;

                            fp = fopen(fileName, "w");

                            if (fp != NULL) {
                                fwrite(&user, sizeof(struct acc_detail), 1, fp);
                                fclose(fp);
                                printf("\nSuccessfully deposited");
                            } else {
                                printf("Error opening file");
                            }
                            break;
                        case 3:
                            printf("Enter the account to which money is to transfer: ");
                            scanf("%s", enter_acc);
                            printf("\nEnter the amount: ");
                            scanf("%f", &amount);

                            strcpy(fileName, enter_acc);
                            fp = fopen(strcat(fileName, ".dat"), "r");

                            if (fp == NULL) {
                                printf("\nAccount not registered ");
                            } else {
                                fread(&user1, sizeof(struct acc_detail), 1, fp);
                                fclose(fp);
                            }

                            if (amount > user.balance) {
                                printf("\nInsufficient balance!!!");
                            } else {
                                fp = fopen(fileName, "w");
                                user1.balance += amount;
                                fwrite(&user1, sizeof(struct acc_detail), 1, fp);
                                fclose(fp);

                                if (fp != NULL) {
                                    printf("\nYou have transferred Rs %.2f to %s", amount, enter_acc);
                                    strcpy(fileName, user.acc_num);
                                    fp = fopen(strcat(fileName, ".dat"), "w");
                                    user.balance -= amount;
                                    fwrite(&user, sizeof(struct acc_detail), 1, fp);
                                    fclose(fp);
                                } else {
                                    printf("Error opening file");
                                }
                            }
                            break;
                        
                        case 4:
    printf("Enter the account to which money is to transfer: ");
    scanf("%s", enter_acc);
    printf("\nEnter the amount: ");
    scanf("%f", &amount);

    strcpy(fileName, enter_acc);
    fp = fopen(strcat(fileName, ".dat"), "r");

    if (fp == NULL) {
        printf("\nAccount not registered ");
    } else {
        fclose(fp);  // Close the file after checking existence

        // Open the file for reading user1 details
        fp = fopen(fileName, "r");
        fread(&user1, sizeof(struct acc_detail), 1, fp);
        fclose(fp);

        if (amount > user.balance) {
            printf("\nInsufficient balance!!!");
        } else {
            // Open the file for writing user1 details
            fp = fopen(fileName, "w");
            user1.balance += amount;
            fwrite(&user1, sizeof(struct acc_detail), 1, fp);
            fclose(fp);

            // Open the file for writing user details
            strcpy(fileName, user.acc_num);
            fp = fopen(strcat(fileName, ".dat"), "w");
            user.balance -= amount;
            fwrite(&user, sizeof(struct acc_detail), 1, fp);
            fclose(fp);

            // Display the success message
            printf("\nYou have transferred Rs %.2f to %s", amount, enter_acc);
        }
    }
    break;


                        default:
                            printf("Invalid choice. Please enter a valid option.\n");
                            break;
                    }
                } while (choice != 7);
            } else {
                printf("Invalid Password");
            }
        }
}

    return 0;
}

