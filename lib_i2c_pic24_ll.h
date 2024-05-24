/**
 * @file    lib_i2c_pic24_ll.h 
 * @author 	Alexis ROLLAND
 * @date	2022/02
 * @brief 	Low level library for I2C / PIC24 (Multi Target) - common Header file
 *          V3 - 05/2024 
 *          Supported Targets are (name and support status) : 
 *                  PIC24FJ128GFA010 - Fully tested
 *                  PIC24FV16KM202 - currently being tested
 */

#ifndef	__LIB_I2C_PIC24_LL_H__
#define	__LIB_I2C_PIC24_LL_H__
#include <xc.h>

#include    "lib_i2c_pic24_ll_common_types.h"

/**
 * Target specific includes
 */
#if defined(__PIC24FJ128GA010__) 
    #include    "lib_i2c_pic24_ll_GA0xx.h"
#else
    #error "Specific target not supported yet."
#endif




/**
 * @brief   Initializes the I2C module     
 * 
 * @param       i2c_id  ID of the target I2C module (_I2C1 or _I2C2)
 * @param[in]   pI2cCFG Address of the fully completed i2c_config_t structure
 * @param[out]  pI2c    Address of the I2c module descriptor (fully completed by the function)  
 * 
 * @return  I2C_OK  on success
 * @return  I2C_UNKNOWN_MODULE if I2C module is unknown   
 */
i2c_err_t   i2c_init(i2c_id_t i2c_id, i2c_config_t* pI2cCFG, i2c_desc_t *pI2c);
    
  /**
 * @brief       Sends NbBytes on the I2Cbus
 * 
 * @param[in]   pi2c        Address of an initialized I2C descriptor
 * @param       i2c_Addr    I2C address of the slave (7 bits)
 * @param[in]   pByte       Address of the Tx buffer 
 * @param       NbBytes     Number of Bytes to send	
 * 
 * @return      I2C_OK on success
 * @return      I2C_NO_ACK on no ack error
 * @return      I2C_UNKNOWN_MODULE if I2C module is unknown
 *  
 * @attention   7bits address must be passed 
 *
 */
i2c_err_t   i2c_write(i2c_desc_t *pi2c, uint8_t i2c_Addr,const uint8_t *pByte,uint8_t NbBytes);
 
 /**
 * @brief       Reads NbBytes on the I2Cbus
 * 
 * @param[in]   pi2c        Address of an initialized I2C descriptor
 * @param       i2c_Addr    I2C address of the slave (7 bits)
 * @param[out]  pByte       Address of the rx buffer 
 * @param       NbBytes     Number of Bytes to read
 * 
 * @return      I2C_OK on success
 * @return      I2C_NO_ACK on no ack error
 * @return      I2C_UNKNOWN_MODULE if I2C module is unknown
 *  
 * @attention   7bits address must be passed 
 *
 */
i2c_err_t   i2c_read(i2c_desc_t *pi2c, uint8_t i2c_Addr,uint8_t *pByte,uint8_t NbBytes);
 
 /**
 * @brief       Write sequence, followed by a read sequence. 
 *              Restart condition is issued between the sequences.  
 * 
 * @param[in]   pi2c        Address of an initialized I2C descriptor
 * @param       i2c_Addr    I2C address of the slave (7 bits)
 * @param[in]   pByteWR     Address of the Tx buffer 
 * @param       NbBytes2WR  Number of Bytes to Write
 * @param[out]  pByteRD     Address of the Rx buffer 
 * @param       NbBytes2RD  Number of Bytes to Read
 * 
 * @return      I2C_OK on success
 * @return      I2C_NO_ACK on no ack error  
 *  
 * @attention   7bits address must be passed 
 *
 */
 i2c_err_t  i2c_write_then_read(i2c_desc_t *pi2c, uint8_t i2c_Addr,const uint8_t *pByteWR,uint8_t NbBytes2WR,uint8_t *pByteRD,uint8_t NbBytes2RD);
 
 //-----------------------------------------------------------------------------
 // The following functions are low level functions, not intended to be used 
 // as "public" API functions.
 //-----------------------------------------------------------------------------
 
 /**
 * @brief       Reads a raw byte from the bus.
 * 
 * @param[in]   pi2c        Address of an initialized I2C descriptor
 * @param[out]  pByte       Address where to put the received byte value	
 * @param       EtatACK     ACK level to put on th line after the byte reception  
 * 
 * @return      I2C_OK 
 */
 i2c_err_t  I2C_GetByte(i2c_desc_t *pi2c, uint8_t *pByte, set_ack_t EtatACK);
 
 /**
 * @brief       Raw sending of a byte on the bus.
 * 
 * @param[in]   pi2c        Address of an initialized I2C descriptor
 * @param       Byte        Byte to send	
 * 
 * @return      I2C_OK on success
 * @return      I2C_NO_ACK on no ack error
 */
 i2c_err_t  I2C_PutByte(i2c_desc_t *pi2c, uint8_t Byte);

 //-----------------------------------------------------------------------------
 /**
 * @brief       Very Low level I2C functions, used to generate START, STOP and RESTART conditions
 * 
 * @param[in]	pi2c    Address of an initialized I2C descriptor 
 * 
 * @return      I2C_OK
 */
i2c_err_t   I2C_Start(const i2c_desc_t *pi2c);
i2c_err_t   I2C_Stop(const i2c_desc_t *pi2c);
i2c_err_t   I2C_ReStart(const i2c_desc_t *pi2c);





#endif


