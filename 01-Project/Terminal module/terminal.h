/**
 * @file terminal.h
 * @author Adel Mostafa (adelmostafa389@gmail.com)
 * @brief This file includes the typedefs and functions prototype related to the TERMINAL module
 * @version 0.1
 * @date 2022-08-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef TERMINAL_H
#define TERMINAL_H

/************************************* Include Section ******************************************/
#include "../STD_TYPES.h"
#include "../Card module/card.h"

/***************************** Typedefs and Declaration Section *********************************/
typedef enum En_terminalError_t
{
    OK_terminal = 0,
    WRONG_DATE,
    EXPIRED_CARD,
    INVALID_CARD,
    INVALID_AMOUNT,
    EXCEED_MAX_AMOUNT,
    INVALID_MAX_AMOUNT
}En_terminalError_t ;

typedef struct St_terminalData_t{
    float transAmount;
    float maxtransAmount;
    uint8_t transactionDate[11];
}St_terminalData_t;

/****************************** Functions prototypes Section ***********************************/

/**
 * @brief Get the Transaction Date
 *
 * @param terminal_l
 * @return En_terminalError_t
 */
En_terminalError_t getTransactionDate(St_terminalData_t* terminal_l);

/**
 * @brief This function compares the card expiry date with the transaction date.
 *
 * @param terminalData
 * @param cardData
 * @return En_terminalError_t
 */
En_terminalError_t isCardExpried(St_cardData_t *cardData, St_terminalData_t *terminalData);

/**
 * @brief Get the required transaction amount
 *
 * @param terminalData
 * @return En_terminalError_t
 */
En_terminalError_t gatTransactionAmount(St_terminalData_t *terminalData);

/**
 * @brief Check if the amount is accepted by the terminal
 * (If it isless than the daily maximum transaction amount)
 *
 * @param terminalData
 * @return En_terminalError_t
 */
En_terminalError_t isBelowMaxAmount(St_terminalData_t *terminalData);

/**
 * @brief This function sets the maximum allowed amount into terminal data.
 *
 * @param terminalData
 * @return En_terminalError_t
 */
En_terminalError_t setMaxAmount(St_terminalData_t *terminalData);

#endif
