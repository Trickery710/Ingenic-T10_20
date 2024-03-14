/*
 * System utils header file.
 /* * System utils header file.
 * Copyright (C) 2014 Ingenic Semiconductor Co.
 */

#ifndef __SU_BASE_H__
#define __SU_BASE_H__

#include <stdint.h>

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * Sysutils base function header file
 */

/**
 * @defgroup sysutils System Utils
 /* @defgroup sysutils

/**
 * @defgroup Sysutils_Base
 * @ingroup sysutils
 * @brief Sysutils_Base.
 * @{
 */

/**
 * Device ID logical code
 */
#define DEVICE_ID_MAGIC "53ef"

/**
 * Device ID logical code length
 */
#define DEVICE_ID_MAGIC_LEN 4

/**
 * Device ID length
 */
#define DEVICE_ID_LEN 32

/**
 * Maximum length of device model\device ID\firmware version information
 */
#define MAX_INFO_LEN 64

/**
 * Equipment model.
 */
typedef struct {
char chr[MAX_INFO_LEN]; /**< Device model string */
} suModelNum.

/**
 * Device software version.
 */
typedef struct {
char chr[MAX_INFO_LEN]; /**< Device software version string */
} suversion.

/**
 * Device ID. The device ID is a unique value and varies between CPU chips.
 */
typedef union {
char chr[MAX_INFO_LEN]; /** < Device ID string */
uint8_t hex[MAX_INFO_LEN]; /**< device ID binary */
} suDevID.

/**
 * System time structure.
 */
typedef struct {
int sec; /**< Number of seconds, range: 0~59 */
int min; /**< Number of minutes, range: 0~59 */
int hour; /**< Number of hours, range: 0~23 */
int mday; /**< day of the month, range: 1~31 */
int mon; /**< month, range: 1~12 */
int year; /**< Year, range: >1900 */
} SUTime.

/**
 * @fn int SU_Base_GetModelNumber(SUModelNum *modelNum)
 *
 * Get device model number.
 *
 * @param[out] modelNum Pointer to device model structure.
 *
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * * @remarks None.
 * @remarks None.
 * * @attention None.
 * @attention None.
 */
int SU_Base_GetModelNumber(SUModelNum *modelNum);

/**
 * @fn int SU_Base_GetVersion(SUVersion *version)
 *
 * Get device version.
 *
 * @param[out] version Pointer to device version structure.
 *
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * @retval 0 success. * @retval non 0 failure.
 * @remarks None.
 * * @attention None.
 * @attention None.
 */
int SU_Base_GetVersion(SUVersion *version).

/**
 * @fn int SU_Base_GetDevID(SUDevID *devID)
 *
 * Get device ID.
 *
 * @param[out] devID Pointer to device ID structure.
 *
 * @retval 0 Success.
 * @retval Non-0 Failure.
 * * @remarks Device ID for each CPU chip.
 * @remarks The device ID is unique for each CPU chip.
 * @attention None.
 * @attention None.
 */
int SU_Base_GetDevID(SUDevID *devID).

/**
 * @fn int SU_Base_GetTime(SUTime *time)
 *
 * Get the system time.
 *
 * @param[in] time Pointer to system time structure.
 *
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * @retval 0 success. * @retval non-zero failure.
 * @remarks None.
 * * @attention None.
 * @attention None.
 */
int SU_Base_GetTime(SUTime *time).

/**
 * @fn int SU_Base_SetTime(SUTime *time)
 *
 * Sets the system time.
 *
 * @param[out] time Pointer to system time structure.
 *
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * @retval 0 success. * @retval non-zero failure.
 * @remarks None.
 * * @attention
 * @attention The system time parameter needs to be within a reasonable range or the function call fails.
 */
int SU_Base_SetTime(SUTime *time).

/**
 * @fn int SU_Base_SUTime2Raw(SUTime *suTime, uint32_t *rawTime)
 *
 * Converts a time of type SUTime to Raw time in seconds.
 *
 * @param[in] suTime Pointer to system time structure.
 * @param[out] rawTime Raw time (from 1970-01-01 00:00:00).
 * @retval 0 Success.
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * @retval 0 success. * @retval non-zero failure.
 * @remarks This function can be used to set the relative seconds of the Alarm.
 * @attention None.
 * @attention None.
 */
