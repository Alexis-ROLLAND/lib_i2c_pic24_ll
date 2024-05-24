/**
 * @file    lib_i2c_pic24_ll_common_types.h 
 * @author 	Alexis ROLLAND
 * @date	2024-05
 * @brief 	Common types & macros definitions for lib_i2c_pic24_ll
 */

#ifndef	__LIB_I2C_PIC24_LL_COMMON_TYPES_H__
#define	__LIB_I2C_PIC24_LL_COMMON_TYPES_H__
#include <xc.h>

#ifndef REG_ADDR_TYPE
#define REG_ADDR_TYPE
typedef uint16_t*    regAddr;       /**<    Alias to uint16_t*  */
#endif

/**
 * Defines for classical BRG Values
 */
#define KHZ100_MHZ16    157     /**<    100 kHz with Osc 32 MHz     */
#define KHZ100_MHZ8     78      /**<    100 kHz with Osc 16 MHz     */ 
#define KHZ100_MHZ4     39      /**<    100 kHz with Osc 8 MHz      */
#define KHZ400_MHZ16    37      /**<    400 kHz with Osc 32 MHz     */
#define KHZ400_MHZ8     18      /**<    400 kHz with Osc 16 MHz     */
#define KHZ400_MHZ4     9       /**<    400 kHz with Osc 8 MHz      */
#define KHZ400_MHZ2     4       /**<    400 kHz with Osc 4 MHz      */

typedef enum    {   
    _I2C1,      /**< Value for I2C1 module (real I2C or MSSP)   */
    _I2C2       /**< Value for I2C2 module (real I2C or MSSP)   */
} i2c_id_t;
                
typedef enum    {   
    I2C_SET_ACK = 0,        /**< Set ACK after receiving byte */
    I2C_SET_NO_ACK = 1      /**< Set NO ACK after receiving byte */
} set_ack_t;
                    
typedef enum    {   
    I2C_OK,                 /**< Succes value                   */
    I2C_ERROR,              /**< Non Specific Error             */
    I2C_UNKNOWN_MODULE,     /**< The I2C Module ID is unknown   */
    I2C_NO_ACK,             /**< No ack received from slave     */
    I2C_BAD_ADDRESS         /**< Address is not I2C             */
 } i2c_err_t; 
                    
/** 
 * Type i2c_config_t
 */
typedef struct{ 
    uint16_t    i2cBRG_value;   /**< Only BRG value is needed to configure bitrate  */
} i2c_config_t;
                    
        
                            

 
 
 

 





#endif  /*  __LIB_I2C_PIC24_LL_COMMON_TYPES_H__ */


