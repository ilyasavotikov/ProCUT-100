#include "lcd.h"
#include "stm32f4xx_hal.h"
#include "Butt_hand.h"

#define LENGUAGE_ADDRESS 44000
#define SYMBOL_A 65535

extern  uint16_t cut [CUT_PAR_QUANITY]; // TIG AC parameters 

	// LCD lable flag 
 extern  uint16_t TemprHIDE_lable_flag;
 extern  uint16_t LOW_presure_lable_flag;
 extern uint16_t Torch_Error_lable_flag;
 extern uint16_t Cut_Grid_lable_flag;

void Lcd_update (uint16_t * cut_arr);  // all update LCD

void Lcd_begin_Paton (void);
void Lcd_static_line(void);
void Lcd_DrawFatRect(uint32_t x,uint32_t y,uint32_t w, uint32_t h ,uint32_t color, uint32_t f );// //All rect
void Lcd_static_sting(void);   
void Lcd_namber_program(void);
void Lcd_dinamic_sting(void);
// Lable_LCD
void Pressure_lable(void); 
void TemprHIDE_lable(void);
void Torch_lable(void);
void Cut_Grid_lable(void);
	
void Switch_language(void);


