/**
 * @file Application.h
 * @author Adel Mostafa (adelmostafa389@gmail.com)
 * @brief This file contains the regular typedefs in the payment project
 * @version 0.1
 * @date 2022-08-19
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef APPLICATION_H
#define APPLICATION_H
/************************************* Include Section ******************************************/
#include <string.h>
#include <stdio.h>

#include "STD_TYPES.h"
#include "Server module/server.h"

/***************************** Typedefs and Declaration Section *********************************/
typedef struct St_date_t{
    int day;
    int month;
    int year;
}St_date_t;


/****************************** Functions prototypes Section ***********************************/

void appStart(void);
void handle_card_data_error(EN_cardError_t error);
void handle_terminal_data_error(En_terminalError_t error);
void handle_transaction_data_error(En_transState_t error);


#endif
