/**
 * @file terminal.c
 * @author Adel Mostafa (adelmostafa389@gmail.com)
 * @brief This file includes the functions implementation related to the TERMINAL module
 * @version 0.1
 * @date 2022-08-19
 *
 * @copyright Copyright (c) 2022
 *
 */


#include "terminal.h"
#include <stdio.h>
#include <string.h>

/**
 * @brief Get the Transaction Date
 *
 * @param terminal_l
 * @return En_terminalError_t
 */
En_terminalError_t getTransactionDate(St_terminalData_t* terminal_l){
    En_terminalError_t retVal = WRONG_DATE ;
    uint8_t DateLength = 0;
    printf("Please Enter transaction Date: (DD/MM/YYYY)\n");
    fflush(stdin);
    gets(terminal_l->transactionDate);
    DateLength = strlen(terminal_l->transactionDate);
    if((DateLength != 10) || (terminal_l->transactionDate[2] != '/') || (terminal_l->transactionDate[5] != '/')){
        retVal = WRONG_DATE;
    }
    else{
        retVal = OK_terminal;
    }
    return retVal;
}

/**
 * @brief Check if the card is expired
 *
 * @param cardData
 * @param terminalData
 * @return En_terminalError_t
 */
En_terminalError_t isCardExpried(St_cardData_t *cardData, St_terminalData_t *terminalData){
    En_terminalError_t retVal = EXPIRED_CARD;
    uint8_t expYear = 0;
    uint8_t expMonth = 0;
    uint8_t transYear = 0;
    uint8_t transMonth = 0;
    expMonth = ((cardData->cardExpiryDate[0] - '0') * 10) + (cardData->cardExpiryDate[1] - '0');
    expYear = ((cardData->cardExpiryDate[3] - '0') * 10 ) + (cardData->cardExpiryDate[4] - '0');
    transMonth = ((terminalData->transactionDate[3] - '0') * 10) + (terminalData->transactionDate[4] - '0');
    transYear = ((terminalData->transactionDate[8] - '0') * 10) + (terminalData->transactionDate[9] - '0');
    if(transYear > expYear){
        retVal = EXPIRED_CARD;
    }
    else if(transYear == expYear){
        if(transMonth > expMonth){
            retVal = EXPIRED_CARD;
        }
        else{
            retVal = OK_terminal;
        }
    }
    else{
        retVal = OK_terminal;
    }
    return retVal;
}

/**
 * @brief Get the required transaction amount
 *
 * @param terminalData
 * @return En_terminalError_t
 */
En_terminalError_t gatTransactionAmount(St_terminalData_t *terminalData){
    En_terminalError_t retVal = OK_terminal;
    printf("Please Enter the Transaction Amount: \n");
    scanf("%f", &(terminalData->transAmount));
    if((terminalData->transAmount) <= 0){
        retVal = INVALID_AMOUNT;
    }
    else{
        retVal = OK_terminal;
    }
    return retVal;
}

/**
 * @brief Check if the amount is accepted by the terminal
 * (If it isless than the daily maximum transaction amount)
 *
 * @param terminalData
 * @return En_terminalError_t
 */
En_terminalError_t isBelowMaxAmount(St_terminalData_t *terminalData){
    En_terminalError_t retVal = EXCEED_MAX_AMOUNT;
    if (terminalData->transAmount > terminalData->maxtransAmount){
        retVal = EXCEED_MAX_AMOUNT;
    }
    else{
        retVal = OK_terminal;
    }
    return retVal;
}

/**
 * @brief This function sets the maximum allowed amount into terminal data.
 *
 * @param terminalData
 * @return En_terminalError_t
 */
En_terminalError_t setMaxAmount(St_terminalData_t *terminalData){
    En_terminalError_t retVal = OK_terminal;
    printf("Please Enter the Maximum Transaction Amount: \n");
    scanf("%f", &(terminalData->maxtransAmount));
    if((terminalData->maxtransAmount) <= 0){
        retVal = INVALID_MAX_AMOUNT ;
    }
    else{
        retVal = OK_terminal;
    }
    return retVal;
}
