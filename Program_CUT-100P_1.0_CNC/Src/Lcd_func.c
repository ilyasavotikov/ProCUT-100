#include "Lcd_func.h"

uint16_t mode_diagram_reset=0;

uint16_t mode_screen_reset=0;
uint16_t namber_prog_reset_lcd=0;

uint16_t namber_par_weld_screen_reset=500;
uint16_t namber_unit_par_weld_screen_reset=500;

uint16_t mode_screen_reset_namber=500;
uint16_t mode_screen_reset_unit=500;

uint16_t mode_screen_value_reset=500;
uint16_t butt_mod_reset=500;
uint16_t value_par_reset=50000; 
uint16_t value_par_reset_2=50000; 
uint16_t value_par_reset_3=50000; 
uint16_t value_par_reset_4=50000; 
//lable 
uint32_t pl_reset=2;
uint32_t weld_butt_labl_reset=0;
uint32_t SAVE_butt_labl_reset=1;
uint32_t SAVE_butt_lable_time=0;
uint32_t INVol_labl_reset=1;
uint32_t TemperHIDE_labl_reset=1;
uint32_t low_press_labl_reset=1;
uint32_t Torch_labl_reset=1;
uint32_t Cut_grid_reset=1;
extern uint16_t language;

void Lcd_update (uint16_t * cut_arr)  // all update LCD
 {
	 Lcd_dinamic_sting();
   Lcd_static_sting();
   TemprHIDE_lable();
   Pressure_lable(); 
	 Torch_lable();	 
	 Cut_Grid_lable();
}
void Lcd_begin_Paton (void)
 {
	LCD_Init();
  LCD_SetRotation(1);	
	LCD_FillScreen (BLACK); 
	uint32_t T; 
	T = HAL_GetTick ();
	 
	 HAL_TIM_PWM_Start(&htim13, TIM_CHANNEL_1); // FAN init 
	 TIM13->CCR1=1000; // FAN 100%

		 
	while ( (HAL_GetTick () - T)< 700)
	{
		LCD_SetCursor (100,20);		
		LCD_SetTextSize (1);		
		LCD_Printf ("Paton"); //ПАТОН
		LCD_SetCursor (60,90);		 
		LCD_SetTextSize (1);
		LCD_Printf ("ProCut-100");// CUT-40P 

	}
	 HAL_Delay(1500);
	 TIM13->CCR1=0; // FAN 0%
	 
	LCD_FillScreen (BLACK);
 }

 void Lcd_static_line(void)
 {
	// Lcd_DrawFatRect(0,0,320,240,WHITE,3);//All rect
   LCD_DrawLine (0,166,320,166,WHITE);
	 LCD_DrawLine (0,165,320,165,WHITE);
	 LCD_DrawLine (0,164,320,164,WHITE);
	 LCD_DrawLine (0,163,320,163,WHITE);
	 
	 LCD_DrawLine (201,165,201,0,WHITE);
	 LCD_DrawLine (202,165,202,0,WHITE);
	 LCD_DrawLine (203,165,203,0,WHITE);
	 LCD_DrawLine (204,165,204,0,WHITE);
	 
 }
 
 
 void Lcd_DrawFatRect (uint32_t x,uint32_t y,uint32_t w, uint32_t h ,uint32_t color, uint32_t f )// //All rect
{
	for (uint32_t i = 0; i <=f; i++)
	{
		LCD_DrawRect (x,y,w,h,color);
		x++;
		y++;
		w = w - 2;
		h = h - 2;			
	}
	
}






void Lcd_static_sting()
{
	if (mode_screen_reset==0)
	{
		
		switch (language)
	{

		case 0: //UA 
			
	   LCD_SetCursor (45,20);
	   LCD_SetTextSize (0);
	   LCD_Printf ("Nompi");	
	
		break;
		
		case 1: //RU 

	   LCD_SetCursor (65,20);
	   LCD_SetTextSize (0);
		 LCD_Printf ("Okg");	

		break;
		
		case 2: //ENG
	   LCD_SetCursor (25,20);
	   LCD_SetTextSize (1);
	   LCD_Printf ("Current");	
	
		break;
		
	}
		mode_screen_reset=1;
	}
	
}	


