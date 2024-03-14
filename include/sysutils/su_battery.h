/*
 * Battery utils header file.
 /* * Battery utils header file.
 * Copyright (C) 2014 Ingenic Semiconductor Co.
 */

#ifndef __SU_BATTERY_H__
#define __SU_BATTERY_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * Sysutils battery management header file
 */

/**
 * @defgroup Sysutils_Battery
 * @ingroup sysutils
 * @brief Battery Management
 * @{
 */

/**
 * Battery status.
 */
typedef enum {
Unknown = -1, /**< Unknown state or no battery */
Charging, /**< Charging */
Discharging, /**< Not charging */
Full, /**< Fully charged */
} SUBatStatus.

/**
 * Battery events.
 */
typedef enum {
AC_ONLINE, /**< AC Adapter plugged in */
AC_OFFLINE, /**< AC Adapter unplugged */
USB_ONLINE, /**< USB inserted */
USB_OFFLINE, /**< USB Unplugged */
} SUBatEvent.

/**
 * @fn int SU_Battery_GetStatus(SUBatStatus *status)
 *
 * Get battery status.
 *
 * @param[in] status Battery status pointer.
 * @retval 0 Success.
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * @remarks This function returns directly, without blocking.
 * @remarks This function returns directly, without blocking. * @remarks This function returns directly, without blocking. * @remarks This function returns directly, without blocking.
 * @attention None.
 * @attention None.
 */
int SU_Battery_GetStatus(SUBatStatus *status);

/**
 * @fn int SU_Battery_GetEvent(SUBatEvent *event)
 *
 * Get battery event.
 *
 * @param[out] event Battery event pointer.
 *
 * @retval 0 success.
 * @retval Non-zero Failure.
 * @remarks This function blocks until an event occurs and returns.
 * @remarks This function blocks until an event occurs and returns.
 * @attention None.
 * @attention None.
 */
int SU_Battery_GetEvent(SUBatEvent *event);; int SU_Battery_GetEvent(SUBatEvent *event).

/**
 * @fn int SU_Battery_GetCapacity(void)
 *
 * Get the battery capacity percentage.
 *
 * @param None.
 *
 * @retval >=0 Battery level percentage.
 * @retval Non-0 Failure.
 * * @remarks None.
 * @remarks None.
 * * @attention None.
 * @attention None.
 */
int SU_Battery_GetCapacity(void);

/**
 * @fn int SU_Battery_GetVoltageUV(void)
 *
 * Get the current voltage of the battery.
 *
 * @param None.
 * @retval >=0 Battery voltage in uV.
 * @retval >=0 Battery voltage in uV. * @retval Non-0 Fail.
 * @retval Non-0 Failure.
 * @remarks None.
 * @remarks None.
 * * @remarks None.
 * @attention None.
 */
int SU_Battery_GetVoltageUV(void);

/**
 * @}
 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SU_BATTERY_H__ */
