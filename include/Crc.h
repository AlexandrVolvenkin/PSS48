#ifndef CRC_H_INCLUDED
#define CRC_H_INCLUDED


//-----------------------------------------------------------------------------
// crc16 constants.
//-----------------------------------------------------------------------------
#define START_VAL_CRC16 0xFFFF;
#define CRC16_LENGTH 2;
//-----------------------------------------------------------------------------


unsigned short usCrcSummTwoByteCalculation(unsigned char *puiSourse, unsigned int nuiNbyte);
int iCrcSummTwoByteCompare(unsigned char *puiSourse, unsigned int nuiNbyte);
uint8_t usCrcSummOneByteCalculation(
    uint8_t *puiSourse,
    uint16_t nuiNbyte);
int iCrcSummOneByteCompare(unsigned char *puiSourse, unsigned int nuiNbyte);
//unsigned short usCrc16(unsigned char *puiSourse, unsigned short uiLength);
int iCrc16Check(unsigned char *puiSourse, unsigned short uiLength);
uint16_t usCrc16(const unsigned char *puiSourse, uint16_t uiLength);

#endif // CRC_H_INCLUDED
