/*
 * shooter_base.cpp
 *
 *  Created on: Sep 14, 2023
 *      Author: rabbi
 */

/************** F446RE **************/

#include "shooter_base.h"

int16_t enc_hz = 0;
int16_t enc_ev = 0;

double target_hz = 0.0; //SP
double target_ev=0.0; //SP
int hz_ok = 0;
int ev_ok = 0;

double et_hz = 0.0;
double et_ev = 0.0;
double sigma_et_hz = 0.0;
double sigma_et_ev = 0.0;
double ut_hz = 0.0;
double ut_ev = 0.0;
double last_et_hz = 0.0;
double last_et_ev = 0.0;

double P_hz = 0.3;
double I_hz = 0.02;
double D_hz = 0.015;

double P_ev = 0.3;
double I_ev = 0.02;
double D_ev = 0.007;

//double hz[5000];
//int hz_cnt = 0;
//double ev[5000];
//int ev_cnt = 0;

void shooter_base(){

//horizontal angle
	enc_hz = __HAL_TIM_GetCounter(&htim2);
	angle_hz += 360*((double)enc_hz/(4*resolution_hz*ratio_hz))*2;	//PV
//	hz[hz_cnt] = angle_hz/360/span_hz;
	__HAL_TIM_SetCounter(&htim2, 0);
//	hz_cnt++;

	//et
	et_hz = target_hz - angle_hz;
	sigma_et_hz += et_hz;

	//ut -> pulse
	ut_hz = P_hz*et_hz /*+ I_hz*sigma_et_hz*span_hz + D_hz*(et_hz-last_et_hz)/span_hz*/;	//PID Control
	if(ut_hz > 0.5) ut_hz = 0.5;
	else if(ut_hz < -0.5) ut_hz = -0.5;

	if(ut_hz>0){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	}
	else if(ut_hz<0){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_SET);
	}
	else if(ut_hz==0){
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, GPIO_PIN_RESET);
	}
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_1,fabs(ut_hz)*20000);

	//record et
	last_et_hz = et_hz;

//elevation angle
	enc_ev = __HAL_TIM_GetCounter(&htim3);
	angle_ev += 360*((double)enc_ev/(4*resolution_ev*ratio_ev))*2;	//PV
//	ev[ev_cnt] = angle_ev/360/span_ev;
	__HAL_TIM_SetCounter(&htim3, 0);
//	ev_cnt++;

	//et
	et_ev = target_ev - angle_ev;
	sigma_et_ev += et_ev;

	//ut -> pulse
	ut_ev = P_ev*et_ev + I_ev*sigma_et_ev*span_ev + D_ev*(et_ev-last_et_ev)/span_ev;	//PID Control
	if(ut_ev > 0.5) ut_ev = 0.5;
	else if(ut_ev < -0.5) ut_ev = -0.5;

	if(ut_ev>0){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	}
	else if(ut_ev<0){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_SET);
	}
	else if(ut_ev==0){
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9, GPIO_PIN_RESET);
	}
	__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_2,fabs(ut_ev)*20000);

	//record et
	last_et_ev = et_ev;
}

//bool reset = 0;
//bool hz_neg;	//negative limit
//bool hz_origin;	//zero
//bool hz_pos;	//positive limit
//bool ev_origin;	//zero
//
//void reset(){
//
//	button_hz = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4);
//	button_ev = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5);
//
//	if(reset){
//		while(){
//			if(angle_hz > 0){
//				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PI_SET);
//				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);
//			}
//			else if(angle_hz < 0){
//				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET);
//				HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
//			}
//		}
//	}
//}
