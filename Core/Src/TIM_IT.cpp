/*
 * TIM_IT.cpp
 *
 *  Created on: Sep 14, 2023
 *      Author: rabbi
 */

/************** F446RE **************/

#include "TIM_IT.h"

double angle_hz = 0.0;
double angle_ev = 0.0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){

	if(htim->Instance == TIM5){
		shooter();
		shooter_base();
	}
}
