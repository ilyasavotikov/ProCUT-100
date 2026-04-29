#include "tech_process.h"

#define MAX_PULSE 680  //680 max //570 било 
#define MIN_PULSE 100

uint16_t OutCurrent;
uint16_t temprRAD;
extern uint16_t PULSE;
uint32_t puls_pwm = MIN_PULSE;


void FIB_SIB_init(void)
{
    PULSE=100;
	  HAL_TIMEx_PWMN_Start_IT(&htim1, TIM_CHANNEL_1);// - FIB ch1	
	
		for (uint32_t i = 0; i <= 2000; i++)
	  {		
	  }
		
		HAL_TIM_PWM_Start_IT (&htim1, TIM_CHANNEL_4);// - FIB ch2		
	  for (uint32_t i = 0; i <= 4000; i++) 
	  {		
	  }
		
}

void FIB_SIB_DEinit(void)
{

  HAL_TIM_PWM_Stop_IT (&htim1,TIM_CHANNEL_4);// - FIB ch2
	HAL_TIMEx_PWMN_Stop_IT(&htim1, TIM_CHANNEL_1);// - FIB ch1
}



 uint16_t Current_Stabiliti(uint16_t Set_cur_adc)
  {
	    PULSE = Set_cur_adc;			
  }
 





uint32_t tempr_filter=0;
uint32_t tempr_filter_MIN=0;
uint32_t tempr_filter_MIDLE=0;
uint32_t tempr_filter_MAX=0;
uint32_t tempr_filter_Back_weld=0;

