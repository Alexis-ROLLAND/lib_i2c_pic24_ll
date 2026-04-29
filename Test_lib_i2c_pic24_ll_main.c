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

#if defined(__PIC24FJ128GA010__) 
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
#endif


#if defined(__PIC24FJ256GA702__)
/*--------------------------------------------------------------------------*/
/* PIC24FJ256GA702  - 28 pin 3,3V device															*/
/*--------------------------------------------------------------------------*/
#pragma config BWRP = OFF           // Boot Segment Write-Protect bit
#pragma config BSS = DISABLED       // Boot Segment Code-Protect Level bits
#pragma config BSEN = OFF           // Boot Segment Control bit
#pragma config GWRP = OFF           // General Segment Write-Protect bit
#pragma config GSS = DISABLED       // General Segment Code-Protect Level bits
#pragma config CWRP = OFF           // Configuration Segment Write-Protect bit
#pragma config CSS = DISABLED       // Configuration Segment Code-Protect Level bits
#pragma config AIVTDIS = OFF        // Alternate Interrupt Vector Table bit
#pragma config FBSLIM_BSLIM = BSLIM // Boot Segment Flash Page Address Limit bits
#pragma config FNOSC = FRC          // Oscillator Select (FRC, FRCPLL, PRI, PRIPLL, SOSC, LPRC, FRCDIV)
#pragma config PLLMODE = DISABLED   // PLL Mode Selection
#pragma config IESO = OFF           // Internal External Switch Over Mode (ON, OFF)
#pragma config POSCMD = NONE        // Primary Oscillator Select (EC, XT, HS, NONE)
#pragma config OSCIOFCN = ON        // OSC2 Pin Function bit (ON, OFF)
#pragma config SOSCSEL = ON         // SOSC Power Selection Configuration bits
#pragma config PLLSS = PLL_FRC      // PLL Secondary Selection Configuration bit
#pragma config IOL1WAY = OFF        // Peripheral pin select configuration bit
#pragma config FCKSM = CSDCMD       // Clock Switching and Monitor (CSECME, CSECMD, CSDCMD)
#pragma config WDTPS = PS256        // Watchdog Timer Postscaler (PS1, PS2, PS4, PS8,..., PS32768)
#pragma config FWPSA = PR32         // WDT Prescaler (PR32, PR128)
#pragma config FWDTEN = OFF         // Watchdog Timer Enable (ON, OFF)
#pragma config WINDIS = ON          // Watchdog Timer Window (ON, OFF)
#pragma config WDTWIN = WIN50       // Watchdog Timer Window Select bits
#pragma config WDTCMX = LPRC        // WDT MUX Source Select bits
#pragma config WDTCLK = LPRC        // WDT Clock Source Select bits
#pragma config BOREN = OFF          // Brown Out Enable bit
#pragma config LPCFG = OFF          // Low power regulator control
#pragma config DNVPEN = DISABLE     // Downside Voltage Protection Enable bit
#pragma config ICS = PGD2           // Comm Channel Select 
#pragma config JTAGEN = OFF         // JTAG Port Enable (ON, OFF)
#pragma config ALTCMPI = DISABLE    // Alternate Comparator Input Enable bit
#pragma config TMPRPIN = OFF        // Tamper Pin Enable bit
#pragma config SOSCHP = ON          // SOSC High Power Enable bit (valid only when SOSCSEL = 1)
#pragma config ALTI2C1 = ALTI2CEN   // Alternate I2C pin Location /!\
//----------------------------------------------------------------------------
#endif


/* Directives de compilation - Macros		*/



/* Déclarations des variables globales 	*/

/* Programme Principal			*/
#if (CURRENT_TEST == TEST_BACKLIGHT)
int main(void){
    Initialiser();		// Appel fonction d'initialisation

    while(1){
        main_Task();
    }
}					
#endif

#if (CURRENT_TEST == TEST_TSL2561)
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


