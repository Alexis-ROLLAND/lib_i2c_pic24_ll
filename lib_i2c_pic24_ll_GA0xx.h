/**
 * @file    lib_i2c_pic24_ll_GA0xx.h 
 * @author 	Alexis ROLLAND
 * @date	2024-05
 * @brief 	Target dependant very low level I2C driver header
 *          Familly : PIC24FJ128GA01
 *          Devices :
 *              PIC24FJ128GA010 -   Fully tested OK
 *              PIC24FJ96GA010  -   Not tested
 *              PIC24FJ64GA010  -   Not tested
 * 
 *              PIC24FJ128GA008 -   Not tested
 *              PIC24FJ96GA008  -   Not tested
 *              PIC24FJ64GA008  -   Not tested 
 * 
 *              PIC24FJ128GA006 -   Not tested
 *              PIC24FJ96GA006  -   Not tested
 *              PIC24FJ64GA006  -   Not tested             
 */

#ifndef	__LIB_I2C_PIC24_LL_GA0XX_H__
#define	__LIB_I2C_PIC24_LL_GA0XX_H__
#include <xc.h>

#include "lib_i2c_pic24_ll_common_types.h"

/** 
 * Masks for I2CxCON registers - Target Specific
 */
#define I2CEN_MASK  (0x0001 << 15)  /**< I2CEN bit  */
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
                            

 
 
 
 




#endif  /*  __LIB_I2C_PIC24_LL_GA0XX_H__    */


