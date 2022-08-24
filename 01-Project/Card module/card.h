/**
 * @file card.h
 * @author Adel Mostafa (adelmostafa389@gmail.com)
 * @brief This file include the typedefs and functions prototype related to the CARD module
 * @version 0.1
 * @date 2022-08-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef CARD_H
#define CARD_H

/************************************* Include Section ******************************************/
#include "../STD_TYPES.h"

/************************************** Macros Section ******************************************/
#define PAN_length 20

/***************************** Typedefs and Declaration Section *********************************/
typedef enum EN_cardError_t
{
    OK_card, 
    WRONG_NAME, 
    WRONG_EXP_DATE, 
    WRONG_PAN
}EN_cardError_t;

typedef struct St_cardData_t{
    char cardHolderName[24];
    uint8_t primaryAccountNumber[PAN_length];
    uint8_t cardExpiryDate[6];
    //St_date_t cardDate_st;
}St_cardData_t;

/****************************** Functions prototypes Section ***********************************/

/**
 * @brief This function will ask for the cardholder's name and store it into card data.
 * 
 * @param card_l 
 * @return EN_cardError_t 
 */
EN_cardError_t getCardHolderName(St_cardData_t* card_l);

/**
 * @brief This function will ask for the card expiry date and store it in card data.
 * 
 * @param card_l 
 * @return EN_cardError_t 
 */
EN_cardError_t getCardExpiryDate(St_cardData_t* card_l);

/**
 * @brief This function will ask for the card's Primary Account Number and store it in card data.
 * 
 * @param card_l 
 * @return EN_cardError_t 
 */
EN_cardError_t getCardPAN(St_cardData_t* card_l);

#endif
