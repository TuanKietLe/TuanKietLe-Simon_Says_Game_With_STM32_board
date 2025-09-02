/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>


#define NOTE_C4  262
#define NOTE_D4  294
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_REST 0

/* Simon Says Game Tones */
#define SIMON_G3 196  // Green button - G3
#define SIMON_C4 262  // Red button - C4
#define SIMON_E4 330  // Yellow button - E4
#define SIMON_G4 392  // Blue button - G4


void DelayMicroseconds(unsigned int us);
void PlayHz(uint32_t frequency, uint32_t duration_ms);

//First row
void Init_LED0(void);
void Init_PushButton_5(void);
//Second row
void Init_LED1(void);
void Init_PushButton_4(void);

//Third row
void Init_LED2(void);
void Init_PushButton_3(void);

//Fourth row
void Init_LED3(void);
void Init_PushButton_2(void);

//Sound buzzer
void Init_buzzer(void);

//making sound 

//Simon Says LED
void Init_Red_LED(void);
void Init_Yellow_LED(void);
void Init_Blue_LED(void);
void Init_Green_LED(void);
void Turn_On_Red(void);
void Turn_On_Blue(void);
void Turn_On_Yellow(void);
void Turn_On_Green(void);
void Turn_Off_Red(void);
void Turn_Off_Blue(void);
void Turn_Off_Yellow(void);
void Turn_Off_Green(void);

//Simon Says Button
void Init_Red_Button(void);
void Init_Yellow_Button(void);
void Init_Blue_Button(void);
void Init_Green_Button(void);

void Write_String_LCD(char*);
void Write_Char_LCD(uint8_t);
void Write_Instr_LCD(uint8_t);
void LCD_nibble_write(uint8_t, uint8_t);
void Write_SR_LCD(uint8_t);
void Delay(unsigned int);
void LCD_Init(void);
//Game setting
uint8_t take_user_input(void);
void SystemClock_Config(void);
void Delay(unsigned int);	
void SystemClock_Config(void);
void Increase_Diff(uint8_t *diff);
void Decrease_Diff(uint8_t *diff);
const uint16_t simon_notes[] = {
    SIMON_G3, SIMON_C4, SIMON_E4, SIMON_G4,  // Ascending
    SIMON_E4, SIMON_C4,                      // Descending
    SIMON_G3, SIMON_C4, SIMON_E4, SIMON_G4,  // Repeat ascending
    SIMON_G4, SIMON_G4, NOTE_REST,           // Double high note and pause
    SIMON_E4, SIMON_C4, SIMON_G3, NOTE_REST  // Descending finish
};
const uint8_t delay1 = 50;
const uint8_t delay2 = 100;
const uint16_t simon_durations[] = {
    delay1, delay1, delay1, delay2,  // Ascending
    delay1, delay1,          // Descending
    delay1, delay1, delay1, delay2,  // Repeat ascending
    delay1, delay1, delay2,      // Double high note and pause
    delay1, delay1, delay2, delay2   // Descending finish
};

/* Play Simon Says Theme Song */
void PlaySimonTheme(void);
void PlaySimonThemeRev(void);

void UpdateLCD(char *line1, char *line2) {
    Write_Instr_LCD(0x01); /* Clear display */
    Delay(2);
    Write_String_LCD(line1);
    Write_Instr_LCD(0xc0); /* Move to line 2 */
    Write_String_LCD(line2);
}

/* Update to PlaySimonTone in paste-2.txt */

//Game function prototypes
//Global variable
void get_pattern(uint8_t*);
uint8_t start_game(uint8_t* arr);
void play_LED_sequence(void);
uint8_t compare_pattern(uint8_t *);
void play_pattern(uint8_t *);
uint8_t take_LED_input(void);
void game_over_sequence(uint8_t high_score);
void flash_leds_sequence(void);
void play_game_over_sound(void);

