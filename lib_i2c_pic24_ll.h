/**
 * @file    lib_i2c_pic24_ll 
 * @author 	Alexis ROLLAND
 * @date	2022/02
 * @brief 	Low level library for I2C / PIC24 (PIC24FJ128GA010 fully tested)
 *  
 *
 */

#ifndef	__LIB_I2C_PIC24_LL_H__
#define	__LIB_I2C_PIC24_LL_H__
#include <xc.h>


// Defines for classical BRG Values : 
#define KHZ100_MHZ16    157     // 100 kHz with Osc 32 MHz 
#define KHZ100_MHZ8     78      // 100 kHz with Osc 16 MHz 
#define KHZ100_MHZ4     39      // 100 kHz with Osc 8 MHz
#define KHZ400_MHZ16    37      // 400 kHz with Osc 32 MHz 
#define KHZ400_MHZ8     18      // 400 kHz with Osc 16 MHz 
#define KHZ400_MHZ4     9       // 400 kHz with Osc 8 MHz
#define KHZ400_MHZ2     4       // 400 kHz with Osc 4 MHz

// Masks for I2CxCON register
#define I2CEN_MASK  (0x0001 << 15)

typedef enum    {   _I2C1,      /**< Value for I2C1 module */
                    _I2C2       /**< Value for I2C2 module */
                    } i2c_id_t;
                
typedef enum    {   I2C_SET_ACK = 0,
                    I2C_SET_NO_ACK = 1
                    } set_ack_t;
                    
typedef enum    {   I2C_OK,                 /**< Succes value                   */
                    I2C_ERROR,              /**< Non Specific Error             */
                    I2C_UNKNOWN_MODULE,     /**< The I2C Module ID is unknown   */
                    I2C_NO_ACK,             /**< No ack received from slave     */
                    I2C_BAD_ADDRESS         /**< Address is not I2C             */
                    } i2c_err_t; 
                    
/** Type i2c_config_t
 * 
 * 
 */
typedef struct{ uint16_t    i2cBRG_value;
                
                
    } i2c_config_t;
                    
/** Type i2c_desc_t
 * 
 * 
 */
typedef struct {
    i2c_id_t    i2cID;
    uint16_t    *pI2CxBRG;
    uint16_t    *pI2CxCON;
    uint16_t    *pI2CxSTAT;
    uint16_t    *pI2CxTRN;
    uint16_t    *pI2CxRCV;
    } i2c_desc_t;            

                            
/**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
i2c_err_t   i2c_init(i2c_id_t i2c_id, i2c_config_t* pI2cCFG, i2c_desc_t *pI2c);
    
 
 /**
 * @brief   Send NbBytes on the I2Cbus
 * 
 * @param[in]   Address of an initialized I2C descriptor
 * @param[in]   I2C address of the slave
 * @param[in]   Address of the Tx buffer 
 * @param[in]   Number of Bytes to send	
 * 
 * @return      I2C_OK, I2C_NO_ACK or I2C_UNKNOWN_MODULE 
 * 
 * @attention   7bits address must be passed 
 *
 */
i2c_err_t   i2c_write(i2c_desc_t *pi2c, uint8_t i2c_Addr,uint8_t *pByte,uint8_t NbBytes);
 
 /**
 * @brief       Read NbBytes on the I2Cbus
 * 
 * @param[in]   Address of an initialized I2C descriptor
 * @param[in]   I2C address of the slave
 * @param[in]   Address of the rx buffer 
 * @param[in]   Number of Bytes to read
 * 
 * @return      I2C_OK, I2C_NO_ACK or I2C_UNKNOWN_MODULE 
 * 
 * @attention   7bits address must be passed 
 *
 */
i2c_err_t   i2c_read(i2c_desc_t *pi2c, uint8_t i2c_Addr,uint8_t *pByte,uint8_t NbBytes);
 
 
  /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 * 
 * @attention   7bits address must be passed 
 *
 */
 i2c_err_t  i2c_write_then_read(i2c_desc_t *pi2c, uint8_t i2c_Addr,uint8_t *pByteWR,uint8_t NbBytes2WR,uint8_t *pByteRD,uint8_t NbBytes2RD);
 
 //-----------------------------------------------------------------------------
  /**
 * @brief  
 * 
 * @param	
 * 
 * @return   
 *
 */
 i2c_err_t  I2C_GetByte(i2c_desc_t *pi2c, uint8_t *pByte, set_ack_t EtatACK);
 
 /**
 * @brief       Raw sending of a byte on the bus
 * 
 * @param[in]   Address of an initialized I2C descriptor
 * @param[in]   Byte to send	
 * 
 * @return      I2C_OK, I2C_UNKNOWN_MODULE or I2C_NO_ACK
 *
 */
 i2c_err_t  I2C_PutByte(i2c_desc_t *pi2c, uint8_t Byte);

 //-----------------------------------------------------------------------------
 /**
 * @brief   Very Low level I2C functions, used to generate START, STOP and RESTART conditions
 * 
 * @param	Address of an initialized I2C descriptor 
 * 
 * @return  I2C_OK on success, I2C_UNKNOWN_MODULE otherwise 
 */
i2c_err_t   I2C_Start(i2c_desc_t *pi2c);
i2c_err_t   I2C_Stop(i2c_desc_t *pi2c);
i2c_err_t   I2C_ReStart(i2c_desc_t *pi2c);





#endif


