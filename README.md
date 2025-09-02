# My Magic Wand PCB Project
## Project Member
Tuan Kiet Le - Electrical Engineering
## Project Objective
As an electrial engineering student, being able to understand how **Printed Circuit Board (PCB)** works is very important. Therefore, I have decided to make an intro project for my first PCB design ever. The expected outcomes from this project are:
* understanding the process of making a PCB, including: designing schematic, finding an appropriate footprint for each component, modifying route appropriately, and exporting Gerber and Drill files.
* being able to solder components on the PCB.
* getting used to digital IC chips, especially the 555 Timer.
## Introduction
For this project, I am designing a custom PCB for a "magic wand" that brings a touch of enchantment through a sequence of blinking LEDs. The goal of the project is to create a compact, handheld wand that lights up in a programmed pattern, simulating a magical effect. Using simple IC digital chips and a series of LEDs, this project will cover essential PCB design principles, including component layout, circuit routing, and power management. The wand will create dazzling light sequences, offering an interactive and visually engaging experience. This project not only combines electronics with creativity but also offers hands-on experience in designing a functional and aesthetic PCB.
## Project Result
The aim of this project is to create a PCB-based "magic wand" that performs a dynamic LED blinking sequence, adjustable by user input. The circuit will utilize IC components such as the 555 timer, binary counter, and decoder, with two potentiometers to adjust the LED blinking speed.

The 555 timer generates the clock pulses, whose frequency can be adjusted using the potentiometers. The clock signal drives the binary counter, which outputs sequential signals. These are then processed by the decoder to illuminate each LED in a specific sequence, creating a flowing or animated effect.

This design emphasizes user interaction, low power consumption, and precise control of LED timing, making the wand visually engaging and customizable.
## Materials Used
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
