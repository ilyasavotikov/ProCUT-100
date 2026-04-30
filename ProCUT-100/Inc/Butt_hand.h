
#include "lcd.h"
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "tim.h"
#include "gpio.h"
#include "i2c.h"

#define CUT_PAR_QUANITY 3


#define EEPROM_ADDRESS 0x50

#define MEMORY_FLAG_ADDRESS 40000 // check for first start of EEPROM 
#define MEMORY_FLAG 96

extern uint16_t namber_par_weld;


void Butt_scan (uint16_t * cut_arr);  //Button handler 

void EEprom_Write(uint16_t * cut_arr);

void EEprom_Read(uint16_t * cut_arr);

void Fix_weld_value (void); 
void EEprom_write_Plant_Set(void); 
void Go_to_Plant_Set(void); 