uint32_t Rad_temp_1;
uint32_t Rad_temp_2;
uint32_t AC_shift=0;
void Tempr_FANspeed_flagHIDE(void)
{      

	   HAL_ADCEx_InjectedStart(&hadc3);//запустим аналого-цифровое преобразование
	   Rad_temp_1 = 1; //ADC3->JDR1;  // дачк дуги 
	   temprRAD = ADC3->JDR2;  

	  
	 if (HAL_GPIO_ReadPin(Weld_1_GPIO_Port, Weld_1_Pin)==0)
		{
			TIM13->CCR1 = MAX_speed_FAN; 
		}
	else
		{
			//...Проверка температуры. Если температура соответсвуте минимальной в течении 10 000 проверок - устанавливаем скважность для минимальной температуры
					if (temprRAD < MIN_temperature)  // 0% speed
					{
						tempr_filter_MIN++;
						if(tempr_filter_MIN>10000)
							{
								TIM13->CCR1 = MIN_speed_FAN; 
								tempr_filter_MIN=0;
							}		
					}
				else
					{
						tempr_filter_MIN=0; //Хоть раз из 10 000 температура не соответсвует минимальной - счетчик сбрасывается
					}
						
			
				if ((temprRAD > MIN_temperature)&&(temprRAD < MIDLE_temperature)) // 50% speed
					{
						tempr_filter_MIDLE++;
						if(tempr_filter_MIDLE>10000)
							{
									tempr_filter_MIDLE=0;
									TIM13->CCR1 = MIDLE_speed_FAN; 
							}
					}
				else 
					{
						tempr_filter_MIDLE=0;
					}
				
			
				if (temprRAD > MIDLE_temperature) //100% speed
					{
						tempr_filter_MAX++;
						if(tempr_filter_MAX>10000)
						{
							tempr_filter_MAX=0;
							TIM13->CCR1 = MAX_speed_FAN; 
						}
					}
					else
					{
						tempr_filter_MAX=0;
					}
		}
		
				
			
		if (temprRAD > (MAX_temperature)) //HIDE Temperature
			{
				tempr_filter++;
				if (tempr_filter>100000)
				{
				TemprHIDE_lable_flag=1;
				tempr_filter=0;
        }					
			}
			else 
        {
				tempr_filter=0;
				}
		
		if (temprRAD < temperature_back_to_weld) //back to weld
			{
			tempr_filter_Back_weld++;
			if(tempr_filter_Back_weld>10000)
				{
					TemprHIDE_lable_flag=0;  
					tempr_filter_Back_weld=0;
				}
			}
}

	


 



			
			
			

			
			
			
			
			
			
			
   uint16_t position_2T=1;
   uint16_t TIG_DC_Weld_flag=0;
   extern uint16_t weld_procces_lable_flag;			
   int delta_curent_dc;
	 uint16_t time_one_amper_dc;	
			
	 uint16_t	dinamic_curent_rise; 
	 uint16_t	dinamic_curent_fall;
			
	 uint16_t pre_flow_dc;
   uint16_t start_cur_dc;			
	 uint16_t rise_time_dc;
	 uint16_t main_cur_dc; 
	 uint16_t fall_time_dc;	
	 uint16_t finish_cur_dc;	
	 uint16_t post_flow_dc; 
	 uint16_t pulse_balanse_dc;
   uint16_t pulse_freq_dc;
   uint16_t low_cur_dc;

   uint16_t main_Arc_CUT;	
    
   uint32_t time_dinam;
   uint32_t time_non_cur=0;
	 uint16_t non_cur_reset;
	 uint16_t dinamic_curent_pulse;

   uint32_t Pilot_arc;
	 uint32_t Pilot_arc_filter;

 void CUT_2T_procces(void)    // 2T CUTTING
  {		
		  pre_flow_dc=8;
			start_cur_dc=25;			
			rise_time_dc=1;
			main_cur_dc=cut[1]; 
				
			Tempr_FANspeed_flagHIDE();
			
			if ((HAL_GPIO_ReadPin(Weld_1_GPIO_Port, Weld_1_Pin)==0)) // нажата кнопка
			 {
				  TIG_DC_Weld_flag=1;
					position_2T=1;
					time_dinam = HAL_GetTick();
			 }
					 
		 if(HAL_GPIO_ReadPin(Air_Press_GPIO_Port, Air_Press_Pin)==1) // датчик давления 
			 {
				LOW_presure_lable_flag=1;
				position_2T=6;
			 }

			 
			 
	 while (TIG_DC_Weld_flag==1)	
	  {
				 
		 if(HAL_GPIO_ReadPin(Air_Press_GPIO_Port, Air_Press_Pin)==1) // датчик давления 
			 {
				LOW_presure_lable_flag=1;
				position_2T=6;
			 }
			
		 Tempr_FANspeed_flagHIDE();	
		 if (TemprHIDE_lable_flag==1)  // температура 
			 {
				 position_2T=6;
			 }
				 
switch (position_2T)
	{		 
		 case 1: // Pre Flow
			   position_2T=2;
		     time_dinam = HAL_GetTick();
	   break;
						
		 case 2: // ArcStart
			 if ((HAL_GetTick()-time_dinam)<(pre_flow_dc*100))
			{
				HAL_GPIO_WritePin(EPK_GPIO_Port,EPK_Pin, GPIO_PIN_RESET); //EPK off
			  HAL_GPIO_WritePin(EPK_2_GPIO_Port,EPK_2_Pin, GPIO_PIN_SET); //EPK_2 on
			}
			else
       {
		    HAL_GPIO_WritePin(EPK_2_GPIO_Port,EPK_2_Pin, GPIO_PIN_RESET); //EPK_2 off
		    HAL_GPIO_WritePin(EPK_GPIO_Port,EPK_Pin, GPIO_PIN_SET); //EPK on
		    HAL_GPIO_WritePin(Pilot_ARC_GPIO_Port,Pilot_ARC_Pin, GPIO_PIN_SET); //PilotArc on 
			 
			  FIB_SIB_init();
			  Current_Stabiliti(curentTarirovka [start_cur_dc]); 
			  position_2T=3; //  PilotTime 
			  time_dinam = HAL_GetTick();
			 }
		break;
					
		case 3:// PilotTime
		
        Current_Stabiliti(curentTarirovka [start_cur_dc]);  
	    	Pilot_arc_filter=0;   

		     while ((position_2T!=7)&&(position_2T!=6)&&(Pilot_arc_filter<80000))   
					 {
							HAL_ADCEx_InjectedStart(&hadc3);//запустим аналого-цифровое преобразование
							Pilot_arc = ADC3->JDR1;  // дачк дуги 
							 
							if(Pilot_arc>3700)
								{
									Pilot_arc_filter++; //...Увеличиваем итерацию только когда значение дуги буольше 3700
								}
								
								Current_Stabiliti(curentTarirovka [start_cur_dc]);
								 
							if(HAL_GPIO_ReadPin(Air_Press_GPIO_Port, Air_Press_Pin)==1) // виход по датчик давления 
									 {
										 LOW_presure_lable_flag=1;
										 position_2T=6;
									 } 
											
									 if (HAL_GPIO_ReadPin(Weld_1_GPIO_Port, Weld_1_Pin)==1)  // вихід по кнопкі 
									{
										 position_2T=6;
									} 
									
								if((HAL_GetTick()-time_dinam)>3000) //виход по часу 
								  {
									  position_2T=7;   // go to non curent 
								  }	
									
               if(Pilot_arc_filter>=80000)// виход по нваявності дуги 
								  {
									  position_2T=4;
								  }																				
					  }
						 
				HAL_GPIO_WritePin(Pilot_ARC_GPIO_Port,Pilot_ARC_Pin, GPIO_PIN_RESET); //PilotArc off
				time_dinam = HAL_GetTick();
				dinamic_curent_rise = start_cur_dc;

	  break;
					
		case 4:// Nominal current 
			
		if (main_cur_dc>start_cur_dc)
					{
						delta_curent_dc = main_cur_dc - start_cur_dc;
					}
					
		if (main_cur_dc<start_cur_dc)
			{
				delta_curent_dc = start_cur_dc-main_cur_dc;
			}
			
		time_one_amper_dc = ((rise_time_dc*1000)/delta_curent_dc)/10; //...Время спада одного ампера 
		    	
		if ((HAL_GetTick()-time_dinam)>time_one_amper_dc) //...Если спад произошел на больше чем один ампер
			{
				time_dinam = HAL_GetTick();
					
				//...dinamic_curent_rise плавно увеличивается до значения main_cur_dc
				if (main_cur_dc>start_cur_dc)
					{
						dinamic_curent_rise++;
					}
					
				if (main_cur_dc<start_cur_dc)
					{
						dinamic_curent_rise--;
					}
					
				if (start_cur_dc==main_cur_dc)
					 {
						dinamic_curent_rise  = main_cur_dc;
					 }	
			}	
					
		if (dinamic_curent_rise >= main_cur_dc)
			{			 
				dinamic_curent_rise = main_cur_dc;

			 time_dinam = HAL_GetTick();
			}
	
		  Current_Stabiliti(curentTarirovka[dinamic_curent_rise]); 
					
			HAL_ADCEx_InjectedStart(&hadc3);//запустим аналого-цифровое преобразование
			Pilot_arc = ADC3->JDR1;  // дачк дуги 
			
		if(Pilot_arc<3100)	// non current              
			{   
				if (time_non_cur==0)
				{
					time_non_cur=HAL_GetTick();
				}
			}
			else
			{
				time_non_cur=0;
			}
			
		if (((HAL_GetTick()-time_non_cur)>2000)&&time_non_cur!=0)
			{
				 position_2T=7;   // go to non curent 
				 time_dinam = HAL_GetTick();
			}			
	
		if (HAL_GPIO_ReadPin(Weld_1_GPIO_Port, Weld_1_Pin)==1)
			{
				position_2T=6;
				time_dinam = HAL_GetTick();
			}
		break;
					
		case 5:// Fall Time
	  break;
					
	  case 6:// Post Flow 
						
		FIB_SIB_DEinit();
		TIG_DC_Weld_flag=0;
		position_2T=2;  // go to arc start  
		time_dinam = HAL_GetTick();
		time_dinam_post_flov = HAL_GetTick();
		EEprom_Write(cut);
		break;
						
		case 7:// none curent 
			
		FIB_SIB_DEinit();
		if (HAL_GPIO_ReadPin(Weld_1_GPIO_Port, Weld_1_Pin)==1)
			{			 
			 position_2T=6; // Post Flow 
			}
		break;	
						
				}
		}
}
		 






