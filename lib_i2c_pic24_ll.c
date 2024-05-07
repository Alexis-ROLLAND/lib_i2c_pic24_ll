/**
 * @file    lib_i2c_pic24_ll.c
 * @author 	Alexis ROLLAND
 * @date	2022-03
 * @brief 	Low level library for I2C / PIC24 (PIC24FJ128GA010 fully tested)
 *  
 *
 */


#include "lib_i2c_pic24_ll.h" // Inclusion du fichier .h  renommé

/* Directives de compilation - Macros		*/


/* Déclarations des variables globales 	*/



/*	Implémentation du code */
i2c_err_t   i2c_init(i2c_id_t i2c_id, i2c_config_t* pI2cCFG, i2c_desc_t *pI2c)
{
    uint16_t    tmpReg;
    
    switch(i2c_id){
        case _I2C1:
            pI2c->pI2CxBRG = (uint16_t*)&I2C1BRG;
            pI2c->pI2CxCON = (uint16_t*)&I2C1CON;
            pI2c->pI2CxSTAT = (uint16_t*)&I2C1STAT;
            pI2c->pI2CxTRN = (uint16_t*)&I2C1TRN;
            pI2c->pI2CxRCV = (uint16_t*)&I2C1RCV;
            break;
        case _I2C2:
            pI2c->pI2CxBRG = (uint16_t*)&I2C2BRG;
            pI2c->pI2CxCON = (uint16_t*)&I2C2CON;
            pI2c->pI2CxSTAT = (uint16_t*)&I2C2STAT;
            pI2c->pI2CxTRN = (uint16_t*)&I2C2TRN;
            pI2c->pI2CxRCV = (uint16_t*)&I2C2RCV;
            break;
        default:
            return I2C_UNKNOWN_MODULE;
            break;
    }
    
    pI2c->i2cID = i2c_id;
    
    // Configuration effective
    //------------------------------------------
    // I2CBRG
    *(pI2c->pI2CxBRG) = pI2cCFG->i2cBRG_value;
    
    //------------------------------------------
    // I2CCON
    tmpReg = 0x0000;
    
    // I2CEN
    tmpReg |= I2CEN_MASK;
    
    *(pI2c->pI2CxCON) = tmpReg;
    
    //------------------------------------------
    // I2CSTAT
    tmpReg = 0x0000;
    
    *(pI2c->pI2CxSTAT) = tmpReg;
    //------------------------------------------
    return I2C_OK;
}
//----------------------------------------------------------------------------
i2c_err_t   i2c_write(i2c_desc_t *pi2c, uint8_t i2c_Addr,const uint8_t *pByte,uint8_t NbBytes){
    i2c_err_t   Res;
    uint8_t     i;
    
    Res = I2C_Start(pi2c);
    if (Res != I2C_OK) return Res;
    
    // Emission adresse en écriture
    Res = I2C_PutByte(pi2c, ((i2c_Addr<<1) & 0xFE));
    if (Res != I2C_OK)
        {
        I2C_Stop(pi2c);
        return I2C_NO_ACK;
    }
    
    for (i=0;i<NbBytes;i++)
    {
        Res = I2C_PutByte(pi2c, pByte[i]);
        if (Res != I2C_OK)
            {
            I2C_Stop(pi2c);
            return I2C_NO_ACK;
        }
    }
    I2C_Stop(pi2c);
    return I2C_OK;
    
    
}
//----------------------------------------------------------------------------
i2c_err_t   i2c_read(i2c_desc_t *pi2c, uint8_t i2c_Addr,uint8_t *pByte,uint8_t NbBytes){
    i2c_err_t   Res;
    uint8_t     Index;
    
    Res = I2C_Start(pi2c);
    if (Res != I2C_OK) return Res;
    
    Res = I2C_PutByte(pi2c, ((i2c_Addr<<1) | 0x01));
    if (Res != I2C_OK)
        {
        I2C_Stop(pi2c);
        return I2C_NO_ACK;
    }

    Index = 0;
    while(Index < (NbBytes - 1))
        {
        Res = I2C_GetByte(pi2c, &pByte[Index],I2C_SET_ACK);
        Index++;
        if (Res != I2C_OK)
            {
            I2C_Stop(pi2c);
            return Res;  // Réception ACK ?
            }
        }
    
    Res = I2C_GetByte(pi2c,&pByte[Index],I2C_SET_NO_ACK);    // Dernier octet lu sans ACQ 
    if (Res != I2C_OK)
    {
        I2C_Stop(pi2c);
        return Res;  // Réception ACK ?
    }

    I2C_Stop(pi2c);
    
    return I2C_OK;
}
//----------------------------------------------------------------------------
i2c_err_t  i2c_write_then_read(i2c_desc_t *pi2c, uint8_t i2c_Addr,uint8_t *pByteWR,uint8_t NbBytes2WR,uint8_t *pByteRD,uint8_t NbBytes2RD){
    i2c_err_t   Res;    
    uint8_t     Index;

    Res = I2C_Start(pi2c);
    if (Res != I2C_OK) return Res;
    
    // Emission adresse en écriture
    Res = I2C_PutByte(pi2c, ((i2c_Addr<<1) & 0xFE));
    if (Res != I2C_OK)
        {
        I2C_Stop(pi2c);
        return I2C_NO_ACK;
        }
    
    for (Index=0;Index<NbBytes2WR;Index++)
    {
        Res = I2C_PutByte(pi2c, pByteWR[Index]);
        if (Res != I2C_OK)
            {
            I2C_Stop(pi2c);
            return I2C_NO_ACK;
            }
    }
    
    I2C_ReStart(pi2c);    
    
    Res = I2C_PutByte(pi2c, ((i2c_Addr << 1) | 0x01));
    if (Res != I2C_OK)
        {
        I2C_Stop(pi2c);
        return I2C_NO_ACK;
        }

    Index = 0;
    while(Index < (NbBytes2RD - 1))
        {
        Res = I2C_GetByte(pi2c, &pByteRD[Index],I2C_SET_ACK);
        Index++;
        if (Res != I2C_OK)
            {
            I2C_Stop(pi2c);
            return Res;  // Réception ACK ?
            }
        }
    
    Res = I2C_GetByte(pi2c,&pByteRD[Index],I2C_SET_NO_ACK);    // Dernier octet lu sans ACQ (cf doc))
    if (Res != I2C_OK)
        {
        I2C_Stop(pi2c);
        return Res;  // Réception ACK ?
        }

    I2C_Stop(pi2c);
    
    return I2C_OK;
}
//----------------------------------------------------------------------------
i2c_err_t  I2C_PutByte(i2c_desc_t *pi2c, uint8_t Byte){
    *(pi2c->pI2CxTRN) = Byte;   // Chargement registre d'émission
    switch (pi2c->i2cID)
    {
        case _I2C1:
            while(!IFS1bits.MI2C1IF);   // Attente fin émission
                       
            if (I2C1STATbits.ACKSTAT != 0)
                {
                I2C_Stop(pi2c);
                return I2C_NO_ACK;
                }
            IFS1bits.MI2C1IF = 0;       // Raz Flag
            break;
        case _I2C2:
            while(!IFS3bits.MI2C2IF);   // Attente fin émission
                      
            if (I2C2STATbits.ACKSTAT != 0)
                {
                I2C_Stop(pi2c);
                return I2C_NO_ACK;
                }
             IFS3bits.MI2C2IF = 0;       // Raz Flag
            break;
        
        
        
        default: return I2C_UNKNOWN_MODULE;
    }
    return I2C_OK;
    
}
//----------------------------------------------------------------------------
i2c_err_t  I2C_GetByte(i2c_desc_t *pi2c, uint8_t *pByte, set_ack_t EtatACK){
    switch (pi2c->i2cID)
    {
        case _I2C1:
            I2C1CONbits.ACKDT = EtatACK;    // type d'ACK à générer
            
            I2C1CONbits.RCEN = 1;           // Lancer lecture
            while(!IFS1bits.MI2C1IF);       // Attente fin réception
                        
            *pByte = *(pi2c->pI2CxRCV);     // Lecture octet
            while(!IFS1bits.MI2C1IF);               
            IFS1bits.MI2C1IF = 0;           // Raz Flag
            
            I2C1CONbits.ACKEN = 1;          // Lancement génération ACK/NACK
            while(!IFS1bits.MI2C1IF);               
            IFS1bits.MI2C1IF = 0;           // Raz Flag
                        
            break;
        case _I2C2:
            I2C2CONbits.ACKDT = EtatACK;    // type d'ACK à générer
            
            I2C2CONbits.RCEN = 1;           // Lancer lecture
            while(!IFS3bits.MI2C2IF);       // Attente fin réception
                        
            *pByte = *(pi2c->pI2CxRCV);     // Lecture octet
            while(!IFS3bits.MI2C2IF);               
            IFS3bits.MI2C2IF = 0;           // Raz Flag
            
            I2C2CONbits.ACKEN = 1;          // Lancement génération ACK/NACK
            while(!IFS3bits.MI2C2IF);               
            IFS3bits.MI2C2IF = 0;           // Raz Flag
            break;        
        default: break;
    }
    return I2C_OK;
}
//----------------------------------------------------------------------------
i2c_err_t   I2C_Start(i2c_desc_t *pi2c){
    switch (pi2c->i2cID)
    {
        case _I2C1:
            I2C1CONbits.SEN = 1;
            while(!IFS1bits.MI2C1IF);   // Attente fin génération start
            IFS1bits.MI2C1IF = 0;       // Raz Flag
            break;
        case _I2C2:
            I2C2CONbits.SEN = 1;
            while(!IFS3bits.MI2C2IF);   // Attente fin génération start
            IFS3bits.MI2C2IF = 0;       // Raz Flag
            break;
               
        default: return I2C_UNKNOWN_MODULE;
    }
    return I2C_OK;
}
        
