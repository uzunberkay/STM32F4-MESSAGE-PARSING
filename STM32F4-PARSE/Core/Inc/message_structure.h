/*______________________________________________
* Berkay Uzun									|
*												|
*												|
* 												|
* 												|
* Date          : 28.12.2023					|
* By            : Berkay UZUN					|
* e-mail        : berkyuzun@gmail.com			|
* ______________________________________________|
*/


#ifndef MESSAGE_STRUCTURE_H
#define MESSAGE_STRUCTURE_H

#include <stdint.h>
#include "main.h"
#include "usbd_cdc_if.h"
/*--------------------> Global degiskenler ve tanimlamalar  <-----------------------------*/
extern TIM_HandleTypeDef htim1; // TIM1 icin tanimlanan Timer Handle'i
extern uint32_t TIM1_Address;	// TIM1'in adresi
extern uint16_t tim1_count;		// TIM1'in sayac degeri
extern uint16_t tim1_count_start; // TIM1'in başlangic sayac degeri
extern char dizi[64];			// Genel amacli bir karakter dizisi
extern int successfulMessageCount; // Hatasız mesaj sayacı
extern int errorMessageCount;     // Hatalı mesaj sayacı

/*--------------------> Mesaj yapisi icin baslangic degerleri<-----------------------------*/

#define COMMAND_NUMBER_START_INDEX 1 	// Emir numarasi icin başlangic indeksi
#define SLAVE_NUMBER_START_INDEX 5		// Birim numarasi icin başlangic indeksi
#define COMMAND_ADDRESS_START_INDEX 7	// Emir adresi icin başlangic indeksi
#define COMMAND_TYPE_START_INDEX 15		// Emir turu icin başlangic indeksi
#define DATA_TYPE_START_INDEX 17		// Data turu icin başlangic indeksi
#define CHAR_DATA_BLOCK_START_INDEX 19	// CHAR tipindeki data blogu için başlangic indeksi
#define Message_Length 24




/* ----------------------> ENUM TANIMLAMALARI <----------------------------- */

// Emir turleri enum'u
typedef enum {
    READ_COMMAND=0, // Okuma emiri
    WRITE_COMMAND	// Yazma emiri
} CommandType;

// Data tipleri enum'u
typedef enum {
    CHAR_TYPE=0,
    FLOAT_TYPE,
    INT_TYPE
} DataType;

typedef enum {
    NO_ERROR,				// Hata yok
    INVALID_START_CHAR,		// Gecersiz baslangic karakteri
    INVALID_END_CHAR,		// Gecersiz bitis karakteri
    INVALID_COMMAND_TYPE,	// Gecersiz emir turu
    INVALID_DATA_TYPE,		// Gecersiz data turu
	INVALID_DATA_SIZE

} ErrorCode;


/* ----------------------> MESAJ YAPISI <----------------------------- */
typedef struct {
    char start;              // Başlangic karakteri (£)
    uint16_t commandNumber;  // Emir numarasi
    uint8_t slaveNumber;     // Birim numarasi
    uint32_t commandAddress; // Emir adresi
    CommandType commandType; // Read veya Write komutu
    DataType dataType;       // Data tipi
    union {
        char charData[4];
        float floatData;
        uint16_t intData;
    } dataBlock;             // Data blogu
    char end;                 // Bitiş karakteri (%)
} Message;

/* ----------------------> FONKSIYON PROTOTIPLERI <----------------------------- */
ErrorCode parseMessage(char*);
void parseData(char*);
uint8_t hexToUint8(int,char[]);
uint16_t hexToUint16(int,char[]);
uint32_t hexToUint32(int,char[]);
int readCommand();
int writeCommand(const char*);



#endif // MESSAGE_STRUCTURE_H