void CUT_4T_procces(void)    //  4T CUTTING
 {		
			pre_flow_dc=8;
			start_cur_dc=20;			
			rise_time_dc=1;
			main_cur_dc=cut[1]; 
	
			Tempr_FANspeed_flagHIDE();
			Button_2tackt (cut_but_4t);
			
		if ((cut_but_4t[0]==1)&&(HAL_GPIO_ReadPin(Air_Press_GPIO_Port, Air_Press_Pin)==0)) // нажата кнопка перший раз 
			 {
				  TIG_DC_Weld_flag=1;
					position_2T=1;
					time_dinam = HAL_GetTick();
			 }
					 
		if(HAL_GPIO_ReadPin(Air_Press_GPIO_Port, Air_Press_Pin)==1) // датчик давления 
			 {
				LOW_presure_lable_flag=1;
				position_2T=6;
			 }
 
	while (TIG_DC_Weld_flag==1)	
{
				
		 Button_2tackt (cut_but_4t);
				 
		 if(HAL_GPIO_ReadPin(Air_Press_GPIO_Port, Air_Press_Pin)==1) // датчик давления 
			 {
				LOW_presure_lable_flag=1;
				position_2T=6;
			 }
	
		  Tempr_FANspeed_flagHIDE();	
			if (TemprHIDE_lable_flag==1)  // температура 
				{
				position_2T=6;
				}
				 
	switch (position_2T)
	{
					 
		 case 1: // Pre Flow
			   position_2T=2;
		     time_dinam = HAL_GetTick();
	   break;
						
		 case 2: // ArcStart
			 if ((HAL_GetTick()-time_dinam)<(pre_flow_dc*100))
			{
				HAL_GPIO_WritePin(EPK_GPIO_Port,EPK_Pin, GPIO_PIN_RESET); //EPK off
			  HAL_GPIO_WritePin(EPK_2_GPIO_Port,EPK_2_Pin, GPIO_PIN_SET); //EPK_2 on
			}
			else
       {
		    HAL_GPIO_WritePin(EPK_2_GPIO_Port,EPK_2_Pin, GPIO_PIN_RESET); //EPK_2 off
		    HAL_GPIO_WritePin(EPK_GPIO_Port,EPK_Pin, GPIO_PIN_SET); //EPK on
		    HAL_GPIO_WritePin(Pilot_ARC_GPIO_Port,Pilot_ARC_Pin, GPIO_PIN_SET); //PilotArc on 
			 
			  FIB_SIB_init();
			  Current_Stabiliti(curentTarirovka [start_cur_dc]); 
			  position_2T=3; //   PilotTime 
			  time_dinam = HAL_GetTick();
			 }
		 break;
					
		 case 3:// PilotTime
		
        Current_Stabiliti(curentTarirovka [start_cur_dc]);  
	    	Pilot_arc_filter=0;

		     while ((position_2T!=7)&&(position_2T!=6)&&(Pilot_arc_filter<80000)) 
					  {
							Button_2tackt (cut_but_4t);
							 
							HAL_ADCEx_InjectedStart(&hadc3);//запустим аналого-цифровое преобразование
							Pilot_arc = ADC3->JDR1;  // дачк дуги 
							 
							if(Pilot_arc>3700)
								{
									Pilot_arc_filter++;
								}
								
							Current_Stabiliti(curentTarirovka [start_cur_dc]);
								 
							if(HAL_GPIO_ReadPin(Air_Press_GPIO_Port, Air_Press_Pin)==1) // датчик давления 
								{
									 LOW_presure_lable_flag=1;
									 position_2T=6;
								} 
												
							if (cut_but_4t[0]==2) // кнопка нажата другий раз 
								{
								  position_2T=6;
								} 
									if((HAL_GetTick()-time_dinam)>3000) //виход по часу 
								  {
									  position_2T=7;   // go to non curent 
								  }	
									
               if(Pilot_arc_filter>=80000)// виход по нваявності дуги 
								  {
									  position_2T=4;
								  }					
					
					   }
						
						 
					HAL_GPIO_WritePin(Pilot_ARC_GPIO_Port,Pilot_ARC_Pin, GPIO_PIN_RESET); //PilotArc off
					time_dinam = HAL_GetTick();
					dinamic_curent_rise = start_cur_dc;

	  break;
					
		case 4:// Nominal current 
			
		if (main_cur_dc>start_cur_dc)
					{
						delta_curent_dc = main_cur_dc - start_cur_dc;
					}
					
		if (main_cur_dc<start_cur_dc)
			{
				delta_curent_dc = start_cur_dc-main_cur_dc;
			}
			
		time_one_amper_dc = ((rise_time_dc*1000)/delta_curent_dc)/10;
		    
					
		if ((HAL_GetTick()-time_dinam)>time_one_amper_dc) //Если успел упасть 1 ампер
			{
				time_dinam = HAL_GetTick();
					
				if (main_cur_dc>start_cur_dc) 
					{
						dinamic_curent_rise++;
					}
					
				if (main_cur_dc<start_cur_dc)
					{
						dinamic_curent_rise--;
					}
					
				if (start_cur_dc==main_cur_dc)
					 {
						dinamic_curent_rise  = main_cur_dc;
					 }	
			}	
					
		if (dinamic_curent_rise >= main_cur_dc)
			{			 
				dinamic_curent_rise = main_cur_dc;

			 time_dinam = HAL_GetTick();
			}
					
		Current_Stabiliti(curentTarirovka [dinamic_curent_rise]);
			
		 HAL_ADCEx_InjectedStart(&hadc3);//запустим аналого-цифровое преобразование
		 Pilot_arc = ADC3->JDR1;  // дачк дуги 
			
		if(Pilot_arc<3100)	// non current    			
			{   
				if (time_non_cur==0)
				{
					time_non_cur=HAL_GetTick();
				}
			}
			else
			{
				time_non_cur=0;
			}
			
		if (((HAL_GetTick()-time_non_cur)>2000)&&time_non_cur!=0)
			{
				 position_2T=7;   // go to non curent 
				 time_dinam = HAL_GetTick();
			}			
	
				
		 if (cut_but_4t[0]==2) // кнопка нажата другий раз 
			{
				position_2T=6;
				time_dinam = HAL_GetTick();
			}
		break;
					
		case 5:// Fall Time
	  break;
					
	  case 6:// Post Flow 
			
		FIB_SIB_DEinit();	 
		TIG_DC_Weld_flag=0;
		position_2T=2;  // go to arc start  
		time_dinam = HAL_GetTick();
		time_dinam_post_flov = HAL_GetTick();
	  EEprom_Write(cut);
		break;
						
		case 7:// none curent 
		
		FIB_SIB_DEinit();
		if (cut_but_4t[0]==2) // кнопка нажата другий раз 
			{			 
			 position_2T=6; // Post Flow 
			}
		break;	
						
				}
		}
}
		

uint32_t Button_2tackt (uint32_t * press_quanity)
{
	if ((HAL_GPIO_ReadPin (Weld_1_GPIO_Port, Weld_1_Pin)==0)&&(press_quanity[1] == 0))// Check state of button and repeat flag state
	{		
		press_quanity[0]++;		 		
		press_quanity[1] = 1;	
		return 1;
	}
	if (HAL_GPIO_ReadPin (Weld_1_GPIO_Port, Weld_1_Pin)==1)
	{		
		press_quanity[1] = 0;	
		return 0;
	}	
	if(press_quanity[0] >2)
	{
		press_quanity[0] = 1;
	}
}

void Torc_Error_determinate(void)
{
	
}

void Cut_Grid_determinate(void)
{
	
}
		 