int SU_Base_SUTime2Raw(SUTime *suTime, uint32_t *rawTime);

/**
 * @fn int SU_Base_Raw2SUTime(uint32_t *rawTime, SUTime *suTime)
 *
 * Converts Raw time in seconds to SUTime type.
 *
 * @param[in] rawTime Raw time (from 1970-01-01 00:00:00).
 * @param[out] suTime Pointer to system time structure.
 * @retval 0 Success.
 * @retval 0 success.
 * @retval Non-zero Failure.
 * @retval 0 success. * @retval non-zero failure.
 * @remarks This function can be used to set the relative seconds of Alarm.
 * @attention None.
 * @attention None.
 */
int SU_Base_Raw2SUTime(uint32_t *rawTime, SUTime *suTime);

/**
 * @fn int SU_Base_SetAlarm(SUTime *time)
 *
 * Set alarm time.
 *
 * @param[in] time Pointer to system time structure.
 * * @param[in] time Pointer to system time structure.
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * @retval 0 success. * @retval non 0 failure.
 * @remarks Temporarily supports setting alarms within 24 hours.
 * * @attention The system time parameter must be within a reasonable range or the function call will fail.
 * @attention The system time parameter must be within a reasonable range or the function call will fail.
 */
int SU_Base_SetAlarm(SUTime *time).

/**
 * @fn int SU_Base_GetAlarm(SUTime *time)
 *
 * Get alarm timer time.
 *
 * @param[out] time Pointer to system time structure.
 *
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * @retval 0 success. * @retval non-zero failure.
 * @remarks None.
 * * @attention None.
 * @attention None.
 */
int SU_Base_GetAlarm(SUTime *time).

/**
 * @fn int SU_Base_EnableAlarm()
 *
 * Enable alarm.
 *
 * @param None.
 *
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * * @remarks
 * @remarks Before calling this function, call SU_Base_GetAlarm (SUTime *time) to set the alarm time.
 * @attention
 * @attention Returns a failure if the alarm time is before the current system time.
 */
int SU_Base_EnableAlarm(void).

/**
 * @fn int SU_Base_DisableAlarm()
 *
 * Disable alarm.
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
int SU_Base_DisableAlarm(void).

/**
 * @fn int SU_Base_PollingAlarm(uint32_t timeoutMsec)
 *
 * Wait for the alarm.
 *
 * @param[in] timeout in milliseconds.
 *
 * @retval 0 Success.
 * @retval Non-0 Failure.
 * * @remarks After calling this function, the program goes into blocking.
 * @remarks After calling this function, the program enters a blocking state and continues until the alarm response exits or the timeout exits.
 * @attention None.
 * @attention None.
 */
int SU_Base_PollingAlarm(uint32_t timeoutMsec);

/**
 * @fn int SU_Base_Shutdown(void)
 *
 * Device shutdown.
 *
 * @param none.
 *
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * * @remarks The device shuts down immediately after calling this function and powers off the mains.
 * @remarks The device shuts down and turns off the main power immediately after calling this function.
 * @attention
 * @attention Make sure all files are saved before calling this function.
 */
int SU_Base_Shutdown(void).

/**
 * @fn int SU_Base_Reboot(void)
 *
 * Device reboot.
 *
 * @param none.
 *
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * * @remarks The device reboots immediately after calling this function.
 * @remarks The device reboots immediately after calling this function.
 * @attention Make sure you have saved all your files before calling this function.
 * @attention Make sure all files are saved before calling this function.
 */
int SU_Base_Reboot(void).

/**
 * @fn int SU_Base_Suspend(void)
 *
 * Device sleep.
 *
 * @param none.
 *
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * @remarks The device goes to sleep immediately after calling this function.
 * @remarks The device goes to sleep immediately after calling this function, and the function exits normally indicating that the system has woken up. * @remarks The device goes to sleep immediately after calling this function, and the function exits normally indicating that the system has woken up.
 * @attention None.
 * @attention None.
 */
int SU_Base_Suspend();

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SU_BASE_H__ */