//savotikov
void OutputThreeSymbols(first, second, third){
	
			char a[3],b[3],c[3];
	
			sprintf (a,"%d",first);
			sprintf (b,"%d",second);
			sprintf (c,"%d",third);
	
			if(value_par_reset!=first){
				LCD_FillRect(15,70,60,80,BLACK);	//value rect savotikov було LCD_FillRect (15,70,60,80,BLACK);
				LCD_DrawChar_BIG_1(9,70,*a,WHITE,RED,2); // delta 36 savotikov було LCD_DrawChar_BIG_1(9,70,*a,WHITE,RED,2);
				LCD_DrawChar_BIG_2(9+32,70,*a,WHITE,RED,2); //savotikov було LCD_DrawChar_BIG_2(9+32,70,*a,WHITE,RED,2);
				value_par_reset=first;
			}
			
			if(value_par_reset_2!=second){
				LCD_FillRect (75,70,60,80,BLACK);	//value rect savotikov було LCD_FillRect (75,70,60,80,BLACK); 
				LCD_DrawChar_BIG_1(67,70,*b,WHITE,RED,2); //savotikov було LCD_DrawChar_BIG_1(67,70,*b,WHITE,RED,2);
				LCD_DrawChar_BIG_2(67+32,70,*b,WHITE,RED,2); //savotikov було LCD_DrawChar_BIG_2(67+32,70,*b,WHITE,RED,2);
				value_par_reset_2=second;
			}
	
			if((value_par_reset_3!=third)){ //savotikov Було if((value_par_reset_3!=1)&&(cut[1] == 100)) 
				LCD_FillRect (135,70,60,80,BLACK);	//value rect savotikov було LCD_FillRect (135,70,42,56,BLACK);
				LCD_DrawChar_BIG_1(127,70,*c,WHITE,RED,2); //savotikov було  LCD_DrawChar_BIG_1(127,70,*c,WHITE,RED,2);
				LCD_DrawChar_BIG_2(127+32,70,*c,WHITE,RED,2); //savotikov було LCD_DrawChar_BIG_2(127+32,70,*c,WHITE,RED,2);
				value_par_reset_3 = third; //savotikov було value_par_reset_3=1; 
				value_par_reset_4=0;
			}
}





void OutputTwoSymbols(second, third){
	
		char a[3],b[3];
	
		sprintf (a,"%d",second);
		sprintf (b,"%d",third);
	
		 if(value_par_reset!=second){
				LCD_FillRect(15,70,60,80,BLACK);	//draw sumbol 1
				LCD_DrawChar_BIG_1(9,70,*a,WHITE,RED,2); 
				LCD_DrawChar_BIG_2(9+32,70,*a,WHITE,RED,2); 
				value_par_reset=second;
			}
			
			if(value_par_reset_2!=third){
				LCD_FillRect (75,70,60,80,BLACK); //draw sumbol 2
				LCD_DrawChar_BIG_1(67,70,*b,WHITE,RED,2); 
				LCD_DrawChar_BIG_2(67+32,70,*b,WHITE,RED,2); 
				value_par_reset_2=third;
			}
	
			if((value_par_reset_3!=SYMBOL_A)){ 	//draw sumbol 'a'
				LCD_FillRect (135,70,60,80,BLACK);	
				LCD_DrawChar_BIG_A1(135,93,'A',WHITE,RED,3); 
				LCD_DrawChar_BIG_A2(135+33,93,'A',WHITE,RED,3); 
				value_par_reset_3 = SYMBOL_A; 
				value_par_reset_4=0;
			}
			
			
}
//...savotikov

void OutputCurrentSymbols(OutputThreeDigits, first, second, third){
	if(OutputThreeDigits){
			OutputThreeSymbols(first, second, third);
		}else{
			OutputTwoSymbols(second, third);
		}
}



