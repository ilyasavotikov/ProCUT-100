#include "Butt_hand.h"




uint16_t speed_par_set;
uint16_t speed_par_set_down;

uint16_t mode_reset=0;    
uint16_t grid_reset=0; 
uint16_t prog_nam_reset=0; 
uint16_t right_butt_reset=0;
uint16_t left_butt_reset=0;
uint16_t up_butt_reset=0;
uint16_t down_butt_reset=0;
uint16_t enter_butt_reset=0;
uint16_t prog_nam_reset_read=0;

extern  uint16_t cut [CUT_PAR_QUANITY]; // CUT parameters 
extern uint16_t Cut_Grid_lable_flag; 
uint16_t cut_MAX [CUT_PAR_QUANITY] = {3,100,2};    // CUT_MAX parameters //savotikov було "uint16_t cut_MAX [CUT_PAR_QUANITY] = {3,125,2};"
uint16_t cut_MIN [CUT_PAR_QUANITY] = {1,20,1};       // CUT_MIN parameters 
uint16_t PlantSet_cut [CUT_PAR_QUANITY] = {1,50,1}; // CUT parameters PlantSet
uint16_t address_prog_CUT[3]={0, 400, 800}; 
uint16_t address_actual_CUT=0;

uint16_t test_gas_reset=0;



void Butt_scan (uint16_t * cut_arr) //+
{
	

	
	if ((HAL_GPIO_ReadPin(Bott_mod_GPIO_Port, Bott_mod_Pin)==0) && (mode_reset==0)) // 2T/4T Handler +
	{
		
		cut_arr[0]=cut_arr[0]++;
		
		if(cut_arr[0]==4)
		{
			cut_arr[0]=1;
		}
	
   
  
		mode_reset=1;

	}
	
	if (HAL_GPIO_ReadPin(Bott_mod_GPIO_Port, Bott_mod_Pin)==1) // reset
	{
	 mode_reset=0;
	}
	
	
	
	
		if ((HAL_GPIO_ReadPin(Bott_grid_GPIO_Port, Bott_grid_Pin)==0) && (grid_reset==0)) // CUT_GRID
	{
		
		Cut_Grid_lable_flag++;
		
		if(Cut_Grid_lable_flag==2)
		{
			Cut_Grid_lable_flag=0;
		}
	
   
  
		grid_reset=1;

	}
	
	if (HAL_GPIO_ReadPin(Bott_grid_GPIO_Port, Bott_grid_Pin)==1) // reset
	{
	 grid_reset=0;
	}
	
	
	
	
	
  if ((HAL_GPIO_ReadPin(Test_gas_GPIO_Port, Test_gas_Pin)==0)) // Test_gas button +
	  { 
       HAL_GPIO_WritePin(EPK_GPIO_Port,EPK_Pin, GPIO_PIN_SET);
			 test_gas_reset=1;
    }
		else
		{
		   if(test_gas_reset==1)
			 {
				 HAL_GPIO_WritePin(EPK_GPIO_Port,EPK_Pin, GPIO_PIN_RESET);
				 test_gas_reset=0;
				 
			 }
			 
		}
	 

	 

	
if((HAL_GPIO_ReadPin(Up_GPIO_Port, Up_Pin)==0) && (up_butt_reset==0)) // Up button handler //
		{
			cut_arr[1]++;
			up_butt_reset=1;
		}
	
		if (HAL_GPIO_ReadPin(Up_GPIO_Port, Up_Pin)==1) // reset
	  {
		 up_butt_reset=0;
		}
		
	
			
if((HAL_GPIO_ReadPin(Up_GPIO_Port, Up_Pin)==0)) //Up button handler +++ 
    {
		  HAL_TIM_Base_Start(&htim4);
      HAL_TIM_Base_Start_IT(&htim4);
			
		  if (speed_par_set==1)
			  {
				 TIM4->PSC=300;
			   cut_arr[1]++;
			   speed_par_set=0;
			  }
		 }
		else                                         // reset
		 {
			 HAL_TIM_Base_Stop(&htim4);
			 TIM4->CNT=0;
		   TIM4->PSC=4500;
		 }
		
		if ((HAL_GPIO_ReadPin(Down_GPIO_Port, Down_Pin)==0) && (down_butt_reset==0))      // Down button handler 
		{
			cut_arr[1]--;
			down_butt_reset=1;
		}
			
		if (HAL_GPIO_ReadPin(Down_GPIO_Port, Down_Pin)==1)                                  // reset
    {
			down_butt_reset=0;
		}			
			        
		
		if ((HAL_GPIO_ReadPin(Down_GPIO_Port, Down_Pin)==0))           //   Down button handler +++
		{
			HAL_TIM_Base_Start(&htim6);
      HAL_TIM_Base_Start_IT(&htim6);
		
		  if (speed_par_set_down==1)
		  	{
		 	  	TIM6->PSC=300;
			    cut_arr[1]--;
			  	speed_par_set_down=0;
			  } 
		 }			
		else                                                            // reset
		{
		 HAL_TIM_Base_Stop(&htim6);
		 TIM6->CNT=0;
		 TIM6->PSC=4500;
		}
		  		
	}
