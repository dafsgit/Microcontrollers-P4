/* 
 * File:   main.c
 * Author: dafne
 *
 * Created on 3 de octubre de 2021, 08:11 PM
 */

//********************
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


// PIC18F4550 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1L
#pragma config PLLDIV = 5       // PLL Prescaler Selection bits (Divide by 5 (20 MHz oscillator input))
#pragma config CPUDIV = OSC3_PLL4// System Clock Postscaler Selection bits ([Primary Oscillator Src: /3][96 MHz PLL Src: /4])
#pragma config USBDIV = 2       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes from the 96 MHz PLL divided by 2)

// CONFIG1H
#pragma config FOSC = HSPLL_HS  // Oscillator Selection bits (HS oscillator, PLL enabled (HSPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = ON        // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = OFF     // CCP2 MUX bit (CCP2 input/output is multiplexed with RB3)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

//********************
#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdbool.h>

#include "stdio.h"
#include "stdlib.h"
//#include <p18f4550.h>

/*
 * 
 */

void TMR0_WriteTimer(uint16_t timerVal){
    // Write to the Timer0 registers
    TMR0H = (timerVal >> 8);
    TMR0L = (uint8_t) timerVal;
}

void parseNote(unsigned char n){
    int df = 0;
    uint16_t init = 0;
    switch(n){
        case 'c': //261.63 Hz
            df = 523;
            init = 63624; // T = 3822 us -> T/2 = 1911 us
            break;
        case 'd': //293.67 Hz
            df = 587;
            init = 63832; // T = 3405 us -> T/2 = 1703 us
            break;
        case 'e': //329.63 Hz
            df = 659;
            init = 64018; // T = 3034 us -> T/2 = 1517 us
            break;
        case 'f': //349.23 Hz
            df = 699;
            init = 64103; // T = 2864 us -> T/2 = 1432 us
            break;
        case 'g': //392 Hz
            df = 784;
            init = 64259; // T = 2551 us -> T/2 = 1276 us
            break;
        case 'a': //440 Hz
            df = 880;
            init = 64398; // T = 2273 us -> T/2 = 1137 us
            break;
        case 'b': //493.88 Hz
            df = 988;
            init = 64523; // T = 2025 us -> T/2 = 1012 us
            break;
        case 'C': //277.18 Hz
            df = 554;
            init = 63731; // T = 3608 us -> T/2 = 1804 us
            break;
        case 'D': //311.13 Hz
            df = 622;
            init = 63928; // T = 3214 us -> T/2 = 1607 us
            break;
        case 'F': //369.99 Hz
            df = 740;
            init = 64183; // T = 2703 us -> T/2 = 1352 us
            break;
        case 'G': //415.3 Hz
            df = 831;
            init = 64331; // T = 2408 us -> T/2 = 1204 us
            break;
        case 'A': //466.16 Hz
            df = 932;
            init = 64462; // T = 2145 us -> T/2 = 1073 us
            break;
        // ...
        case 's': //0 Hz
            df = 0;
            init = 0;
            break;
        default: // case 'c' -> 261.63 Hz
            df = 523;
            init = 63624; // T = 3822 us -> T/2 = 1911 us          
            break;
    }
    T0CONbits.TMR0ON = 0;
    INTCONbits.TMR0IF = 0;
    if(df == 0){
        PORTDbits.RD4 = 0;
        for(int i=0; i<=523*2; i++){
            TMR0_WriteTimer(63624);
            T0CONbits.TMR0ON = 1;
            while(INTCONbits.TMR0IF == 0);
            T0CONbits.TMR0ON = 0;
            INTCONbits.TMR0IF = 0;
        } 
    }else{
        for(int i=0; i<=df*2; i++){
            if(PORTDbits.RD4 == 0){
                PORTDbits.RD4 = 1;
            }else if(PORTDbits.RD4 == 1){
                PORTDbits.RD4 = 0;
            }
            TMR0_WriteTimer(init);
            T0CONbits.TMR0ON = 1;
            while(INTCONbits.TMR0IF == 0);
            T0CONbits.TMR0ON = 0;
            INTCONbits.TMR0IF = 0;
        } 
    }
}

void firstSong(){ // SUPER MARIO BROS
    // MI - MI - MI - DO - MI - SOL
    // DO - SOL- FA- LA- SI- LA#- LA- SOL- MI- SOL- LA- FA- SOL- MI- DO- RE- SI
    unsigned char notas[] = {'e','e','e','c','e','g','c','g','f','a','b','A','a','g','e','g','a','f','g','e','c','d','b'};
    for(int i=0; i<23; i++){
        parseNote(notas[i]); //tocar nota a la frecuencia determinada
    }
}

void secondSong(){ // ATTACK ON TITAN
    // C-C-e-D-------C---C-e-D---|
    // C-C-----------C---C-------|
    // G-G-e-D---b-b-G---G-e-D---|
    // ----------b-b-------------
    unsigned char notas[] = {'C','C','e','D','s','s','s','C','s','C','e','D','s','C','C','s','s','s','s','s','C','s','C','s','s','s','G','G','e','D','s','b','b','G','s','G','e','D','s','s','s','s','s','s','b','b'};
    for(int i=0; i<46; i++){
        parseNote(notas[i]); //tocar nota a la frecuencia determinada
    }
}

void thirdSong(){ // HARRY POTTER
    // B B E G F# E
    // B A F# s
    // E G F# Eb
    // F B B s

    // B B E G F# E
    // B D s s s  Db C
    // Ab C B Bb Bb Bb
    // G E
    unsigned char notas[] = {'b','b','e','g','F','e','b','a','F','s','e','g','F','D','f','b','b','s','b','b','e','g','F','e','b','d','s','s','s','C','c','G','c','b','A','A','A','g','e'};
    for(int i=0; i<39; i++){
        parseNote(notas[i]); //tocar nota a la frecuencia determinada
    }
}

void main(void) {
       
    TRISD = 0b00001110;
    TRISB = 0b00000000;
    
    //PORTA, PORTB and PORTE are digital
    ADCON1bits.PCFG = 0xF; 
    
    // SCS INTOSC; IDLEN disabled; IRCF 4MHz; 
    OSCCON = 0x60;
    // INTSRC 31kHz derived from INTRC internal oscillator; TUN = 0
    OSCTUNE = 0x00;
    
    INTCONbits.GIE = 1;
    //INTCONbits.PEIE = 1;
    INTCONbits.TMR0IF = 0;
    INTCONbits.TMR0IE = 1;
    T0CONbits.T0CS = 0;
    T0CONbits.T0SE = 0;
    T0CONbits.T08BIT = 0;
    /*
    T0CONbits.PSA = 0;
    T0CONbits.T0PS = 0b011; //cada 1 segundo (1:16)
    TMR0_WriteTimer(3035);
    */
    T0CONbits.PSA = 1;
    
    PORTDbits.RD4 = 0;
    PORTB = 0b11111111;
    while(1){
        if(PORTDbits.RD1 == 1){
            firstSong();
        }else if(PORTDbits.RD2 == 1){
            secondSong();
        }else if(PORTDbits.RD3 == 1){
            thirdSong();
        }
    }

    //return 1;
}
