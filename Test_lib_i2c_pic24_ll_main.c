/**
 * @file     
 * @author 	Alexis ROLLAND
 * @date	2024/05
 * @brief 	
 */

#include "lib_test_lib_i2c_pic24_ll.h"   // Inclusion du fichier .h "Applicatif" renommé

/**
 * Insérer Ici les bits de configuration pour le MCU 						  
 * Copier / Coller depuis le fichier Config_Pic24.txt					  
 */
/*--------------------------------------------------------------------------*/
/* PIC24FJ128GA010															*/
/*--------------------------------------------------------------------------*/
#pragma config POSCMOD = HS         // Primary Oscillator Select (EC, XT, HS, NONE)
#pragma config OSCIOFNC = ON        // Primary Oscillator Output Function (ON, OFF)
#pragma config FCKSM = CSDCMD       // Clock Switching and Monitor (CSECME, CSECMD, CSDCMD)
#pragma config FNOSC = PRI          // Oscillator Select (FRC, FRCPLL, PRI, PRIPLL, SOSC, LPRC, FRCDIV)
#pragma config IESO = OFF           // Internal External Switch Over Mode (ON, OFF)
#pragma config WDTPS = PS256        // Watchdog Timer Postscaler (PS1, PS2, PS4, PS8,..., PS32768)
#pragma config FWPSA = PR32         // WDT Prescaler (PR32, PR128)
#pragma config WINDIS = OFF         // Watchdog Timer Window (ON, OFF)
#pragma config FWDTEN = OFF         // Watchdog Timer Enable (ON, OFF)
#pragma config ICS = PGx2           // Comm Channel Select (PGx1, PGx2)
#pragma config BKBUG = OFF          // Background Debug (ON, OFF)
#pragma config GWRP = OFF           // General Code Segment Write Protect (ON, OFF)
#pragma config GCP = OFF            // General Code Segment Code Protect (ON, OFF)
#pragma config JTAGEN = OFF         // JTAG Port Enable (ON, OFF)
//----------------------------------------------------------------------------
/* Directives de compilation - Macros		*/



/* Déclarations des variables globales 	*/
extern i2c_desc_t  myI2C;

uint8_t Buffer[2];


/* Programme Principal			*/
#ifdef TEST_BACKLIGHT
int main(void)
{
// Variables locales au main
    i2c_err_t   Res;


    Initialiser();		// Appel fonction d'initialisation

    // Init RGB Backlight
    Buffer[0] = 0x00;
    Buffer[1] = 0x00;
    Res = i2c_write(&myI2C, RGBLED_ADDR, Buffer, 2);
    if (Res != I2C_OK) error_handler();
    
    Buffer[0] = 0x01;
    Buffer[1] = 0x00;
    Res = i2c_write(&myI2C, RGBLED_ADDR, Buffer, 2);
    if (Res != I2C_OK) error_handler();
   
    Buffer[0] = 0x08;
    Buffer[1] = 0xAA;
    Res = i2c_write(&myI2C, RGBLED_ADDR, Buffer, 2);
    if (Res != I2C_OK) error_handler();
    
    Buffer[0] = BLUE_REG;
    Buffer[1] = 0x00;
    while(1)
    {
        __delay_ms(100);
        LATA=Buffer[1];
        
       Res = i2c_write(&myI2C, RGBLED_ADDR, Buffer, 2);
       if (Res != I2C_OK) error_handler();
            Buffer[1]++;

        
    }
}					
#endif

#ifdef  TEST_TSL2561
int main(void)
{
// Variables locales au main
    i2c_err_t   Res;

    Initialiser();		// Appel fonction d'initialisation

    Buffer[0] = 0x80;
    Buffer[1] = 0x03;
    Res = i2c_write(&myI2C, TSL2561_ADDR, Buffer, 2);
    if (Res != I2C_OK) error_handler();
    
    while(1)
    {
        __delay_ms(2000);
        Buffer[0] = 0x80;
        Res = i2c_write_then_read(&myI2C, TSL2561_ADDR,Buffer, 1,&Buffer[1],1);
        if (Res != I2C_OK) error_handler();
        
        __delay_ms(2000);
        Buffer[0] = 0x80;
        Buffer[1] = 0x00;
        Res = i2c_write(&myI2C, TSL2561_ADDR, Buffer, 2);
        if (Res != I2C_OK) error_handler();
        
        __delay_ms(2000);
        Buffer[0] = 0x80;
        Res = i2c_write_then_read(&myI2C, TSL2561_ADDR,Buffer, 1,&Buffer[1],1);
        if (Res != I2C_OK) error_handler();
        
        __delay_ms(2000);
        Buffer[0] = 0x80;
        Buffer[1] = 0x03;
        Res = i2c_write(&myI2C, TSL2561_ADDR, Buffer, 2);
        if (Res != I2C_OK) error_handler();
        
        LATAbits.LATA0 = ~LATAbits.LATA0;
    }
}		

#endif


