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
#include "message_structure.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Global olarak tanımlanan mesaj değişkeni
Message globalMessage;


/**
 * @brief Hexadecimal bir diziyi temsil eden bir char dizisinden uint8_t degeri cikarmak icin kullanilir.
 * @param startIndex: Başlangic indeksi
 * @param hex: Hexadecimal diziyi temsil eden char dizisi
 * @retval uint8_t turunde cikartilan deger
 */
uint8_t hexToUint8(int startIndex, char hex[]) {
    uint8_t result = 0;
    uint8_t length=2;	// Bir uint8_t icin hexadecimal değer 2 karakterlidir.

    for (uint8_t i = startIndex; i < startIndex + length; i++) {
        result = result << 4;	// 4 bit sola kaydırma işlemi yapılır.

        if (hex[i] >= '0' && hex[i] <= '9') {
            result |= hex[i] - '0';			// '0' ile '9' arasındaki karakterleri isler.
        } else if (hex[i] >= 'A' && hex[i] <= 'F') {
            result |= hex[i] - 'A' + 10;	// 'A' ile 'F' arasındaki karakterleri isler.
        } else if (hex[i] >= 'a' && hex[i] <= 'f') {
            result |= hex[i] - 'a' + 10;	// 'a' ile 'f' arasındaki karakterleri isler.
        } else {
            return -1;						// Gecersiz karakter durumunda -1 dondurulur.

        }
    }

    return result;
}
/**
 * @brief Hexadecimal bir diziyi temsil eden bir char dizisinden uint16_t degeri cikarmak icin kullanilir.
 * @param startIndex: Başlangic indeksi
 * @param hex: Hexadecimal diziyi temsil eden char dizisi
 * @retval uint16_t turunde cikartilan deger
 */
uint16_t hexToUint16(int startIndex, char hex[]) {
    uint16_t result = 0;
    uint8_t length=4;	// Bir uint16_t icin hexadecimal değer 4 karakterlidir.

    for (uint8_t i = startIndex; i < startIndex + length; i++) {
        result = result << 4;	// 4 bit sola kaydirma islemi yapılır.

        if (hex[i] >= '0' && hex[i] <= '9') {
            result |= hex[i] - '0';				// '0' ile '9' arasındaki karakterleri isler.
        } else if (hex[i] >= 'A' && hex[i] <= 'F') {
            result |= hex[i] - 'A' + 10;		// 'A' ile 'F' arasındaki karakterleri isler.
        } else if (hex[i] >= 'a' && hex[i] <= 'f') {
            result |= hex[i] - 'a' + 10;		// 'a' ile 'f' arasındaki karakterleri isler.
        } else {
            return -1;							// Gecersiz karakter durumunda -1 dondurulur.

        }
    }

    return result;
}
/**
 * @brief Hexadecimal bir diziyi temsil eden bir char dizisinden uint32_t degeri cikarmak icin kullanilir.
 * @param startIndex: Başlangic indeksi
 * @param hex: Hexadecimal diziyi temsil eden char dizisi
 * @retval uint32_t turunde cikartilan deger
 */
uint32_t hexToUint32(int startIndex, char hex[]) {
    uint32_t result = 0;
    uint8_t length=8;	// Bir uint32_t icin hexadecimal değer 8 karakterlidir.

    for (uint8_t i = startIndex; i < startIndex + length; i++) {
        result = result << 4;	// 4 bit sola kaydirma islemi yapılır.

        if (hex[i] >= '0' && hex[i] <= '9') {
            result |= hex[i] - '0';				// '0' ile '9' arasındaki karakterleri isler.
        } else if (hex[i] >= 'A' && hex[i] <= 'F') {
            result |= hex[i] - 'A' + 10;		// 'A' ile 'F' arasındaki karakterleri isler.
        } else if (hex[i] >= 'a' && hex[i] <= 'f') {
            result |= hex[i] - 'a' + 10;		// 'a' ile 'f' arasındaki karakterleri isler.
        } else {
            return -1;							// Gecersiz karakter durumunda -1 dondurulur.

        }
    }

    return result;
}
/**
 * @brief Gelen mesajın veri tipine göre özel işlemleri gerçekleştiren fonksiyon.
 *
 * @param messageString: Mesajı temsil eden string.
 * @return ErrorCode: Fonksiyonun başarılı olup olmadığını belirten hata kodu.
 */
int readCommand() {
    switch (globalMessage.dataType) {
        case CHAR_TYPE:
            // CHAR_TYPE ile ilgili islemler yapilabilir.
            break;
        case FLOAT_TYPE:
            // FLOAT_TYPE ile ilgili islemler yapilabilir.
            break;
        case INT_TYPE:
            if (globalMessage.commandNumber == 0x1234) {
                if (globalMessage.commandAddress == &tim1_count) {
                    sprintf(dizi, "Tim1 degeri: %d\n", tim1_count);
                } else {
                    sprintf(dizi, "Tim1 degeri yollanamadi\n");
                }
                CDC_Transmit_FS((uint8_t*)dizi, strlen(dizi));
            } else {
                // commandNumber kontrolu ile baska komutlar ile farkli islemler yapilabilir.
            }
            break;
        default:
            return INVALID_DATA_TYPE;
    }
    return NO_ERROR;
}
/**
 * @brief Gelen mesajın veri tipine göre özel işlemleri gerçekleştiren yazma fonksiyonu.
 *
 * INT_TYPE için gelen mesajdan alınan veriyi TIM1 sayacına atar ve
 * yeni degeri iletisim portuna gonderir.
 *
 * @param messageString: Mesaji temsil eden string.
 * @return ErrorCode: Fonksiyonun basarili olup olmadigini belirten hata kodu.
 */
