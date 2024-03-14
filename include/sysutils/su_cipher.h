/*
 * Cipher utils header file.
 /* * Cipher utils header file.
 * Copyright (C) 2014 Ingenic Semiconductor Co.
 */

#ifndef __SU_CIPHER_H__
#define __SU_CIPHER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * Sysutils encryption/decryption management header file
 */

/**
 * @defgroup Sysutils_Cipher
 * @ingroup sysutils
 * @brief Encryption and decryption management
 * @{
 */

/**
 * Select encryption algorithm.
 * @remarks Both AES and DES encryption algorithms are supported.
 */
typedef enum IN_UNF_CIPHER_ALG_E
IN_UNF_CIPHER_ALG_E
IN_UNF_CIPHER_ALG_AES = 0x0, * @remarks supports AES and DES encryption algorithms.
IN_UNF_CIPHER_ALG_DES = 0x1
} IN_UNF_CIPHER_ALG.

/**
 * Select encryption mode.
 * @remarks Both CBC and ECB encryption modes are supported.
 */
typedef enum IN_UNF_CIPHER_WORK_MODE_E
IN_UNF_CIPHER_WORK_MODE_E
IN_UNF_CIPHER_WORK_MODE_ECB = 0x0, IN_UNF_CIPHER_WORK_MODE_E
IN_UNF_CIPHER_WORK_MODE_CBC = 0x1,
IN_UNF_CIPHER_WORK_MODE_OTHER = 0x2
} IN_UNF_CIPHER_WORK_MODE.

/**
 * Select the length of the encryption key.
 * @remarks Due to hardware limitation, only 128bit length KEY is supported at this stage.
 */
typedef enum IN_UNF_CIPHER_KEY_LENGTH_E
IN_UNF_CIPHER_KEY_LENGTH_E
IN_UNF_CIPHER_KEY_AES_128BIT = 0x0, }
} IN_UNF_CIPHER_KEY_LENGTH.

/**
 * Select the length of data to be processed by the encryption algorithm at one time.
 * @remarks Due to hardware limitation, only 128bit data length is supported at this stage.
 */
typedef enum IN_UNF_CIPHER_BIT_WIDTH_E
IN_UNF_CIPHER_BIT_WIDTH_E
IN_UNF_CIPHER_BIT_WIDTH_128BIT = 0x0, }
} IN_UNF_CIPHER_BIT_WIDTH.

/**
 * Selection of cryptographic processing control structure.
 */
