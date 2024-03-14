/*
 * IMP Decoder func header file.
 /* * IMP Decoder func header file.
 * Copyright (C) 2014 Ingenic Semiconductor Co.
 */

#ifndef __IMP_DECODER_H__
#define __IMP_DECODER_H__

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * IMP decoder header file
 */

/**
 * @defgroup IMP_Decoder
 * @ingroup imp
 * @brief Video decoding module, currently only supports JPEG decoding.
 * @{
 */

/**
 * Define decoder properties
 */
typedef struct {
IMPPayloadType decType; /**< Decode frame raw data protocol type */
uint32_t maxWidth; /**< Maximum width of the decoder frame */
uint32_t maxHeight; /**< Maximum height of the decoded frame */
IMPPixelFormat pixelFormat; /**< Decode frame target data protocol type */
uint32_t nrKeepStream; /**< Number of decoder cache frames */
uint32_t frmRateNum; /**< Number of time units in a second, in time units. That is, the numerator of the frame rate */
uint32_t frmRateDen; /**< The number of time units in a frame, in time units. The denominator of the frame rate */
} impDecoderAttr.

/**
 * Define the DecodeChannel property
 */
typedef struct {
IMPDecoderAttr decAttr; /**< Decoder Attribute */
} IMPDecoderCHNAttr.

/**
 * Define decoded frame data attributes
 */
typedef struct {
int i_payload; /**< Data length of the decoded frame */
uint8_t *p_payload; /**< Data pointer to decode frame */
int64_t timeStamp; /**< Decode frame timestamp */
} impDecoderNal.

/**
 * Define decoder stream properties
 */
typedef struct {
IMPDecoderNal decoderNal; /**< Decoder frame data structure */
} IMPDecoderStream.

/**
 * @fn int IMP_Decoder_CreateChn(int decChn, const IMPDecoderCHNAttr *attr)
 *
 * Creates a decoding Channel.
 *
 * @param[in] decChn decoding Channel number, range: [0, @ref NR_MAX_DEC_CHN - 1].
 * @param[in] attr Pointer to decoding Channel attribute.
 * @retval 0
 * @retval 0 success
 * @retval Non-0 Failure
 *
 * @remarks None.
 * @attention None.
 */
int IMP_Decoder_CreateChn(int decChn, const IMPDecoderCHNAttr *attr);

/**
 * @fn int IMP_Decoder_DestroyChn(int decChn)
 * @fn int IMP_Decoder_DestroyChn(int decChn)
 * Destroy the decoding Channel
 * @param[in] decChn
 * @param[in] decChn Decode Channel number, value range: [0, @ref NR_MAX_DEC_CHN - 1]
 * @retval 0 Success.
 * @retval 0 success
 * @retval 0 success * @retval non-0 failure
 * @retval 0 success * @retval non-zero failure
 * @remarks None.
 * @attention None.
 */
int IMP_Decoder_DestroyChn(int decChn).

/**
 * @fn int IMP_Decoder_StartRecvPic(int decChn)
 *
 * Start decoding Channel to receive images.
 *
 * @param[in] decChn decoding Channel number, value range: [0, @ref NR_MAX_DEC_CHN - 1]
 * @retval 0 Success.
 * @retval 0 success
 * @retval 0 success * @retval non-0 failure
 * @retval 0 success * @retval non-zero failure
 * @remarks Enable DecodeChannel to receive images before decoding can begin.
 * @remarks Enables the Decode Channel to receive images before decoding can begin.
 * @attention Returns failure if the Channel is not created.
 */
int IMP_Decoder_StartRecvPic(int decChn).

/**
 * @fn int IMP_Decoder_StopRecvPic(int decChn)
 *
 * Stop the decoding Channel from receiving images
 *
 * @param[in] decChn Decode Channel number, range: [0, @ref NR_MAX_DEC_CHN - 1].
 * @retval 0 Success.
 * @retval 0 success
 * @retval 0 success * @retval non-0 failure
 * @retval 0 success * @retval non-zero failure
 * @remarks Stop decoding Channel from receiving images.
 * @attention
 * @attention Returns failure if Channel is not created.
 */
int IMP_Decoder_StopRecvPic(int decChn).

/**
 * @fn int IMP_Decoder_SendStreamTimeout(int decChn, IMPDecoderStream *stream, uint32_t timeoutMsec)
 *
 * Send data to be decoded.
 *
 * @param[in] decChn Decode Channel number, range: [0, @ref NR_MAX_DEC_CHN - 1] * @param[in] stream.
 * @param[in] stream Pointer to the stream structure to be decoded.
 * @param[in] timeoutMsec Decoding timeout in ms.
 timeoutMsec decoding timeout in ms * @retval 0
 * @retval 0 success
 * @retval 0 success * @retval non-0 failure
 * @retval 0 success * @retval non-zero failure
 * @remarks None.
 *
 * @attention Returns failure if Channel is not created.
 */
int IMP_Decoder_SendStreamTimeout(int decChn, IMPDecoderStream *stream, uint32_t timeoutMsec);

/**
 * @fn int IMP_Decoder_PollingFrame(int decChn, uint32_t timeoutMsec)
 * @fn int IMP_Decoder_PollingFrame(int decChn)
 * Polling decoder stream cache.
 *
 * @param[in] decChn decoding Channel number, range: [0, @ref NR_MAX_DEC_CHN - 1] * @param[in] time[in] decChn, timeoutMsec
 * @param[in] timeoutMsec Timeout in ms.
 * @retval 0 Success.
 * @retval 0 Success
 * @retval Non-0 Failure
 *
 * @remarks None.
 *
 * @attention Returns failure if Channel is not created.
 */
int IMP_Decoder_PollingFrame(int decChn, uint32_t timeoutMsec);

/**
 * @fn int IMP_Decoder_GetFrame(int decChn, IMPFrameInfo **frame)
 *
 * Get the decoded stream.
 *
 * @param[in] decChn Decode Channel number, range: [0, @ref NR_MAX_DEC_CHN - 1].
 * @param[out] frame Pointer to decoder stream structure.
 * @retval 0
 * @retval 0 success
 * @retval 0 success * @retval non-0 failure
 *
 * @remarks None.
 * * @attention The decoding stream buffer is requested by the decoder internally.
 * @attention The decoding stream buffer is requested internally by the decoder, this function only needs to be passed a pointer to the structure.
 */
int IMP_Decoder_GetFrame(int decChn, IMPFrameInfo **frame);

/**
 * @fn int IMP_Decoder_ReleaseFrame(int decChn, IMPFrameInfo *frame)
 *
 * Releases the stream cache.
 *
 * @param[in] decChn Decode Channel number, range: [0, @ref NR_MAX_DEC_CHN - 1].
 * @param[in] frame Pointer to decode stream structure.
 * @retval 0 Success.
 * @retval 0 success
 * @retval 0 success * @retval non-0 failure
 * @retval 0 success * @retval non-zero failure
 * @remarks None.
 * * @attention None.
 * @attention None.
 */
int IMP_Decoder_ReleaseFrame(int decChn, IMPFrameInfo *frame);

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __IMP_DECODER_H__ */