int writeCommand(const char* messageString) {
    switch (globalMessage.dataType) {
        case CHAR_TYPE:
            // CHAR_TYPE ile ilgili islemler eklenebilir.
            break;
        case FLOAT_TYPE:
            // FLOAT_TYPE ile ilgili islemler eklenebilir.
            break;
        case INT_TYPE:
            globalMessage.dataBlock.intData= hexToUint16(CHAR_DATA_BLOCK_START_INDEX, messageString);
            __HAL_TIM_SET_COUNTER(&htim1, globalMessage.dataBlock.intData);
            sprintf(dizi, "Yeni Tim1 degeri: %d\n", globalMessage.dataBlock.intData);
            CDC_Transmit_FS((uint8_t*)dizi, strlen(dizi));
            break;
        default:
            return INVALID_DATA_TYPE;
    }
    return NO_ERROR;
}

/**
 * @brief Mesaj stringini analiz ederek globalMessage yapisini dolduran ve mesaji isleyen bir fonksiyon.
 *
 * Bu fonksiyon, verilen mesaj stringini analiz eder, gecerliligini kontrol eder ve
 * globalMessage yapısına uygun degerleri atar. Ayrica, mesaj turune bagli olarak
 * ozel islemleri gerceklestirir (ornegin, belirli bir komut numarasina veya adresine göre kontrol).
 *
 * @param messageString: Analiz edilecek mesaj stringi.
 * @return ErrorCode: Fonksiyonun basarılı olup olmadığını belirten hata kodu.
 */
ErrorCode parseMessage(char* messageString) {
    // Başlangıç karakterini kontrol et
	if(strlen(messageString)!=Message_Length)
	{
		return INVALID_DATA_SIZE;
	}
    if (messageString[0] != 0xA3) // '£' karakteri kabul etmedigi icin ASCII karsiligi olan hex degerini kullandim.
    {
        return INVALID_START_CHAR;
    }


    // Bitiş karakterini kontrol et
    if (messageString[strlen(messageString)-1] != '%') {
        return INVALID_END_CHAR;
    }
    globalMessage.start=messageString[0];
    globalMessage.end=messageString[strlen(messageString)-1];
//Bu islem seti, bir char dizisinden belirli hexadecimal degerleri cikararak, bu degerleri dogrudan belirli veri turlerine donusturup, global degiskenlere atar.
    globalMessage.commandNumber = hexToUint16(COMMAND_NUMBER_START_INDEX, messageString);
    globalMessage.slaveNumber = hexToUint8(SLAVE_NUMBER_START_INDEX,messageString);
    globalMessage.commandAddress=hexToUint32(COMMAND_ADDRESS_START_INDEX, messageString);
    globalMessage.commandType = hexToUint8(COMMAND_TYPE_START_INDEX,messageString);
    globalMessage.dataType = hexToUint8(DATA_TYPE_START_INDEX,messageString);



    switch (globalMessage.commandType) {
            case READ_COMMAND:
                return readCommand();
            case WRITE_COMMAND:
                return writeCommand(messageString);
            default:
                return INVALID_COMMAND_TYPE;
        }
}
/**
 * @brief Analiz edilmis bir mesajin durumuna gore islem yapar ve gerekirse hata mesaji gonderir.
 *
 * @param buffer: Analiz edilmis mesajin string temsilcisi.
 */
void parseData(char *buffer)
{
	ErrorCode result = parseMessage(buffer);

	    switch (result) {
	            case NO_ERROR:
	                successfulMessageCount++;
	                break;
	            case INVALID_START_CHAR:
            		sprintf(dizi,"Baslangic karakteri hatali!\n");
	                break;
	            case INVALID_END_CHAR:
            		sprintf(dizi,"Bitis karakteri hatali!\n");
	                break;
	            case INVALID_COMMAND_TYPE:
            		sprintf(dizi,"Gecersiz komut tipi! Mesaj gonderimi basarisiz!\n");

	                break;
	            case INVALID_DATA_TYPE:
            		sprintf(dizi,"Gecersiz veri tipi! Mesaj gonderimi basarisiz!\n");

	                break;
	            case INVALID_DATA_SIZE:
            		sprintf(dizi,"Gecersiz veri uzunlugu!\n");
	                break;
	            default:
	                break;
	        }
	    if (result != NO_ERROR) {
	            CDC_Transmit_FS((uint8_t*)dizi, strlen(dizi));
	            errorMessageCount++;
	    }

}