// EEprom // EEprom// EEprom// EEprom// EEprom// EEprom// EEprom// EEprom// EEprom// EEprom
 
 void EEprom_Read(uint16_t * cut_arr)  // EEprom READ 
 {
		 while (HAL_I2C_Mem_Read (&hi2c1,(uint16_t)EEPROM_ADDRESS<<1,address_actual_CUT,10,(uint8_t *)cut,sizeof(uint16_t)*CUT_PAR_QUANITY,100) != HAL_OK) {}		 
 }


void EEprom_Write(uint16_t * cut_arr)     //EEprom WRITE 
{
	while (HAL_I2C_Mem_Write (&hi2c1,(uint16_t)EEPROM_ADDRESS<<1,address_actual_CUT,10,(uint8_t *)cut,sizeof(uint16_t)*CUT_PAR_QUANITY,100) != HAL_OK) {}	  
}

void Fix_weld_value (void) //MIN/MAX weld_parametr 
{
	for (uint16_t i=0; i<=(CUT_PAR_QUANITY-1);i++)   // CUT MIN/MAX
	{
		if (cut[i]>cut_MAX[i]) // MAX
		{
			cut[i]=cut_MAX[i];
		}
		
		if (cut[i]<cut_MIN[i]) // MIX
		{
			cut[i]=cut_MIN[i];
		}
	}
	
}




void EEprom_write_Plant_Set(void)
{
	uint8_t flag[1] = {0};
	HAL_I2C_Mem_Read (&hi2c1,(uint16_t)EEPROM_ADDRESS<<1,MEMORY_FLAG_ADDRESS,10,flag,1,100);
	if (flag[0] != 96)
	 {
		 flag[0]= MEMORY_FLAG;
		 HAL_I2C_Mem_Write (&hi2c1,(uint16_t)EEPROM_ADDRESS<<1,MEMORY_FLAG_ADDRESS,10,flag,1,100);
		 HAL_Delay(100);
		 for (uint16_t i=0; i<=(9);i++)
				{
				 address_actual_CUT = address_prog_CUT[(i)]; 
				 while (HAL_I2C_Mem_Write (&hi2c1,(uint16_t)EEPROM_ADDRESS<<1,address_actual_CUT,10,(uint8_t *)PlantSet_cut,sizeof(uint16_t)*CUT_PAR_QUANITY,100) != HAL_OK) {}
				}
				
			LCD_SetCursor (50,140);		
			LCD_SetTextSize (1);
			LCD_Printf ("Data load");			
			HAL_Delay(2000);
			LCD_FillScreen (BLACK);
	}
			 
}	
	
void Go_to_Plant_Set(void)
{
	if (HAL_GPIO_ReadPin(Test_gas_GPIO_Port, Test_gas_Pin)==0)
	  {
			    for (uint16_t i=0; i<=(9);i++)
						{
						 address_actual_CUT = address_prog_CUT[(i)]; 
				
						
						 while (HAL_I2C_Mem_Write (&hi2c1,(uint16_t)EEPROM_ADDRESS<<1,address_actual_CUT,10,(uint8_t *)PlantSet_cut,sizeof(uint16_t)*CUT_PAR_QUANITY,100) != HAL_OK) {}
					
						}
					LCD_SetCursor (55,140);		
					LCD_SetTextSize (1);
					LCD_Printf ("Reset done");			
					HAL_Delay(3000);
					LCD_FillScreen (BLACK);
			}
}	



