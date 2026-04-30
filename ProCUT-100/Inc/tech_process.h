
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "i2c.h"
#include "tim.h"
#include "gpio.h"
#include "Other_func.h"

#include "lcd.h"
#include "Butt_hand.h"
#include "Lcd_func.h"

extern  uint16_t cut [CUT_PAR_QUANITY]; // TIG AC parameters 

extern uint16_t curentTarirovka [126];

#define temperature_back_to_weld 2800 

#define MAX_temperature 3350// last 3130
#define MIDLE_temperature 2700 
#define MIN_temperature 2200 // 30C


#define MAX_speed_FAN 1000
#define MIDLE_speed_FAN 500
#define MIN_speed_FAN 0


extern uint16_t OutCurrent;
extern  uint16_t TemprHIDE_lable_flag;
extern  uint16_t LOW_presure_lable_flag;
extern uint32_t cut_but_4t[2];
extern uint32_t time_dinam_post_flov;



void FIB_SIB_init(void);
void FIB_SIB_DEinit(void);
uint16_t Current_Stabiliti(uint16_t Set_cur_adc);
void Tempr_FANspeed_flagHIDE(void);

void Torc_Error_determinate(void);
void Cut_Grid_determinate(void);

uint32_t Button_2tackt (uint32_t * press_quanity);

void CUT_2T_procces(void);
void CUT_4T_procces(void);





