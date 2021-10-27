/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC18F46K40
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

/*
                         Main application

 */
volatile int estados=0;
volatile bool funciona=0;
volatile bool error_num = 0;
volatile uint8_t entrega[7];
volatile uint16_t adc =0;
volatile bool bandera=0;
volatile bool TengoADC=0;

void ADC_Trabajando(void){
    
    adc=ADCC_GetConversionResult();
    IO_RD5_Toggle();
    TengoADC=1;
    
}
void main(void)
{
	
	
	
   
    // Initialize the device
    SYSTEM_Initialize();
    ADCC_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
//uint16_t resultado = 0;
//uint16_t adc=0 ;

volatile char pack [5];
volatile int valor;
uint16_t cont_T6PR;

    ADCC_SetADIInterruptHandler(ADC_Trabajando);

 while (1)
    

    {
        
        if(EUSART1_is_rx_ready()){
            switch (estados){
                case 0:
                    IO_RD0_SetLow();
                    entrega[0]=EUSART1_Read();
                    if (entrega[0]=='1'){
                    estados=1;
                    }
                break;
                case 1:
                    entrega[1]=EUSART1_Read();
                    estados=2;
                break;
                case 2:
                    entrega[2]=EUSART1_Read();
                    estados=3;
                break;
                case 3:
                    entrega[3]=EUSART1_Read();
                    estados=4;
                break;
                case 4:
                    entrega[4]=EUSART1_Read();
                    estados=5;
                break;
                case 5:
                    entrega[5]=EUSART1_Read();
                    estados=6;
                break;
                case 6:
                    entrega[6]=EUSART1_Read();
                    if (entrega[6]=='1'){
                        funciona=1;
                        IO_RD0_SetHigh();
                    }else{
                        error_num=1;
                    }
                    estados=0;
                break;		
            }
            
        }
        /*if(EUSART1_is_tx_ready()){
            
            EUSART1_Write(entrega[0]);
            EUSART1_Write(entrega[1] );
            EUSART1_Write(entrega[2] );
            EUSART1_Write(entrega[3] );
            EUSART1_Write(entrega[4] );
            EUSART1_Write(entrega[5] );
            EUSART1_Write(entrega[6] );
            EUSART1_Write(0x0D);
            EUSART1_Write('\n');
            //bandera=0;
            
         }*/
        
        
        
        if(funciona == 1){
            funciona=0;
            valor=(entrega[1]-'0')*10000+(entrega[2]-'0')*1000+(entrega[3]-'0')*100+(entrega[4]-'0')*10+(entrega[5]-'0')*1;
            //EUSART1_Write(valor);
        
        if(valor>=50 && valor<=4096){
            T6CON = 0xF0;
            cont_T6PR = valor/16;
        }
        if(valor>=4097 && valor<=8193){
            T6CON = 0xF1;
            cont_T6PR = valor/32;
        }
        if(valor>=4098 && valor<=12288){
            T6CON = 0xF2;
            cont_T6PR = valor/48;
        }
        if(valor>=4099 && valor<=16384){
            T6CON = 0xF3;
            cont_T6PR = valor/64;
        }
        if(valor>=4100 && valor<=20480){
            T6CON = 0xF4;
            cont_T6PR = valor/80;
        }
        if(valor>=20481 && valor<=24576){
            T6CON = 0xF5;
            cont_T6PR = valor/96;
        }
        if(valor>=24577 && valor<=28672){
            T6CON = 0xF6;
            cont_T6PR = valor/112;
        }
        if(valor>=28673 && valor<=32768){
            T6CON = 0xF7;
            cont_T6PR = valor/128;
            IO_RD1_SetHigh();
        }
        if(valor>=32769 && valor<=36864){
            T6CON = 0xF8;
            cont_T6PR = valor/144;
        }
        if(valor>=36865 && valor<=40960){
            T6CON = 0xF9;
            cont_T6PR = valor/160;
        }
        if(valor>=40961 && valor<=45056){
            T6CON = 0xFA;
            cont_T6PR = valor/176;
        }
        if(valor>=45057 && valor<=49152){
            T6CON = 0xFB;
            cont_T6PR = valor/192;
        }
        if(valor>=49153 && valor<=52000){
            T6CON = 0xFC;
            cont_T6PR = valor/208;
        }
            T6PR=cont_T6PR;
        }
        /*if(TMR6_HasOverflowOccured()){
            IO_RD5_Toggle();
        }*/
        if(TengoADC==1){
            //resultado = ADCC_GetConversionResult();
            //adc=valor;
            TengoADC=0;
            pack[4]= (adc%10);
            adc=(adc/10); 
            pack[3]= (adc%10);
            adc=(adc/10);               
            pack[2] = (adc%10);
            adc=(adc/10);
            pack[1]=(adc%10);
            adc=(adc/10);
            pack[0]=(adc%10);
                        
            bandera=1;
            
        }
        
        if(bandera==1){
            
            EUSART1_Write(pack[0] +'0');
            EUSART1_Write(pack[1] +'0');
            EUSART1_Write(pack[2] +'0');
            EUSART1_Write(pack[3] +'0');
            EUSART1_Write(pack[4] +'0');
            EUSART1_Write(0x0D);
            EUSART1_Write('\n');
            bandera=0;
            
        }
        
 
 }   
 }