uint16_t MAXLEVEL = 32;
uint8_t game_diff = 0;
uint8_t level = 1;
uint8_t random_LED(void);
uint8_t CURRENT_LENGTH = 0;
int main(void)
{ 
	srand(time(NULL));
	
	
	//int i;
  	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  	HAL_Init();

  	/* Configure the system clock */
  	SystemClock_Config();
		LCD_Init();
		Init_Red_LED();
		Init_Blue_LED();
		Init_Green_LED();
		Init_Yellow_LED();
		Init_Red_Button();
		Init_Blue_Button();
		Init_Yellow_Button();
		Init_Green_Button();	
		Init_PushButton_5();	
		Init_LED0();	 
		Init_PushButton_4();		
		Init_LED1();	
		Init_PushButton_3();		
		Init_LED2();	
		Init_PushButton_2();		
		Init_LED3();	
		Init_buzzer();
		Delay(2000);
    char* line1;
		line1 ="Welcome to 3130"; 
    char* line2;
    line2 ="Spring 2025";
	
		LCD_Init(); 
    /*Write_Char_LCD('o');*/
    /*Write_Char_LCD(0x42);*/

    Write_String_LCD(line1);
    Write_Instr_LCD(0xc0); 
    /* move to line 2*/ 
    Write_String_LCD(line2);
		HAL_Delay(2000);
		UpdateLCD("Simon Says", "Get ready");
		PlaySimonTheme();
		uint8_t pattern[MAXLEVEL];
		for(uint8_t i = 0; i < MAXLEVEL; i++){
			pattern[i] = 0;
		}
		
		while(1){
			uint8_t button = take_user_input();
			if(button == 0b0){//start game if SW5 is pressed
				level = start_game(pattern);
				Write_Instr_LCD(0x01);
				HAL_Delay(100);
			}
			if(button == 0b1){//increase the difficulty if SW4 is pressed
				Increase_Diff(&game_diff);
				HAL_Delay(100);
			}
			if(button == 0b10){//decrease the difficulty if SW3 is pressed
				Decrease_Diff(&game_diff);
				HAL_Delay(100);
			}
			if(button == 0b11){//end the game show the highest score
				game_over_sequence(level - 1);
			}
			HAL_Delay(25);
			}
}
void Turn_On_Red(void){//turn on the red LED
	GPIOC->ODR |= (1<<10);
}
void Turn_On_Blue(void){//turn on the blue LED
	GPIOH->ODR |= (1<<0);
}
void Turn_On_Yellow(void){//turn on the yellow LED
	GPIOC->ODR |= (1<<11);
}
void Turn_On_Green(void){//turn on the green LED
	GPIOC->ODR |= (1<<2);
}
void Turn_Off_Red(void){//turn off the red LED
	GPIOC->ODR &= ~(1<<10);
}
void Turn_Off_Blue(void){//turn off the blue LED
	GPIOH->ODR &= ~(1<<0);
}
void Turn_Off_Yellow(void){//turn off the yellow LED 
	GPIOC->ODR &= ~(1<<11);
}
void Turn_Off_Green(void){//turn off the green LED
	GPIOC->ODR &= ~(1<<2);
}
uint8_t take_LED_input(void){//take LED input 
    while (1) {
        if ((GPIOC->IDR & (1 << 12))) {//If red button is pressed
            Turn_On_Red();//turn on the red LED
						PlayHz(SIMON_C4,50);//Play a note
            HAL_Delay(50);
            while ((GPIOC->IDR & (1 << 12)));//Wait for release
            Turn_Off_Red();//turn off the red LED
            return 0;
        }
        if ((GPIOD->IDR & (1 << 2))) {//If yellow button is pressed
            Turn_On_Yellow();//turn on the yellow LEDs
						PlayHz(SIMON_E4,50);//Play a note
            HAL_Delay(50);
            while ((GPIOD->IDR & (1 << 2)));//Wait for release
            Turn_Off_Yellow();//turn off the yellow LED
            return 1;
        }
        if ((GPIOH->IDR & (1 << 1))) {//If blue button is pressed
            Turn_On_Blue();//turn on the blue LED
						PlayHz(SIMON_G4,50);//Play a note
            HAL_Delay(50);
            while ((GPIOH->IDR & (1 << 1)));//Wait for release
            Turn_Off_Blue();//turn off the blue LED
            return 2;
        }
        if ((GPIOC->IDR & (1 << 3))) {//If green button is pressed
            Turn_On_Green();//turn on the green LED
						PlayHz(SIMON_G3,50);//Play a note
            HAL_Delay(50);
            while ((GPIOC->IDR & (1 << 3)));//Wait for release
            Turn_Off_Green();//turn off the green LED
            return 3;
        }
    }
	}
