/*
 * SU ADC header file.
 /* * SU ADC header file.
 * Copyright (C) 2015 Ingenic Semiconductor Co.
 */

#ifndef __SU_ADC_H__
#define __SU_ADC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * ADC module header file
 */

/**
 * @defgroup Sysutils_ADC
 * @ingroup sysutils
 * @brief Modulo-digital conversion module
 * @brief Analog-to-digital conversion module * @brief
 * Please refer to Samples for usage.
 * @{
 */

/**
 * @fn int SU_ADC_Init(void).
 *
 * Initialize the ADC module.
 *
 * @retval 0 Success.
 * @retval Non-0 Failure, return error code.
 * @retval 0 success * @retval non 0 failure, return error code.
 * @remark Always call this function before using ADC.
 *
 * @attention None.
 */
int SU_ADC_Init(void).

/**
 * @fn int SU_ADC_Exit(void).
 *
 * De-initialize the ADC module.
 *
 * @retval 0 success
 * @retval Non-0 Failure, return error code.
 * @retval 0 success * @retval non 0 failure, return error code.
 * @remark Always call this function after not using ADC.
 *
 * @attention None.
 */
int SU_ADC_Exit(void).

/**
 * @fn int SU_ADC_EnableChn(uint32_t chn_num).
 *
 * Enable channel
 *
 * @param[in] chn_num Enable the first channel.
 *
 * @retval 0 success
 * @retval Non-0 Failure, return error code
 * * @remark None
 * @remark None
 * @remark None.
 * @attention None.
 */
int SU_ADC_EnableChn(uint32_t chn_num);

/**
 * @fn int SU_ADC_DisableChn(uint32_t chn_num).
 *
 * Disable channel.
 *
 * @param[in] chn_num stops the channel of the first channel
 *
 * @retval 0 success
 * @retval Non-0 Failure, return error code
 * * @remark no
 * @remark None
 * * @remark None
 * @attention None
 */
int SU_ADC_DisableChn(uint32_t chn_num);

/**
 * @fn int SU_ADC_GetChnValue(uint32_t chn_num, int *value);
 *
 * Get the ADC value of the chn_numth channel.
 *
 * @param[in] chn_num Channel number chn_num
 *
 * @param[out] value Get the ADC value of the chn_num channel.
 * @retval 0
 * @retval 0 success
 * @retval Non-0 Failure, return error code
 * * @remark no
 * @remark none
 * * @remark None
 * @attention None
 */
int SU_ADC_GetChnValue(uint32_t chn_num, int *value);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

/**
 * @}
 */

#endif /* __SU_ADC_H__ */