typedef struct IN_UNF_CIPHER_CTRL_S
{
unsigned int key[4]; /**< The key to be used for encryption.
unsigned int IV[4]; /**< IV vector to be used for encryption */
unsigned int enDataLen; /**< Total length of data to be processed */
IN_UNF_CIPHER_ALG enAlg; /**< Encryption algorithm used to process data */
IN_UNF_CIPHER_BIT_WIDTH enBitWidth; /**< The length of data to be processed by the encryption algorithm at one time */
IN_UNF_CIPHER_WORK_MODE enWorkMode; /**< Mode of the encryption algorithm used to process data */
IN_UNF_CIPHER_KEY_LENGTH enKeyLen; /**< The length of the KEY used by the encryption algorithm***.
} IN_UNF_CIPHER_CTRL.

/**
 * @fn int SU_CIPHER_Init(void)
 *
 * Encryption module open interface.
 *
 * @param None.
 *
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * * @retval 0 success. * @retval non 0 failure.
 * @remarks None.
 * * @attention None.
 * @attention None.
 */
int SU_CIPHER_Init(void);

/**
 * @fn int SU_CIPHER_Exit(void)
 *
 * Cryptographic module shutdown interface.
 *
 * @param None.
 *
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * * @retval 0 success. * @retval non 0 failure.
 * @remarks None.
 * * @attention None.
 * @attention None.
 */
int SU_CIPHER_Exit(void);

/**
 * @fn int SU_CIPHER_CreateHandle(void)
 *
 * Interface to obtain a handle to a cryptographic module.
 *
 * @param None.
 *
 * @retval Success: return handle.
 * @retval Failure: retval < 0.
 * @retval Failure: retval < 0.
 * @remarks None.
 * * @attention This function can be called multiple times.
 * @attention This function can be called multiple times, and each call returns a handle. * @retval After N calls to this function, it is necessary to call this function.
 * After N calls to this function, N calls to SU_CIPHER_DestroyHandle() are required to * destroy all handles.
 * Destroy all handles.
 *
 */
int SU_CIPHER_CreateHandle(void).

/**
 * @fn int SU_CIPHER_DestroyHandle(int fd)
 *
 * Destroys the cryptographic module handle.
 *
 * @param[in] fd Handle to be destroyed.
 *
 * @retval 0 Success.
 * @retval Non-0 Failure.
 * @remarks None.
 * @remarks None.
 * @attention This function can be called multiple times, each time destroying a handle.
 * @attention This function can be called multiple times, destroying a handle each time it is called.
 * @attention This function can be called multiple times, destroying a handle with each call.
 */
int SU_CIPHER_DestroyHandle(int fd).

/**
 * @fn int SU_CIPHER_ConfigHandle(int hCipher, IN_UNF_CIPHER_CTRL* Ctrl)
 *
 * Configures the cryptographic module.
 *
 * @param[in] hCipher Handle to be configured.
 * @param[in] Ctrl Structure with configuration information.
 * @retval 0 Success.
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * @retval 0 success. * @retval nonzero failure.
 * @remarks None.
 * * @attention None.
 * @attention None.
 */
 */
int SU_CIPHER_ConfigHandle(int hCipher, IN_UNF_CIPHER_CTRL* Ctrl);

/**
 * @fn int SU_CIPHER_Encrypt(int hCipher, unsigned int * srcAddr, unsigned int * dstAddr, unsigned int dataLen)
 *
 * Starts encryption of the data.
 *
 * @param[in] hCipher The handle of the operation to be performed.
 * @param[in] srcAddr The source address of the data to be encrypted.
 * @param[in] dstAddr The address where the data will be stored after encryption is complete.
 * @param[in] dataLen The length of the data to be processed.
 * @retval 0 Success.
 * @retval 0 Success.
 * @retval 0 Success.
 * @retval 0 success. * @retval non-zero failure.
 * @remarks None.
 * * @attention
 * @attention Encrypted data length dataLen should not exceed 1Mbyte (1024*1024).
 */ @attention
 */
int SU_CIPHER_Encrypt(int hCipher, unsigned int * srcAddr, unsigned int * dstAddr, unsigned int dataLen);

/**
 * @fn int SU_CIPHER_Decrypt(int hCipher, unsigned int * srcAddr, unsigned int * dstAddr, unsigned int dataLen);
 *
 * Starts data decryption.
 *
 * @param[in] hCipher The handle of the operation to be performed.
 * @param[in] srcAddr The source address of the data to be decrypted.
 * @param[in] dstAddr The address where the data will be stored after decryption is complete.
 * @param[in] dataLen The length of the data to be processed.
 * @retval 0 Success.
 * @retval 0 Success.
 * @retval 0 success. * @retval non 0 failure.
 * @retval 0 success. * @retval non-zero failure.
 * @remarks None.
 * * @attention
 * @attention Decrypted data length dataLen should not exceed 1Mbyte (1024*1024).
 */
 */
int SU_CIPHER_Decrypt(int hCipher, unsigned int * srcAddr, unsigned int * dstAddr, unsigned int dataLen);

/**
 * Error code.
 */
#define REINIT -10 /**< Repeat initialization */
#define INIT_FAILED -11 /**< Failed to initialize */
#define FAILED_GETHANDLE -12 /**< Failed to get handle */
#define INVALID_PARA -13 /**< Invalid Parameter */
#define SET_PARA_FAILED -14 /**< Failed to set parameter */
#define FAILURE -15 /**< Failed operation**/
#define SET_DATALEN_ERR -16 /**< Error in setting operation data length**/
#define EXIT_ERR -17 /**< Failed module exit */
#define UNINIT -18 /**< Module not initialized**/
#define FAILED_DESHANDLE -19 /**< Failed to destroy handle */

/**
 * @}
 */
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SU_CIPHER_H__ */