void Lcd_dinamic_sting(void) //screen 2T_4T, curent
{
	
  uint8_t first;	
	uint8_t second;
	uint8_t third;
	
	char sign;
	char sign_2;

	sign = '2';	
	sign_2='T';
	 
	//savotikov
	//було
   /*first = (cut[1])/10;
	 second = (cut[1])%10;
	 third = 0;*/
	first = (cut[1])/100;
	second= ((cut[1])%100)/10;
	third = ((cut[1])%100)%10;
	//...savotikov
	
	uint8_t OutputThreeDigits = (first == 0) ? 0 : 1;
	OutputCurrentSymbols(OutputThreeDigits, first, second, third);
		
	/* savotikov закоментував
 if((cut[1]==99)||(cut[1]==98))
	{
		if(value_par_reset_4!=1)
		{
		  LCD_FillRect (135,70,60,80,BLACK);	//value rect
		  LCD_DrawChar_BIG_A1(135,93,'A',WHITE,RED,3); // delta 34
		  LCD_DrawChar_BIG_A2(135+33,93,'A',WHITE,RED,3);
		  value_par_reset_3=0;
			value_par_reset_4=1;
		}

	}*/
	
//	if(value_par_reset!=cut[1]/10)
//	{
//	 LCD_FillRect (18,93,42,55,BLACK);	//value rect
//   LCD_DrawChar_BIG_A1(10,93,*a,WHITE,RED,3); // delta 36
//	 LCD_DrawChar_BIG_A2(10+32,93,*a,WHITE,RED,3);
//		
//	 value_par_reset=cut[1]/10;
//	}
//	
//	if(value_par_reset_2!=cut[1]%10)
//	{
//	 LCD_FillRect (58,93,42,55,BLACK);	//value rect
//	 LCD_DrawChar_BIG_A1(50,93,*b,WHITE,RED,3);
//	 LCD_DrawChar_BIG_A2(50+32,93,*b,WHITE,RED,3);
//	 value_par_reset_2=cut[1]%10;
//	}
//	
//	if((value_par_reset_3!=1)&&(cut[1]==100))
//	{
//	 LCD_DrawChar_BIG_A1(90,93,*b,WHITE,RED,3);
//	 LCD_DrawChar_BIG_A2(90+32,93,*b,WHITE,RED,3);
//	 value_par_reset_3=1;
//	}
//	
//	if((cut[1]==99)||(cut[1]==98))
//	{
//		LCD_FillRect (98,93,42,55,BLACK);	//value rect
//		value_par_reset_3=0;
//	}
//	
	if(cut[0]!=butt_mod_reset)
	{
		switch (language)
	{

		case 0: //UA 
			
    if(cut[0]==1)
		 {
			  LCD_SetCursor (15,180);
	      LCD_SetTextSize (0);
		    LCD_Printf ("Mbc. gjklge 2O");	
		 }
		 if(cut[0]==2)
		 {
			  LCD_SetCursor (15,180);
	      LCD_SetTextSize (0);
		    LCD_Printf ("Mbc. gjklge 4O");	
		 }
		 
		 if(cut[0]==3)
		 {
			  LCD_SetCursor (15,180);
	      LCD_SetTextSize (0);
		    LCD_Printf ("Mbc.mk^koe TLG");	
		 }
		 
		 
		break;
		
		case 1: //RU 
			
    if(cut[0]==1)
		 {
			  LCD_SetCursor (15,180);
	      LCD_SetTextSize (0);
		    LCD_Printf ("Mbc. gjklge 2O");	
		 }
		 if(cut[0]==2)
		 {
			  LCD_SetCursor (15,180);
	      LCD_SetTextSize (0);
		    LCD_Printf ("Mbc. gjklge 4O");	
		 }
		 	 if(cut[0]==3)
		 {
			  LCD_SetCursor (15,180);
	      LCD_SetTextSize (0);
		    LCD_Printf ("Mbc.mk^kox TLP");	
		 }
		 
		break;
		
		case 2: //ENG
	   if(cut[0]==1)
		 {
			  LCD_SetCursor (15,180);
	      LCD_SetTextSize (1);
		    LCD_Printf ("Button mode 2T");	
		 }
		 if(cut[0]==2)
		 {
			  LCD_SetCursor (15,180);
	      LCD_SetTextSize (1);
		    LCD_Printf ("Button mode 4T");	
		 }
		 if(cut[0]==3) 
		 {
			  LCD_SetCursor (15,180);
	      LCD_SetTextSize (1);
		    LCD_Printf ( "Work mode  CNC");	
		 }
		break;
		
	}
   butt_mod_reset=cut[0];
}
}