void play_LED_sequence(void){
	for(uint8_t i = 0; i < 3; i++){
		Turn_On_Red();//turn on the red LED
		Turn_On_Yellow();//turn on the yellow LED
		Turn_On_Green();//turn on the green LED
		Turn_On_Blue();//turn on the blue LED
		
		HAL_Delay(1000);//Wait for 1 second
		
		Turn_Off_Red();//turn off the red LED
		Turn_Off_Blue();//turn off the blue LED
		Turn_Off_Green();//turn off green LED
		Turn_Off_Yellow();//turn off yellow LED
		
		HAL_Delay(500);//Wait for 0.5 second
	}
}
void PlaySimonTheme(void) {
    for (uint16_t i = 0; i < 17; i++) {
        uint32_t freq = simon_notes[i];
        uint32_t dur = simon_durations[i];

        // Pick LED for this tone (optional mapping)
        if (freq == SIMON_C4) {
            Turn_On_Red();
        } else if (freq == SIMON_E4) {
            Turn_On_Yellow();
        } else if (freq == SIMON_G4) {
            Turn_On_Blue();
        } else if (freq == SIMON_G3) {
            Turn_On_Green();
        }

        PlayHz(freq, dur);

        Turn_Off_Red();
        Turn_Off_Blue();
        Turn_Off_Green();
        Turn_Off_Yellow();

        // Short rest between notes
        PlayHz(NOTE_REST, 50);
    }
}
void PlaySimonThemeRev(void) {
    for (int i = 16; i > -1; i--) {
        uint32_t freq = simon_notes[i];
        uint32_t dur = simon_durations[i];

        // Pick LED for this tone (optional mapping)
        if (freq == SIMON_C4) {
            Turn_On_Red();
        } else if (freq == SIMON_E4) {
            Turn_On_Yellow();
        } else if (freq == SIMON_G4) {
            Turn_On_Blue();
        } else if (freq == SIMON_G3) {
            Turn_On_Green();
        }

        PlayHz(freq, dur);

        Turn_Off_Red();
        Turn_Off_Blue();
        Turn_Off_Green();
        Turn_Off_Yellow();

        // Short rest between notes
        PlayHz(NOTE_REST, 50);
    }
}

uint8_t start_game(uint8_t *pattern){
    get_pattern(pattern);//get a random pattern

    uint8_t game_on = 1;
    level = 1;  // Reset level at start of game
    CURRENT_LENGTH = game_diff + level;

    while(game_on)  //
    {
        // Display current level
        Write_Instr_LCD(0x01);  // Clear LCD
        Write_String_LCD("Level: ");
        // Convert level to character and display
        Write_Char_LCD('0' + level);
        Write_Instr_LCD(0xc0);  // Move to second line
        Write_String_LCD("Get ready...");
        HAL_Delay(1000);  // Give player time to prepare
        
        play_pattern(pattern);
        
        if(compare_pattern(pattern) == 1){
            //if it is correct
            Write_Instr_LCD(0x01);
            Write_String_LCD("Level Complete!");
            
            // Visual success indicator (flash all LEDs)
            for(int i = 0; i < 3; i++) {
                Turn_On_Red();
                Turn_On_Yellow();
                Turn_On_Green();
                Turn_On_Blue();
                HAL_Delay(200);
                Turn_Off_Red();
                Turn_Off_Yellow();
                Turn_Off_Green();
                Turn_Off_Blue();
                HAL_Delay(200);
            }
            
            level++;
            CURRENT_LENGTH = game_diff + level;
            
            // Check if game is complete
            if(level == 32) {//if the user win 32 consecutive rounds, they win
                Write_Instr_LCD(0x01);
                Write_String_LCD("You Win!");
                Write_Instr_LCD(0xc0);
                Write_String_LCD("Game Complete!");
                HAL_Delay(3000);
                game_on = 0;
            } else {
                HAL_Delay(1000);  // Short pause before next level
            }
        } else {
            // Game over
            Write_Instr_LCD(0x01);
            Write_String_LCD("Game Over!");
            Write_Instr_LCD(0xc0);
            Write_String_LCD("Level: ");
            Write_Char_LCD('0' + (level-1));  // Show the level they reached
						PlaySimonThemeRev();
            HAL_Delay(3000);
            game_on = 0;
            return level;
        }
    }
		return level;
}

