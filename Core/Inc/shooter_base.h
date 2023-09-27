/*
 * shooter_base.h
 *
 *  Created on: Sep 14, 2023
 *      Author: rabbi
 */

/************** F446RE **************/

#ifndef INC_SHOOTER_BASE_H_
#define INC_SHOOTER_BASE_H_

#include "TIM_IT.h"
#include <math.h>

//horizontal angle
#define resolution_hz 1000
#define ratio_hz 6
#define span_hz 0.001 //(s)
//#define P_hz 1
//#define I_hz 1
//#define D_hz 1
//elevation angle
#define resolution_ev 1000
#define ratio_ev 1
#define span_ev 0.001 //(s)
//#define P_ev 1
//#define I_ev 1
//#define D_ev 1

//elevation angle
extern double target_ev;
extern int ev_ok;
//horizontal angle
extern double target_hz;
extern int hz_ok;
//reset
//extern bool reset;	//execute reset?
//extern bool hz_neg;	//negative limit
//extern bool hz_origin;	//zero
//extern bool hz_pos;	//positive limit
//extern bool ev_origin;	//zero
//extern bool ev_vt;	//vertical

//horizontal angle
extern int16_t enc_hz;
extern double angle_hz;
//elevation angle
extern int16_t enc_ev;
extern double angle_ev;

//PID
extern double et_hz;
extern double et_ev;
extern double sigma_et_hz;
extern double sigma_et_ev;
extern double ut_hz;
extern double ut_ev;

extern double P_hz;
extern double I_hz;
extern double D_hz;

extern double P_ev;
extern double I_ev;
extern double D_ev;

void shooter_base();

#endif /* INC_SHOOTER_BASE_H_ */