void Torch_lable(void)
{
	uint32_t color;
	char sign;
	char sign2;
	char sign3;
	char sign4;
	char sign5;
	sign = 'T';
	sign2 = 'o';
	sign3 = 'r';
	sign4 = 'c';
	sign5 = 'h';
	
	if(Torch_labl_reset!=Torch_Error_lable_flag)
	{
			if (Torch_Error_lable_flag == 0)
			{
				color = GREEN;
				Torch_labl_reset=0;
			}
			else
			{
				color = RED;
				Torch_labl_reset=1;
			}
			LCD_FillRoundRect (220,45,88,32,3,color);
			
			LCD_DrawChar (220+5,45+6,sign,BLACK,color,4);
			LCD_DrawChar (220+20,45+6,sign2,BLACK,color,4);
      LCD_DrawChar (220+35,45+6,sign3,BLACK,color,4);
      LCD_DrawChar (220+51,45+6,sign4,BLACK,color,4);
			LCD_DrawChar (220+67,45+6,sign5,BLACK,color,4);
	}
}

void Cut_Grid_lable(void)
{
	uint32_t color;
	char sign;
	char sign2;
	char sign3;
	char sign4;

	sign = 'G';
	sign2 = 'R';
	sign3 = 'I';
	sign4 = 'D';
	
	char sign_g;
	char sign_g2;
	char sign_g3;
	char sign_g4;

	sign_g =  'C';
	sign_g2 = 'U';
	sign_g3 = 'T';



	if(Cut_grid_reset!=Cut_Grid_lable_flag)
	{
			if (Cut_Grid_lable_flag == 0)
			{
				color = BLUE;
				Cut_grid_reset=0;
				
			LCD_FillRoundRect (220,5,88,32,3,color);
			LCD_DrawChar (220+13,5+6,sign,BLACK,color,4);
			LCD_DrawChar (220+28,5+6,sign2,BLACK,color,4);
      LCD_DrawChar (220+43,5+6,sign3,BLACK,color,4);
      LCD_DrawChar (220+59,5+6,sign4,BLACK,color,4);
			}
			else
			{
				color = GREEN;
				Cut_grid_reset=1;
				
			LCD_FillRoundRect (220,5,88,32,3,color);
			LCD_DrawChar (220+20,5+6,sign_g,BLACK,color,4);
			LCD_DrawChar (220+35,5+6,sign_g2,BLACK,color,4);
      LCD_DrawChar (220+52,5+6,sign_g3,BLACK,color,4);
			
			}
			

	}
}

void Pressure_lable(void)
{
	uint32_t color;
	char sign;
	char sign2;
	char sign3;
	char sign4;
	char sign5;
	sign = 'p';
	sign2 = ',';
	sign3 = 'b';
	sign4 = 'a';
	sign5 = 'r';
	
	if(low_press_labl_reset!=LOW_presure_lable_flag)
	{
			if (LOW_presure_lable_flag == 0)
			{
				color = GREEN;
				low_press_labl_reset=0;
			}
			else
			{
				color = RED;
				low_press_labl_reset=1;
			}
			LCD_FillRoundRect (220,85,88,32,3,color);
			
			LCD_DrawChar (220+18,85+4,sign2,BLACK,color,4);
			LCD_DrawChar (220+8,85+1,sign,BLACK,color,4);
      LCD_DrawChar (220+33,85+6,sign3,BLACK,color,4);
      LCD_DrawChar (220+49,85+6,sign4,BLACK,color,4);
			LCD_DrawChar (220+65,85+6,sign5,BLACK,color,4);
	}
}