uint8_t compare_pattern(uint8_t *pattern)
{
  uint8_t valid;
  uint8_t user_input[CURRENT_LENGTH];
  for(uint8_t i = 0; i < (game_diff + 1)* level;i++){//take the user input
    do{
      user_input[i] = take_LED_input();
      if(user_input[i] >= 4){
        valid = 0;
      }else{
        valid = 1;
      }
    }while(valid == 0);
  }

  for(uint8_t i = 0; i < CURRENT_LENGTH; i++){
    if(user_input[i] != pattern[i]){
      return 0;
    }
  }
  
  return 1;
}
void game_over_sequence(uint8_t high_score)
{
	char* line1;
	char* line2;
	char score_string[16] = "High Score:";
	int pos = 11;

	line1 = "Game Over";
	
	 
     if (high_score >= 10) {
        score_string[pos++] = '0' + (high_score / 10);
        score_string[pos++] = '0' + (high_score % 10);
    } else {
        score_string[pos++] = '0' + high_score;
    }
    score_string[pos] = '\0';  
    
    line2 = score_string;
	
	 
	
		
		Write_Instr_LCD(0x01);
		
		Write_String_LCD(line1);
		
		Write_Instr_LCD(0xc0);
		
		Write_String_LCD(line2);
		
		flash_leds_sequence();
}

void flash_leds_sequence(void)
{
	uint8_t i;
	
	for (i = 0; i < 3 ; i++)
	{
		// red 
				GPIOC->ODR |= (1<<10);
				PlayHz(SIMON_C4, 50);
        Delay(150);
        GPIOC->ODR &= ~(1<<10);
		// yelow 
				GPIOC->ODR |= (1<<11);
				PlayHz(SIMON_E4, 50);
        Delay(150);
        GPIOC->ODR &= ~(1<<11);
		// blue 
				GPIOH->ODR |= (1<<0);
				PlayHz(SIMON_G4, 50);
        Delay(150);
        GPIOH->ODR &= ~(1<<0);
		// green
				GPIOC->ODR |= (1<<2);
				PlayHz(SIMON_G3, 50);
        Delay(150);
        GPIOC->ODR &= ~(1<<2);
    }
	for (i = 0; i <5; i++)
		{
			// led on 
				GPIOC->ODR |= (1<<10);  
        GPIOC->ODR |= (1<<11); 
        GPIOH->ODR |= (1<<0);   
        GPIOC->ODR |= (1<<2);
				
			Delay(200);
			
			// led off 
			 GPIOC->ODR &= ~(1<<10); 
        GPIOC->ODR &= ~(1<<11); 
        GPIOH->ODR &= ~(1<<0); 
        GPIOC->ODR &= ~(1<<2);
			
			Delay(200);
		}
}

void play_pattern(uint8_t *pattern)
{
  for(uint8_t i = 0; i < (game_diff + 1)* level; i++){
    if(pattern[i] == 0){
      Turn_On_Red();
      PlayHz(SIMON_C4, 50);
      //Write_Char_LCD('0');
      HAL_Delay(200);
      Turn_Off_Red();
      HAL_Delay(200);
    }else if(pattern[i] == 1){
      Turn_On_Yellow();
      PlayHz(SIMON_E4, 50);
      //Write_Char_LCD('1');
      HAL_Delay(200);
      Turn_Off_Yellow();
      HAL_Delay(200);
    }else if(pattern[i] == 2){
      Turn_On_Blue();
      PlayHz(SIMON_G4, 50);
      //Write_Char_LCD('2');
      HAL_Delay(200);
      Turn_Off_Blue();
      HAL_Delay(200);
    }else{
      Turn_On_Green();
      PlayHz(SIMON_G3, 50);
      //Write_Char_LCD('3');
      HAL_Delay(200);
      Turn_Off_Green();
      HAL_Delay(200);
    }
}
}

