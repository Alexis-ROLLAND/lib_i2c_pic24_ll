/**
 * @file  
 * @author 	Alexis ROLLAND
 * @date	2021-12-30
 * @brief 	
 *  
 *
 */
#ifndef	__LIB_APP_TEST_IC2_PIC24_H__
#define	__LIB_APP_TEST_IC2_PIC24_H__

#ifndef FCY
#define FCY 4000000UL
#endif

#include <libpic30.h>
#include <xc.h>

#include "lib_i2c_pic24_ll.h"

#define I2C_MODULE  _I2C1


#define TEST_BACKLIGHT
//#define TEST_TSL2561

#ifdef TEST_BACKLIGHT
#define     RGBLED_ADDR     0x62    // I2C (7bits address)
#define     BLUE_REG        0x02
#define     GREEN_REG       0x03
#define     RED_REG         0x04
#endif

#ifdef  TEST_TSL2561
#define TSL2561_ADDR        0x29


#endif



/**
 * @brief Global init function/task 
 * 
 * @param	None
 * 
 * @return  Nothing 
 *
 */
void Initialiser(void);

/**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
void    error_handler(void);


 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 
 /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 
 


#endif