void TemprHIDE_lable(void)
{
	char sign;
	char sign_2;
	uint32_t color;
	uint32_t status_color;
	sign = 'T';	
	sign_2='C';
	if(TemperHIDE_labl_reset!=TemprHIDE_lable_flag)
	{
			if (TemprHIDE_lable_flag == 0)
			{
				color = GREEN;
				status_color = GREEN;
				TemperHIDE_labl_reset=0;
			}
			if (TemprHIDE_lable_flag == 1)
			{
				color = RED;
				status_color = RED;
				TemperHIDE_labl_reset=1;
			}
			LCD_FillRoundRect (220,125,88,33,3,color);
			LCD_DrawCircle (220+46,125+7,2,BLACK);
			LCD_DrawChar (220+22,125+6,sign,BLACK,status_color,4);
			LCD_DrawChar (220+49,125+6,sign_2,BLACK,status_color,4);
					
  }
}



uint16_t leg_res_lcd=1;
uint16_t leg_res_buttonRight=1;
uint16_t leg_res_buttonLeft=1;


void Switch_language(void)
{
	 uint8_t flag_leng[1] = {0};
	 HAL_I2C_Mem_Read (&hi2c1,(uint16_t)EEPROM_ADDRESS<<1,LENGUAGE_ADDRESS,10,flag_leng,1,100);
	 
	 if(flag_leng[0]>10)
	 {
		 flag_leng[0]=0;
	 }
	 language = flag_leng[0];
			
	while (HAL_GPIO_ReadPin(Test_gas_GPIO_Port, Test_gas_Pin)==0)
		{
			if ((HAL_GPIO_ReadPin(Up_GPIO_Port, Up_Pin)==0)&&(leg_res_buttonRight==1))
			  {
					leg_res_lcd=1;
					leg_res_buttonRight=0;
			  	language++;
				  if (language==3)
				    {
				    	language=0;
			     	}			
		    }
			if ((HAL_GPIO_ReadPin(Down_GPIO_Port, Down_Pin)==0)&&(leg_res_buttonLeft==1))
				 {
				  leg_res_lcd=1;
				  leg_res_buttonLeft=0;
					language--;
					if (language>10)
						{
							language=2;
						}
          }
			if (HAL_GPIO_ReadPin(Up_GPIO_Port, Up_Pin)==1)
				{
					leg_res_buttonRight=1;
				}
				
			if (HAL_GPIO_ReadPin(Down_GPIO_Port, Down_Pin)==1)
				{
			    leg_res_buttonLeft=1;
				}
			
			switch(language)
				{
					case 0:
						
				if (leg_res_lcd==1)
					{
						LCD_FillScreen (BLACK);		
						LCD_SetCursor (120,100);		
						LCD_SetTextSize (0);
						LCD_Printf ("ik_]"); //мова 
						LCD_SetCursor (60,145);
						LCD_Printf ("Pgm]~jnyg]");	// Українська					
						leg_res_lcd=0;						
					}		
					break;
					
					case 1:
				if (leg_res_lcd==1)
					{
						LCD_FillScreen (BLACK);		
						LCD_SetCursor (120,100);		
						LCD_SetTextSize (0);
						LCD_Printf ("|dxg"); // язык 
						LCD_SetCursor (85,145);
						LCD_Printf ("Mpnngef"); //Русский 						
						leg_res_lcd=0;					
					}		
					break;
					
					case 2:
				if (leg_res_lcd==1)
					{
						LCD_FillScreen (BLACK);		
						LCD_SetCursor (80,100);		
						LCD_SetTextSize (1);
						LCD_Printf ("language");
						LCD_SetCursor (90,145);	
						LCD_Printf ("English");
						leg_res_lcd=0;						
					}		
					break;
					
				}
	 }
	flag_leng[0]=language;    
  HAL_I2C_Mem_Write (&hi2c1,(uint16_t)EEPROM_ADDRESS<<1,LENGUAGE_ADDRESS,10,flag_leng,1,100);
	LCD_FillScreen (BLACK);	
}