void DelayMicroseconds(unsigned int us)
{
    while (us--) {
        __asm__("nop");  // Each NOP takes 1 cycle = 1µs at 1MHz
    }
}
void PlayHz(uint32_t frequency, uint32_t duration_ms) {
    // Handle rest notes (frequency = 0) as a simple delay
    if (frequency == NOTE_REST) {
        Delay(duration_ms);
        return;
    }
    
    uint32_t i;
    uint32_t period_us = 1000000 / frequency;       // Period of the wave in microseconds
    uint32_t delay = period_us / 2;                 // Half-period for high and low
    uint32_t cycles = (duration_ms * 1000) / period_us;  // Number of cycles to fit in the given duration

    for (i = 0; i < cycles; i++) {
        GPIOC->ODR |= (1 << 9);   // Set pin high
        DelayMicroseconds(delay);
        GPIOC->ODR &= ~(1 << 9);  // Set pin low
        DelayMicroseconds(delay);
    }
}

void Delay(unsigned int n)
{
	int i;
    for (; n > 0; n--)
        for (i = 0; i < 136; i++) ;
	}



void LCD_Init()
	{
		uint32_t temp;
		
        /* enable GPIOA clock */ 
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; 
        /* enable GPIOB clock */ 
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
        /*PB5 MOSI, PA10 /CS_7 latch , PA5 shift clock */

			 
        /*PA5 and PA10 are outputs*/ temp = GPIOA->MODER;
        temp &= ~(0x03<<(2*5)); temp|=(0x01<<(2*5)); 
        temp &= ~(0x03<<(2*10)); temp|=(0x01<<(2*10)); 
        GPIOA->MODER = temp;
			 
        temp=GPIOA->OTYPER;
        temp &=~(0x01<<5);
        temp &=~(0x01<<10); GPIOA->OTYPER=temp;

        temp=GPIOA->PUPDR;
        temp&=~(0x03<<(2*5));
        temp&=~(0x03<<(2*10)); GPIOA->PUPDR=temp;

        /*PB5 is output*/

        temp = GPIOB->MODER;
        temp &= ~(0x03<<(2*5)); 
        temp|=(0x01<<(2*5)); 
        GPIOB->MODER = temp;

			 
        temp=GPIOB->OTYPER;
        temp &=~(0x01<<5); 
        GPIOB->OTYPER=temp;

            
        temp=GPIOB->PUPDR;
        temp&=~(0x03<<(2*5)); 
        GPIOB->PUPDR=temp;

		
		
        /* LCD controller reset sequence */ 
        Delay(20);
        LCD_nibble_write(0x30,0); 
        Delay(5); 
        LCD_nibble_write(0x30,0); 
        Delay(1); 
        LCD_nibble_write(0x30,0);
        Delay(1); 
        LCD_nibble_write(0x20,0); 
        Delay(1);

        Write_Instr_LCD(0x28); /* set 4 bit data LCD - two line display - 5x8 font*/ 
        Write_Instr_LCD(0x0E); /* turn on display, turn on cursor , turn off blinking */ 
        Write_Instr_LCD(0x01); /* clear display screen and return to home position*/ 
        Write_Instr_LCD(0x06); /* move cursor to right (entry mode set instruction)*/


}

	
	
void LCD_nibble_write(uint8_t temp, uint8_t s){

/*writing instruction*/ 
if (s==0){ 
	temp=temp&0xF0;
	temp=temp|0x02; /*RS (bit 0) = 0 for Command EN (bit1)=high */ 
	Write_SR_LCD(temp);

    temp=temp&0xFD; /*RS (bit 0) = 0 for Command EN (bit1) = low*/ 
    Write_SR_LCD(temp);	}

/*writing data*/ 
else if (s==1) {
	temp=temp&0xF0;
  temp=temp|0x03;	/*RS(bit 0)=1 for data EN (bit1) = high*/ 
  Write_SR_LCD(temp);

  temp=temp&0xFD; /*RS(bit 0)=1 for data EN(bit1) = low*/ 
  Write_SR_LCD(temp); 
}}

	
	

void Write_String_LCD(char *temp) 
{ 
    int i=0;

    while(temp[i]!=0)
        {
            Write_Char_LCD(temp[i]); i=i+1;
        }
}




void Write_Instr_LCD(uint8_t code)
{
LCD_nibble_write(code&0xF0,0);

code=code<<4; LCD_nibble_write(code,0);
}


void Write_Char_LCD(uint8_t code)
{
    LCD_nibble_write(code&0xF0,1);

    code=code<<4;
    LCD_nibble_write(code,1);
}


