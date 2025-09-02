# Simon Says Game With the STM32L476RGTx
## Project Member
Tuan Kiet Le - Electrical Engineering
## Features
* 4 Colored LEDs: Red, Yellow, Blue, Green pattern display
* 8 Buttons: 4 colored game buttons + 4 control buttons for menu navigation
* LCD Display: 16x2 character display showing game status, difficulty, and level
* Audio Feedback: Buzzer generates unique tones for each color
* Adjustable Difficulty: Three difficulty levels (Easy, Medium, Hard)
* Progressive Gameplay: Up to 10 levels with increasing sequence length
## Hardware Components
* STM32L476 microcontroller
* 8 LEDs (4 for game pattern, 4 for feedback)
* 8 Push buttons
* 16x2 LCD display with shift register interface
* Buzzer for audio output
* Breadboard and connecting components
## Pin Configuration
### Game LEDs
* Red LED: PC10
* Yellow LED: PC11
* Blue LED: PH0
* Green LED: PC2
### Game Buttons
* Red Button: PC12
* Yellow Button: PD2
* Blue Button: PH1
*Green Button: PC3
Control Buttons

SW5 (PB8): Start game
SW4 (PB9): Increase difficulty
SW3 (PB10): Decrease difficulty

Audio & Display

Buzzer: PC9
LCD Interface: PA5 (clock), PA10 (latch), PB5 (data)
* 3 AAA battery holder.
* 1 TI CD74HC138E: IC DECODER/DEMUX 1X3:8 16DIP.
* 1 TI SN74HC393N: IC BINARY COUNTER DL 4BIT 14DIP.
* 1 LM 555 : 555 Timer.
* 8 100 Ohm Resistors.
* 2 100K Potentiometer.
* 1 Switch.
* 8 Green LEDs.
* 1 47uF Electrolytic capacitor.
* 4 0.1uF Ceramic capacitor.
* 1 10uF Ceramic capacitor.
## Works Cited
* Crash Course Electronics and PCB design. https://www.udemy.com/course/crash-course-electronics-and-pcb-design/?kw=PCB+crash&src=sac&couponCode=ST20MT111124B
* 555 Oscillator Works. https://www.electronics-tutorials.ws/waveforms/555_oscillator.html
