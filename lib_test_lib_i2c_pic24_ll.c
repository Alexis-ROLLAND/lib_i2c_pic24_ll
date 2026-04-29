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
#if (CURRENT_TEST == TEST_BACKLIGHT)
i2c_err_t   Res;
uint8_t Buffer[2];

void Initialiser(void){
    i2c_config_t    i2cCfg;
    
    // Leds
    TRISA &= 0xFF00;
    LATA = 0;
            
    // I2C low level config
    // Configurer RB8 et RB9 en entrée (requis pour I2C)
    TRISBbits.TRISB8 = 1;  // SCL1 en entrée
    TRISBbits.TRISB9 = 1;  // SDA1 en entrée
    
    // Désactiver les fonctions analogiques sur ces pins (si applicable)
    ANSBbits.ANSB9 = 0;    // RB9 en digital
    
    i2cCfg.i2cBRG_value = KHZ100_MHZ4;
    i2c_init(I2C_MODULE,&i2cCfg,&myI2C);
    
    
    
    // BlackLight Config
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
    
    Buffer[0] = RED_REG;
    Buffer[1] = 0x00;
}

void    main_Task(void){
    __delay_ms(50);
    LATA=Buffer[1];
        
    Res = i2c_write(&myI2C, RGBLED_ADDR, Buffer, 2);
    if (Res != I2C_OK) error_handler();
    Buffer[1]++;
    
    
}

#endif

#if (CURRENT_TEST == TEST_TSL2561)
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
#endif



void    error_handler(void)
{
    LATAbits.LATA0 = 0;
    while(1){
        LATAbits.LATA0 = ~LATAbits.LATA0;
        __delay_ms(50);
    }
}