void Write_SR_LCD(uint8_t temp)
{
int i;
uint8_t mask=0b10000000;
	
for(i=0; i<8; i++) {
        if((temp&mask)==0)
        GPIOB->ODR&=~(1<<5);
        else
        GPIOB->ODR|=(1<<5);

        /*	Sclck */
        GPIOA->ODR&=~(1<<5); GPIOA->ODR|=(1<<5);
        Delay(1);

        mask=mask>>1;
        }

    /*Latch*/
    GPIOA->ODR|=(1<<10); 
    GPIOA->ODR&=~(1<<10);
}

	
	
uint8_t take_user_input(){
	if((GPIOB->IDR &(0x1<<8))==0)
		GPIOA->ODR&=~(1<<1);
		else{
		GPIOA->ODR|=(1<<1);
			Delay(25);
		return 0;
		}
		if((GPIOB->IDR & (0x1 << 9))==0)//if button is not press
			GPIOA -> ODR &=~(0x01);
		else{
			GPIOA ->ODR |= 1;
			Delay(25);
			return 1;
		}
		if((GPIOB->IDR & (0x1 << 10))==0)//if button is not press
			GPIOC -> ODR &=~(0x01 << 7);
		else{
			GPIOC ->ODR |= (0x01<<7);
			Delay(25);
			return 2;
		}
		if((GPIOB->IDR & (0x1 << 11))==0)//if button is not press
			GPIOC -> ODR &=~(0x01 << 8);
		else{
			GPIOC ->ODR |= (0x01<<8);
			
			Delay(25);
			return 3;
		}
		return 4;
}
void Init_Red_LED()//connect to PC10
{
	uint32_t temp;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;	/* enable GPIO clock */

  temp = GPIOC->MODER;
  temp &= ~(0x03<<(2*10)); 
  temp|=(0x01<<(2*10)); 
  GPIOC->MODER = temp;

  temp=GPIOC->OTYPER;
  temp &=~(0x01<<10); 
  GPIOC->OTYPER=temp;

  temp=GPIOC->PUPDR;
  temp&=~(0x03<<(2*10));
  GPIOC->PUPDR=temp;
}

void Init_Yellow_LED()//connect to PC11
{
	uint32_t temp;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;	/* enable GPIOC clock */

  temp = GPIOC->MODER;
  temp &= ~(0x03<<(2*11)); 
  temp|=(0x01<<(2*11)); 
  GPIOC->MODER = temp;

  temp=GPIOC->OTYPER;
  temp &=~(0x01<<11); 
  GPIOC->OTYPER=temp;

  temp=GPIOC->PUPDR;
  temp&=~(0x03<<(2*11));
  GPIOC->PUPDR=temp;
}

void Init_Blue_LED()//connect to PH0
{
	uint32_t temp;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOHEN;	/* enable GPIO clock */

  temp = GPIOH->MODER;
  temp &= ~(0x03<<(2*0)); 
  temp|=(0x01<<(2*0)); 
  GPIOH->MODER = temp;

  temp=GPIOH->OTYPER;
  temp &=~(0x01<<0); 
  GPIOH->OTYPER=temp;

  temp=GPIOH->PUPDR;
  temp&=~(0x03<<(2*0));
  GPIOH->PUPDR=temp;
}
void Init_Green_LED()//connect to PC2
{
	uint32_t temp;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;	/* enable GPIOA clock */

  temp = GPIOC->MODER;
  temp &= ~(0x03<<(2*2)); 
  temp|=(0x01<<(2*2)); 
  GPIOC->MODER = temp;

  temp=GPIOC->OTYPER;
  temp &=~(0x01<<2); 
  GPIOC->OTYPER=temp;

  temp=GPIOC->PUPDR;
  temp&=~(0x03<<(2*2));
  GPIOC->PUPDR=temp;
}

void Init_Red_Button() //Connect to PC12
{
	uint32_t temp;    

    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;  /* enable GPIOC clock */

    temp = GPIOC->MODER;
    temp &= ~(0x03<<(2*12));  // Set as input
    GPIOC->MODER = temp; 

    temp = GPIOC->OTYPER;
    temp &= ~(0x01<<12);
    GPIOC->OTYPER = temp;

    temp = GPIOC->PUPDR;
    temp &= ~(0x03<<(2*12));  // Clear previous settings
    temp |= (0x02<<(2*12));   // Enable pull-down resistor
    GPIOC->PUPDR = temp;
}

