/* 
 * File:   main.c
 * Author: dafne
 *
 * Created on 3 de octubre de 2021, 08:11 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <p18f4550.h>

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
        PORTDbits.RD0 = 0;
        for(int i=0; i<=523; i++){
            TMR0_WriteTimer(63624);
            T0CONbits.TMR0ON = 1;
            while(INTCONbits.TMR0IF == 0);
            T0CONbits.TMR0ON = 0;
            INTCONbits.TMR0IF = 0;
        } 
    }else{
        for(int i=0; i<=df; i++){
            if(PORTDbits.RD0 == 0){
                PORTDbits.RD0 = 1;
            }else if(PORTDbits.RD0 == 1){
                PORTDbits.RD0 = 0;
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

int main(int argc, char** argv) {
    //PORTA, PORTB and PORTE are digital
    ADCON1bits.PCFG = 0xF; 
    
    // SCS INTOSC; IDLEN disabled; IRCF 4MHz; 
    OSCCON = 0x60;
    // INTSRC 31kHz derived from INTRC internal oscillator; TUN = 0
    OSCTUNE = 0x00;
    
    TRISD = 0b00001110;
    
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
    
    while(1){
        if(PORTDbits.RD1 == 1){
            firstSong();
        }else if(PORTDbits.RD2 == 1){
            secondSong();
        }else if(PORTDbits.RD3 == 1){
            thirdSong();
        }
    }

    return 1;
}

/*
switch(n){
        case 'c': //261.63 Hz
            for(int i=0; i<=523; i++){
                if(PORTDbits.RD0 == 0){
                    PORTDbits.RD0 = 1;
                }else if(PORTDbits.RD0 == 1){
                    PORTDbits.RD0 = 0;
                }
                TMR0_WriteTimer(63624); // T = 3822 us -> T/2 = 1911 us
                T0CONbits.TMR0ON = 1;
                while(INTCONbits.TMR0IF == 0);
                T0CONbits.TMR0ON = 0;
                INTCONbits.TMR0IF = 0;
            }
            break;
        case 'd': //293.67 Hz
            for(int i=0; i<=587; i++){
                if(PORTDbits.RD0 == 0){
                    PORTDbits.RD0 = 1;
                }else if(PORTDbits.RD0 == 1){
                    PORTDbits.RD0 = 0;
                }
                TMR0_WriteTimer(63832); // T = 3405 us -> T/2 = 1703 us
                T0CONbits.TMR0ON = 1;
                while(INTCONbits.TMR0IF == 0);
                T0CONbits.TMR0ON = 0;
                INTCONbits.TMR0IF = 0;
            }
            break;
        case 'e': //329.63 Hz
            for(int i=0; i<=659; i++){
                if(PORTDbits.RD0 == 0){
                    PORTDbits.RD0 = 1;
                }else if(PORTDbits.RD0 == 1){
                    PORTDbits.RD0 = 0;
                }
                TMR0_WriteTimer(64018); // T = 3034 us -> T/2 = 1517 us
                T0CONbits.TMR0ON = 1;
                while(INTCONbits.TMR0IF == 0);
                T0CONbits.TMR0ON = 0;
                INTCONbits.TMR0IF = 0;
            }
            break;
        case 'f': //349.23 Hz
            for(int i=0; i<=699; i++){
                if(PORTDbits.RD0 == 0){
                    PORTDbits.RD0 = 1;
                }else if(PORTDbits.RD0 == 1){
                    PORTDbits.RD0 = 0;
                }
                TMR0_WriteTimer(64103); // T = 2864 us -> T/2 = 1432 us
                T0CONbits.TMR0ON = 1;
                while(INTCONbits.TMR0IF == 0);
                T0CONbits.TMR0ON = 0;
                INTCONbits.TMR0IF = 0;
            }
            break;
        case 'g': //392 Hz
            for(int i=0; i<=784; i++){
                if(PORTDbits.RD0 == 0){
                    PORTDbits.RD0 = 1;
                }else if(PORTDbits.RD0 == 1){
                    PORTDbits.RD0 = 0;
                }
                TMR0_WriteTimer(64259); // T = 2551 us -> T/2 = 1276 us
                T0CONbits.TMR0ON = 1;
                while(INTCONbits.TMR0IF == 0);
                T0CONbits.TMR0ON = 0;
                INTCONbits.TMR0IF = 0;
            }
            break;
        case 'a': //440 Hz
            for(int i=0; i<=880; i++){
                if(PORTDbits.RD0 == 0){
                    PORTDbits.RD0 = 1;
                }else if(PORTDbits.RD0 == 1){
                    PORTDbits.RD0 = 0;
                }
                TMR0_WriteTimer(64398); // T = 2273 us -> T/2 = 1137 us
                T0CONbits.TMR0ON = 1;
                while(INTCONbits.TMR0IF == 0);
                T0CONbits.TMR0ON = 0;
                INTCONbits.TMR0IF = 0;
            }
            break;
        case 'b': //493.88 Hz
            for(int i=0; i<=988; i++){
                if(PORTDbits.RD0 == 0){
                    PORTDbits.RD0 = 1;
                }else if(PORTDbits.RD0 == 1){
                    PORTDbits.RD0 = 0;
                }
                TMR0_WriteTimer(64523); // T = 2025 us -> T/2 = 1012 us
                T0CONbits.TMR0ON = 1;
                while(INTCONbits.TMR0IF == 0);
                T0CONbits.TMR0ON = 0;
                INTCONbits.TMR0IF = 0;
            }
            break;
        case 'A': //466.16 Hz
            for(int i=0; i<=932; i++){
                if(PORTDbits.RD0 == 0){
                    PORTDbits.RD0 = 1;
                }else if(PORTDbits.RD0 == 1){
                    PORTDbits.RD0 = 0;
                }
                TMR0_WriteTimer(64462); // T = 2145 us -> T/2 = 1073 us
                T0CONbits.TMR0ON = 1;
                while(INTCONbits.TMR0IF == 0);
                T0CONbits.TMR0ON = 0;
                INTCONbits.TMR0IF = 0;
            }
            break;
        // ...
        default: // case 'c' -> 261.63 Hz
            for(int i=0; i<=523; i++){
                if(PORTDbits.RD0 == 0){
                    PORTDbits.RD0 = 1;
                }else if(PORTDbits.RD0 == 1){
                    PORTDbits.RD0 = 0;
                }
                TMR0_WriteTimer(63624); // T = 3822 us -> T/2 = 1911 us
                T0CONbits.TMR0ON = 1;
                while(INTCONbits.TMR0IF == 0);
                T0CONbits.TMR0ON = 0;
                INTCONbits.TMR0IF = 0;
            }            
            break;
    }
 */
