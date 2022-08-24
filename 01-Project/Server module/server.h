/**
 * @file server.h
 * @author Adel Mostafa (adelmostafa389@gmail.com)
 * @brief This file include the typedefs and functions prototype related to the SERVER module
 * @version 0.1
 * @date 2022-08-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef SERVER_H
#define SERVER_H

/************************************* Include Section ******************************************/
#include "../STD_TYPES.h"
#include "../Terminal module/terminal.h"


/************************************** Macros Section ******************************************/
#define ACCOUNTS_DATA_BASE_length 255
#define TRANSACTIONS_DATA_BASE_length 3

/***************************** Typedefs and Declaration Section *********************************/
typedef enum EN_transState_t
{
    APPROVED,
    DECLINED_EXPIRED_CARD,
    DECLINED_EXCEED_MAX_AMMOUNT,
    DECLINED_INSUFFECIENT_FUND,
    DECLINED_STOLEN_CARD,
    INTERNAL_SERVER_ERROR
}En_transState_t;

typedef enum En_serverError_t
{
    OK_server = 0,
    SAVING_FAILED,
    TRANSACTION_NOT_FOUND,
    ACCOUNT_NOT_FOUND,
    LOW_BALANCE
}En_serverError_t;

typedef struct ST_transactionData_t{
    St_cardData_t cardHolderData;
    St_terminalData_t terminalData;
    En_transState_t transState;
    uint32_t transactionSequenceNumber;
}St_transactionData_t;

typedef struct St_accountsDB_t {
    uint8_t primaryAccountNumber[PAN_length];
    float balance;
}St_accountsDB_t ;

extern St_accountsDB_t  serverAccountsDataBase[ACCOUNTS_DATA_BASE_length];
extern St_transactionData_t serverTransactionsDataBase[TRANSACTIONS_DATA_BASE_length];

/****************************** Functions prototypes Section ***********************************/

/**
 * @brief This function will take all transaction data and validate its data.
 *
 * @param transData
 * @return EN_transState_t
 */
En_transState_t recieveTransactionData(St_transactionData_t *transData);

/**
 * @brief
 *
 * @param transactionData
 * @param serverData
 * @return En_serverError_t
 */
En_serverError_t isAmountAvailable (St_terminalData_t *terminalData);

/**
 * @brief Verify the Primary Account Number(PAN)
 *
 * @param cardData
 * @param serverData
 * @return En_serverError_t
 */
En_serverError_t isValidAccount(St_cardData_t* cardData);

/**
 * @brief Saves the transaction details into the server-side database
 *
 * @param transaction_l
 * @return En_serverError_t
 */
En_serverError_t saveTransaction(St_transactionData_t* transaction_l);

/**
 * @brief Get the Transaction object
 *
 * @param transactionSequenceNumber
 * @param transData
 * @return EN_serverError_t
 */
En_serverError_t getTransaction(uint32_t transactionSequenceNumber, St_transactionData_t *transData);

#endif