void Init_Yellow_Button() //Connect to PD2
{
	uint32_t temp;    

  RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;  /* enable GPIOB clock */
      
  temp = GPIOD->MODER;
  temp &= ~(0x03<<(2*2));
  GPIOD->MODER = temp; 
  
  
  temp=GPIOD->OTYPER;
  temp &=~(0x01<<2);
  GPIOD->OTYPER=temp;


  temp=GPIOD->PUPDR;
  temp&=~(0x03<<(2*2));
	temp |= (0x02<<(2*2));   // Enable pull-down resistor
  GPIOD->PUPDR=temp;
}

void Init_Blue_Button() //Connect to PH1
{
	uint32_t temp;    

  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOHEN;  /* enable GPIOB clock */
      
  temp = GPIOH->MODER;
  temp &= ~(0x03<<(2*1));
  GPIOH->MODER = temp; 
  
  
  temp=GPIOH->OTYPER;
  temp &=~(0x01<<1);
  GPIOH->OTYPER=temp;


  temp=GPIOH->PUPDR;
  temp&=~(0x03<<(2*1));
	temp |= (0x02<<(2*1));   // Enable pull-down resistor
  GPIOH->PUPDR=temp;
}

void Init_Green_Button() //Connect to PC3
{
	uint32_t temp;    

  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;  /* enable GPIOB clock */
      
  temp = GPIOC->MODER;
  temp &= ~(0x03<<(2*3));
  GPIOC->MODER = temp; 
  
  
  temp=GPIOC->OTYPER;
  temp &=~(0x01<<3);
  GPIOC->OTYPER=temp;


  temp=GPIOC->PUPDR;
  temp&=~(0x03<<(2*3));
	temp |= (0x02<<(2*3));   // Enable pull-down resistor
  GPIOC->PUPDR=temp;
}
/*
Hardware board function
*/
void Init_PushButton_5()
{			
  uint32_t temp;    

  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;  /* enable GPIOB clock */
      
  temp = GPIOB->MODER;
  temp &= ~(0x03<<(2*8));
  GPIOB->MODER = temp; 
  
  
  temp=GPIOB->OTYPER;
  temp &=~(0x01<<8);
  GPIOB->OTYPER=temp;


  temp=GPIOB->PUPDR;
  temp&=~(0x03<<(2*8));
  GPIOB->PUPDR=temp;

}

void Init_PushButton_4()//connect to pb9
{
	uint32_t temp;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	
	temp = GPIOB -> MODER;//set to input
	temp &= ~(0x03 << (2*9));
	GPIOB ->MODER = temp;
	
	temp = GPIOB -> OTYPER;
	temp &= ~(0x01 << 9);
	GPIOB -> OTYPER = temp;
	
	temp = GPIOB -> PUPDR;
	temp &= ~(0x03 << 2*9);
	GPIOB -> PUPDR = temp;
}

void Init_PushButton_3()//connect to pb10
{
	uint32_t temp;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	
	temp = GPIOB -> MODER;//set to input
	temp &= ~(0x03 << (2*10));
	GPIOB ->MODER = temp;
	
	temp = GPIOB -> OTYPER;
	temp &= ~(0x01 << 10);
	GPIOB -> OTYPER = temp;
	
	temp = GPIOB -> PUPDR;
	temp &= ~(0x03 << 2*10);
	GPIOB -> PUPDR = temp;
}

void Init_PushButton_2()//connect to pb11
{
	uint32_t temp;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	
	temp = GPIOB -> MODER;//set to input
	temp &= ~(0x03 << (2*11));
	GPIOB ->MODER = temp;
	
	temp = GPIOB -> OTYPER;
	temp &= ~(0x01 << 11);
	GPIOB -> OTYPER = temp;
	
	temp = GPIOB -> PUPDR;
	temp &= ~(0x03 << 2*11);
	GPIOB -> PUPDR = temp;
}


void Init_LED0()
	{
    uint32_t temp;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;;	/* enable GPIOA clock */

    temp = GPIOA->MODER;
    temp &= ~(0x03<<(2*1)); 
    temp|=(0x01<<(2*1)); 
    GPIOA->MODER = temp;

    temp=GPIOA->OTYPER;
    temp &=~(0x01<<1); 
    GPIOA->OTYPER=temp;

    temp=GPIOA->PUPDR;
    temp&=~(0x03<<(2*1));
    GPIOA->PUPDR=temp;

	}

