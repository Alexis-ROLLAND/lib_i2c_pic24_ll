/**
 * @file Template_lib_Appli_C.c 
 * @author 	Alexis ROLLAND
 * @date	2021-12-30
 * @brief 	Template for PIC24 main app
 *  
 *
 */


#include "lib_test_lib_i2c_pic24_ll.h" // Inclusion du fichier .h "Applicatif" renommé

/* Directives de compilation - Macros		*/


/* Déclarations des variables globales 	*/
i2c_desc_t  myI2C;

/*	Implémentation du code */
void Initialiser(void)
{
    i2c_config_t    i2cCfg;
    
    // Leds
    TRISA &= 0xFF00;
    LATA = 0;
            
    // I2C
    i2cCfg.i2cBRG_value = KHZ100_MHZ4;
    
    i2c_init(I2C_MODULE,&i2cCfg,&myI2C);
    
    

}
void    error_handler(void)
{
    LATAbits.LATA0 = 0;
    while(1){
        LATAbits.LATA0 = ~LATAbits.LATA0;
        __delay_ms(50);
    }
}