i2c_err_t   I2C_Stop(i2c_desc_t *pi2c){
    switch (pi2c->i2cID)
    {
        case _I2C1:
            I2C1CONbits.PEN = 1;
            while(!IFS1bits.MI2C1IF);   // Attente fin génération start
            IFS1bits.MI2C1IF = 0;       // Raz Flag
            break;
        case _I2C2:
            I2C2CONbits.PEN = 1;
            while(!IFS3bits.MI2C2IF);   // Attente fin génération start
            IFS3bits.MI2C2IF = 0;       // Raz Flag
            break;
               
        default: return I2C_UNKNOWN_MODULE;
    }
    return I2C_OK;
}

i2c_err_t   I2C_ReStart(i2c_desc_t *pi2c){
    switch (pi2c->i2cID)
    {
        case _I2C1:
            I2C1CONbits.RSEN = 1;
            while(!IFS1bits.MI2C1IF);   // Attente fin génération start
            IFS1bits.MI2C1IF = 0;       // Raz Flag
            break;
        case _I2C2:
            I2C2CONbits.RSEN = 1;
            while(!IFS3bits.MI2C2IF);   // Attente fin génération start
            IFS3bits.MI2C2IF = 0;       // Raz Flag
            break;
               
        default: return I2C_UNKNOWN_MODULE;
    }
    return I2C_OK;
}
//----------------------------------------------------------------------------