void Init_LED1(void)//connect to PA0
{
	uint32_t temp;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN; //enable GPIOA clock
	
	temp = GPIOA -> MODER;
	temp &= ~(0x03);//set to output
	temp |= (0x01);
	GPIOA->MODER = temp;
	
	temp = GPIOA ->OTYPER;//set output type
	temp &= ~(0x01);
	GPIOA->OTYPER = temp;
	
	temp = GPIOA ->PUPDR;
	temp &= ~(0x03);
	GPIOA ->PUPDR = temp;
}	

void Init_LED2(void)//connect to Pc7
{
	uint32_t temp;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; //enable GPIOA clock
	
	temp = GPIOC -> MODER;
	temp &= ~(0x03<< 2*7);//set to output
	temp |= (0x01 << 2*7);
	GPIOC->MODER = temp;
	
	temp = GPIOC ->OTYPER;//set output type
	temp &= ~(0x01 << 7);
	GPIOC->OTYPER = temp;
	
	temp = GPIOC ->PUPDR;
	temp &= ~(0x03 << 2*7);
	GPIOC ->PUPDR = temp;
}	

void Init_LED3(void)//connect to Pc8
{
	uint32_t temp;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN; //enable GPIOA clock
	
	temp = GPIOC -> MODER;
	temp &= ~(0x03 << 2*8);//set to output
	temp |= (0x01 << 2*8);
	GPIOC->MODER = temp;
	
	temp = GPIOC ->OTYPER;//set output type
	temp &= ~(0x01 << 8);
	GPIOC->OTYPER = temp;
	
	temp = GPIOC ->PUPDR;
	temp &= ~(0x03 << 2*8);
	GPIOC ->PUPDR = temp;
}	


void Init_buzzer() //connect to pc9
{
	uint32_t temp;
	RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	
	temp = GPIOC ->MODER;
	temp &= ~ (0x03 << 2*9);
	temp |= (0x01<<2*9);
	GPIOC -> MODER = temp;
	
	temp = GPIOC->OTYPER;
	temp &= ~(0x01 << 9);
	GPIOC ->OTYPER = temp;
	
	temp = GPIOC -> PUPDR;
	temp &= ~(0x03 << 2*9);
	GPIOC -> PUPDR = temp;
}

void Increase_Diff(uint8_t *diff)
{
	
	
	if (*diff >= 2) {			
			// dereference pointer to compare value
		char* line1 = "Max Level";
		char* line2 = "is achieved";
		Write_Instr_LCD(0x01);
		//Write_String_LCD("     ");
		Write_String_LCD(line1);
		Write_Instr_LCD(0xc0);
		Write_String_LCD(line2);
	} else {
		(*diff)++;	
		char diffc;
		if(*diff == 2)
			diffc = '2';
		else if(*diff == 1)
			diffc = '1';
		else 
			diffc = '0';
		Write_Instr_LCD(0x01);
		Write_String_LCD("Difficulty: ");
		Write_Char_LCD(diffc);
		Delay(25);
						// increment difficulty value
	}
}

// decrease function
void Decrease_Diff(uint8_t *diff)
{
	
	if (*diff <= 0) {			// dereference pointer to compare value
		char* line1 = "Min Level";
		char* line2 = "is achieved";
		Write_Instr_LCD(0x01);
		//Write_String_LCD("     ");
		Write_String_LCD(line1);
		Write_Instr_LCD(0xc0);
		Write_String_LCD(line2);
	} else {
        (*diff)--;	
		char diffc;
		if(*diff == 1)
			diffc = '1';
		else if(*diff == 2)
			diffc = '2';
		else
			diffc = '0';
		Write_Instr_LCD(0x01);
		Write_String_LCD("Difficulty: ");
		Write_Char_LCD(diffc);
				// decrement difficulty value
	}
}
uint8_t random_LED(void){
	uint8_t randint = rand() % 4;
	return randint;
}

void get_pattern( uint8_t *arr) {
    // Generate random pattern for the current level and difficulty
    for(uint8_t i = 0; i < MAXLEVEL; i++) {
            arr[i] = random_LED();  // Set a random LED for the current index
        }
    }

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
