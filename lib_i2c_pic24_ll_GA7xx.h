/**
 * @file    lib_i2c_pic24_ll_GA7xx.h 
 * @author 	Alexis ROLLAND
 * @date	2025-12
 * @brief 	Target dependant very low level I2C driver header
 *          Familly : PIC24FJxxxGA7xx
 *          Devices :
 *              PIC24FJ256GA702 -   Fully tested OK
 * 
 *              PIC24FJ64GA705 - Not tested
 *              PIC24FJ128GA705 - Not tested
 *              PIC24FJ256GA705 - Not tested
 * 
 *              PIC24FJ64GA704 - Not tested
 *              PIC24FJ128GA704 - Not tested
 *              PIC24FJ256GA704 - Not tested
 * 
 *              PIC24FJ64GA702 - Not tested
 *              PIC24FJ128GA702 - Not tested
 * 
 * @ATTENTION : Do not forget to set SDA & SCL lines as GPIO inputs
 *              before the i2c_init call.
 *              /!\ SDA line must be configured as digital line (ANS register)
 *              Be carefull at the #pragma config ALTI2C1 = ALTI2CEN  
 */

#ifndef	__LIB_I2C_PIC24_LL_GA7XX_H__
#define	__LIB_I2C_PIC24_LL_GA7XX_H__
#include <xc.h>

#include "lib_i2c_pic24_ll_common_types.h"

/**
 * For PIC24FJ7xx targets thers's no I2CxCON regs
 * but I2CxCONL & I2CxCONH
 * Legacy use is when I2CxCONL is considered as I2CxCON 
 */
#define I2C1CON     I2C1CONL
#define I2C2CON     I2C2CONL

/**
 * Defines for classical BRG Values
 */
#define KHZ100_MHZ16    78     /**<    100 kHz with Osc 32 MHz     */
#define KHZ100_MHZ8     38      /**<    100 kHz with Osc 16 MHz     */ 
#define KHZ100_MHZ4     18      /**<    100 kHz with Osc 8 MHz      */
#define KHZ400_MHZ16    18      /**<    400 kHz with Osc 32 MHz     */
#define KHZ400_MHZ8     8      /**<    400 kHz with Osc 16 MHz     */
#define KHZ400_MHZ4     3       /**<    400 kHz with Osc 8 MHz      */


/** 
 * Masks for I2CxCON registers - Target Specific
 */
#define I2CEN_MASK  (0x0001 << 15)  /**< I2CEN bit  */
#define DISSLW_MASK (0x0001 << 9)   /**< DISLW bit  */
#define ACKDT_MASK  (0x0001 << 5)   /**< ACKDT bit  */
#define ACKEN_MASK  (0x0001 << 4)   /**< ACKEN bit  */
#define RCEN_MASK   (0x0001 << 3)   /**< RCEN bit  */
#define PEN_MASK    (0x0001 << 2)   /**< PEN bit - Stop Condition  */
#define RSEN_MASK   (0x0001 << 1)   /**< RSEN bit - Restart Condition  */
#define SEN_MASK    (0x0001 << 0)   /**< SEN bit - Start Condition  */

/**
 * Masks for I2CxSTAT registers
 */
#define ACKSTAT_MASK    (0x0001 << 15)  /**< ACKSTAT bit    */
/** 
 * Masks for IFSx Registers
 */
#define I2C1IF_MASK (0x0001 << 1)   /**  IFS1[1]   */
#define I2C2IF_MASK (0x0001 << 2)   /**  IFS3[2]   */

/**
 * Few Macros...
 */
#define ClrIFS()    {*(pi2c->pIFSREG) &= ~pi2c->IFS_MASK;}  /**< Clears the IFS bit */
#define WaitIFS()   {while(!(*(pi2c->pIFSREG) & pi2c->IFS_MASK));}  /**< Wait for the IFS bit to be set (end of action) */

#define EnableSlewRateControl {*(pi2c->pI2CxCON) &= ~DISSLW_MASK;}
#define DisableSlewRateControl {*(pi2c->pI2CxCON) |= DISSLW_MASK;}

/** 
 * Type i2c_desc_t 
 */
typedef struct {
    i2c_id_t    i2cID;          /**< ID of the I2C Module (_I2C1 or _I2C2)  */
    regAddr     pI2CxBRG;       /**< Address of the real I2CxBRG register  */
    regAddr     pI2CxCON;       /**< Address of the real I2CxCON register  */
    regAddr     pI2CxSTAT;      /**< Address of the real I2CxSTAT register  */
    regAddr     pI2CxTRN;       /**< Address of the real I2CxTRN register  */
    regAddr     pI2CxRCV;       /**< Address of the real I2CxRCV register  */
    regAddr     pIFSREG;        /**< Address of the real IFS register */
    uint16_t    IFS_MASK;       /**< Mask for the MI2CxIF bit   */
} i2c_desc_t;            
                            

 
 
 
 




#endif  /*  __LIB_I2C_PIC24_LL_GA7XX_H__    */


