/**
 * @file server.c
 * @author Adel Mostafa (adelmostafa389@gmail.com)
 * @brief This file includes the functions implementation related to the SERVER module
 * @version 0.1
 * @date 2022-08-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "server.h"
#include <string.h>

uint8_t card_index = 0;

/**
 * @brief Server-side accounts database
 *
 */
St_accountsDB_t  serverAccountsDataBase[ACCOUNTS_DATA_BASE_length] ={
    {"123456789012345678", 500.00},
    {"234567891123456789", 6000.00},
    {"567891234987654321", 3250.25},
    {"123456789456789123", 1200.12},
    {"987654321258649137", 100.00},
    {"126547856654823719", 2100.00},
    {"798751354971362485", 0.00},
    {"123546871793148625", 1.00},
    {"658973248123123456", 10.12},
    {"456784562871389321", 0.55}
};

/**
 * @brief Server-side transactions database
 *
 */
St_transactionData_t serverTransactionsDataBase[TRANSACTIONS_DATA_BASE_length] = {0};


/**
 * @brief This function will take all transaction data and validate its data.
 *
 * @param transData
 * @return EN_transState_t
 */
En_transState_t recieveTransactionData(St_transactionData_t *transData){
    En_transState_t retVal = APPROVED;
    // check the Primary Account Number(PAN)
    if(OK_server != isValidAccount(&(transData->cardHolderData))){
        retVal = DECLINED_STOLEN_CARD;
    }
    // check the expiratiation date of the card
    else if(OK_terminal != isCardExpried(&transData->cardHolderData, &transData->terminalData)){
        retVal = DECLINED_EXPIRED_CARD;
    }
    // check the account balance
    else if(OK_server != isAmountAvailable (&transData->terminalData)){
        retVal = DECLINED_INSUFFECIENT_FUND;
    }
    // check if the amount is available in the terminal
    else if(OK_terminal != isBelowMaxAmount(&(transData->terminalData))){
        retVal = DECLINED_EXCEED_MAX_AMMOUNT;
    }
    else{
        retVal = APPROVED;
    }
    // update the account balance if the transaction is approved successfully
    if(APPROVED == transData->transState){
        serverAccountsDataBase[card_index].balance -= transData->terminalData.transAmount;
    }
    else{/*Do Nothing*/}
    transData->transState = retVal;
    return retVal;
}

/**
 * @brief Verify the Primary Account Number(PAN)
 *
 * @param cardData
 * @return En_serverError_t
 */
En_serverError_t isValidAccount(St_cardData_t* cardData){
    uint8_t counter1 = 0;
    En_serverError_t retVal = ACCOUNT_NOT_FOUND;
    uint8_t cmpResult = 0;
    for(counter1 = 0; counter1 < ACCOUNTS_DATA_BASE_length; counter1++){
        cmpResult = strcmp(cardData->primaryAccountNumber, serverAccountsDataBase[counter1].primaryAccountNumber);
        if(0 == cmpResult){
            retVal = OK_server;
            card_index = counter1;
            break;
        }
    }
    return retVal;
}

/**
 * @brief This function will take terminal data and validate these data.
 *
 * @param transactionData
 * @param serverData
 * @return En_serverError_t
 */
En_serverError_t isAmountAvailable (St_terminalData_t *terminalData){
    En_serverError_t retVal = LOW_BALANCE;
    if(terminalData->transAmount > serverAccountsDataBase[card_index].balance){
        retVal = LOW_BALANCE;
    }
    else{
        retVal = OK_server;
    }
    return retVal;
}

/**
 * @brief This function will take all transaction data into the transactions database.
 *
 * @param transaction_l
 * @return En_serverError_t
 */
En_serverError_t saveTransaction(St_transactionData_t* transaction_l){
    En_serverError_t retVal = SAVING_FAILED;
    static uint8_t transactions_index = 0;
    static uint32_t sequenceNumber = 1;
    if(transactions_index > (TRANSACTIONS_DATA_BASE_length-1)){
        retVal = SAVING_FAILED;
    }
    else{
        transaction_l->transactionSequenceNumber = sequenceNumber;
        serverTransactionsDataBase[transactions_index] = *transaction_l;
        sequenceNumber++;
        transactions_index++;
        retVal = OK_server;
    }
    return retVal;
}

