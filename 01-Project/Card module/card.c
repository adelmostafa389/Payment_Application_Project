/**
 * @file card.c
 * @author Adel Mostafa (adelmostafa389@gmail.com)
 * @brief This file includes the functions implementation related to the CARD module
 * @version 0.1
 * @date 2022-08-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "card.h"
#include "stdio.h"

/**
 * @brief This function will ask for the cardholder's name and store it into card data.
 *
 * @param card_l
 * @return EN_cardError_t
 */
EN_cardError_t getCardHolderName(St_cardData_t* card_l){
        EN_cardError_t retval = WRONG_NAME;
        uint8_t HolderNameLength = 0;
        printf("Please Enter the Card Holder Name: \n");
        fflush(stdin);
        gets(card_l->cardHolderName);
        HolderNameLength = strlen(card_l->cardHolderName);
        if((HolderNameLength > 24) || (HolderNameLength < 20)){
                retval = WRONG_NAME;
        }
        else{
                retval = OK_card;
        }
        return retval;
}

/**
 * @brief This function will ask for the card expiry date and store it in card data.
 *
 * @param card_l
 * @return EN_cardError_t
 */
EN_cardError_t getCardExpiryDate(St_cardData_t* card_l){
        EN_cardError_t retval = WRONG_EXP_DATE;
        uint8_t expDateLength = 0;
        printf("Please Enter Card Expiry Date: (MM/YY)\n");
        fflush(stdin);
        gets(card_l->cardExpiryDate);
        expDateLength = strlen(card_l->cardExpiryDate);
        if((expDateLength != 5) || (card_l->cardExpiryDate[2] != '/')){
                retval = WRONG_EXP_DATE;
        }
        else{
                retval = OK_card;
        }
        return retval;
}

/**
 * @brief This function will ask for the card's Primary Account Number and store it in card data.
 *
 * @param card_l
 * @return EN_cardError_t
 */
EN_cardError_t getCardPAN (St_cardData_t* card_l){
        EN_cardError_t retval = WRONG_PAN ;
        uint8_t PANLength = 0;
        printf("Please Enter the Primary Account Number: \n");
        fflush(stdin);
        gets(card_l->primaryAccountNumber);
        PANLength = strlen(card_l->primaryAccountNumber);
        if((PANLength < 16) || (PANLength > 19)){
                retval = WRONG_PAN ;
        }
        else{
                retval = OK_card;
        }
        return retval;
}
