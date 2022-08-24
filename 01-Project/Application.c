/**
 * @file main.c
 * @author Adel Mostafa (adelmostafa389@gmail.com)
 * @brief This project is a simulation of Payment System transaction process
 * @version 0.1
 * @date 2022-05-16
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "Application.h"

St_transactionData_t transaction1;

EN_cardError_t cardRetVal = OK_card;
En_terminalError_t terminalRetVal = OK_terminal;
En_serverError_t serverRetVal = APPROVED;
En_transState_t transactionRetVal = APPROVED;

int main(){
    setMaxAmount(&transaction1.terminalData);
    char answer = 'y';
    while('y' == answer){
        appStart();
        /*==== Check if the User wants to continue with other transaction ====*/
        printf("\nDo you want to continue with another proccess(y/n)?:\n");
        fflush(stdin);
        scanf("%c", &answer);
        printf("*************************\n");
    }
    return 0;
}


void appStart(void){
    printf("\n======== Please Enter Card Data ========\n");
    cardRetVal = getCardHolderName(&transaction1.cardHolderData);
    cardRetVal = getCardPAN(&transaction1.cardHolderData);
    cardRetVal = getCardExpiryDate(&transaction1.cardHolderData);
    printf("\n======== Please Enter Terminal Data ========\n");
    terminalRetVal = gatTransactionAmount(&transaction1.terminalData);
    terminalRetVal = getTransactionDate(&transaction1.terminalData);
    /*======= send transaction data to the server and verfying the data ======*/
    printf("\nVerifying Data from the server.....\n..\n...\n....\n.....");
    transactionRetVal = recieveTransactionData(&transaction1);
    handle_transaction_data_error(transactionRetVal);
}

void handle_card_data_error(EN_cardError_t error){
    switch (error){
    case OK_card:
        printf("The CARD data is OK.\n");
        break;
    case WRONG_NAME:
        printf("Wrong card holder Name!!...\n");
        break;
    case WRONG_EXP_DATE:
        printf("Wrong expiry date!! Dosn't match the format (MM/YY)...\n");
        break;
    case WRONG_PAN:
        printf("Invalid Primary Account Number!!...\n");
        break;
    default:
        break;
    }
}

void handle_terminal_data_error(En_terminalError_t error){
    switch (error){
    case OK_terminal:
        printf("The TERMINAL data is OK.\n");
        break;
    case WRONG_DATE:
        printf("Wrong Transaction date!! Dosn't match the format (DD/MM/YYYY)...\n");
        break;
    case EXPIRED_CARD:
        printf("Expired Card!!...\n");
        break;
    case INVALID_CARD:
        printf("Invalid Card!!...\n");
        break;
    case INVALID_AMOUNT:
        printf("Invalid amount!!...\n");
        break;
    case EXCEED_MAX_AMOUNT:
        printf("Transaction amount excced the maximum amount!!...\n");
        break;
    case INVALID_MAX_AMOUNT:
        printf("The Maximum Daily amount is Wrong!!...\n");
        break;
    default:
        break;
    }
}

void handle_transaction_data_error(En_transState_t error){
    switch (error){
    case APPROVED:
        printf("The Transaction is APPROVED.\n");
        break;
    case DECLINED_EXPIRED_CARD:
        printf("The Card is expired!!...\n");
        break;
    case DECLINED_EXCEED_MAX_AMMOUNT:
        printf("The Maximum Daily amount per card is 5000.00$!!...\n");
        break;
    case DECLINED_STOLEN_CARD:
        printf("Invalid Card!!...\n");
        break;
    case DECLINED_INSUFFECIENT_FUND:
        printf("The Card balance is not enogh!!...\n");
        break;
    case INTERNAL_SERVER_ERROR:
        printf("Something went wrong with the SERVER");
        break;
    default:
        break;
    }
}

void handle_server_data_error(En_serverError_t error){
    switch (error){
    case OK_server:
        printf("The server data is OK.\n");
        break;
    case SAVING_FAILED:
        printf("Saving failed!!...\n");
        break;
    case TRANSACTION_NOT_FOUND:
        printf("Transaction not found...\n");
        break;
    case ACCOUNT_NOT_FOUND:
        printf("Account not found!!...\n");
        break;
    case LOW_BALANCE:
        printf("Account Balance isn't enough!!...\n");
        break;
    default:
        break;
    }
}
