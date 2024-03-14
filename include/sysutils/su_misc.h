/*
 * Misc utils header file.
 /* * Misc utils header file.
 * Copyright (C) 2014 Ingenic Semiconductor Co.
 */

#ifndef __SU_MISC_H__
#define __SU_MISC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif /* __cplusplus */

/**
 * @file
 * Sysutils other functional header files
 */

/**
 * @defgroup Sysutils_Misc
 * @ingroup sysutils
 * @brief Other features.
 * @{
 */

/**
 * Keystroke events.
 */
typedef enum {
KEY_RELEASED, /**< Key raised */
KEY_PRESSED, /**< key press */
} SUKeyEvent.

/**
 * LED behavior commands.
 */
typedef enum {
LED_OFF, /**< LED off */
LED_ON, /**< LED ON */
} SULedCmd.

/**
 * @fn int SU_Key_OpenEvent(void)
 *
 * Get the key event handle.
 *
 * @param none
 *
 * @retval >0 Key event handle.
 * @retval <=0 Failure.
 * @remarks
 * @remarks After successfully obtaining a key event handle, key events are "logged" until the key event is closed.
 * @remarks If multiple handles are opened, one key event is logged for each key event.
 * @remarks For example, if two threads each open a key event, and each thread holds a handle, the two threads will read the same sequence of events. * But if the two threads share the same key event, the two threads will read the same sequence of events.
 * But if the two threads share the same handle, each keystroke event will be read only once.
 *
 * @attention None.
 */
int SU_Key_OpenEvent(void);

/**
 * @fn int SU_Key_CloseEvent(int evfd)
 *
 * Close the key event.
 *
 * @param[in] evfd Key event handle.
 * @retval 0 Success.
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * * @retval 0 Success.
 * @remarks None
 * * @remarks None.
 * @attention None.
 */
int SU_Key_CloseEvent(int evfd).

/**
 * @fn int SU_Key_ReadEvent(int evfd, int *keyCode, SUKeyEvent *event)
 *
 * Reads a key event.
 *
 * @param[in] evfd Key event handle.
 * @param[in] keyCode Key code.
 * @param[out] event Key event pointer.
 * @retval 0 Success.
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * @remarks This function blocks.
 * @remarks This function blocks until a keystroke event occurs to return.
 * @remarks Key codes are defined in linux/input.h, and the mapping to GPIOs is defined in the kernel board-level file.
 * @remarks For example, a few common keystrokes:
 * @code
#define KEY_HOME 102 //HOME key
#define KEY_POWER 116 //Switch on/off key, usually also used as wakeup key.
#define KEY_WAKEUP 143 //Wakeup key, other than the POWER key, is used to wake up the system.
#define KEY_F13 183 //Defined as F13 when PIR is used as a key.
 * @endcode
 * @endcode
 * @remarks The definition of the key key code and GPIO number, whether it is used as a wake-up source or not, and the valid power level information are all defined in the kernel board level file as follows:
 * @remarks
 * @code
struct gpio_keys_button __attribute__((weak)) board_buttons[] = {
#ifdef GPIO_HOME
{
.gpio = GPIO_HOME, //define GPIO number
.code = KEY_HOME, //define the key code
.desc = "home key", //Define key code
.active_low = ACTIVE_LOW_HOME, //define active level
#ifdef WAKEUP_HOME
.wakeup = WAKEUP_HOME, //define if it can be used as a wakeup source, 1 for wakeup suspend
#endif
#ifdef CAN_DISABLE_HOME
.can_disable = CAN_DISABLE_HOME, //Define if CAN_DISABLE_HOME can be disabled.
#endif #ifdef CAN_DISABLE_HOME
}, //Define if it can be disabled #endif #ifdef CAN_DISABLE_HOME
#endif
#ifdef GPIO_POWER
{
.gpio = GPIO_POWER, #endif #ifdef GPIO_POWER {
.code = KEY_POWER, .desc = "power key", #ifdef
.desc = "power key", .active_low = ACTIVE_LOW_POWER
.active_low = ACTIVE_LOW_POWER, #ifdef WAKEUP_POWER
#ifdef WAKEUP_POWER
.wakeup = WAKEUP_POWER, #ifdef WAKEUP_POWER, #endif
#endif
#ifdef CAN_DISABLE_POWER
.can_disable = CAN_DISABLE_POWER, #endif #ifdef WAKEUP_POWER
#endif
}, #endif #ifdef CAN_DISABLE_POWER .
#endif
}
 * @endcode
 * @remarks For a numeric PIR, one way to use it is to define the PIR as a key, with the PIR trigger being equivalent to a key press event (@ref KEY_PRESSED), * and the PIR resume being equivalent to a key lift event (@ref KEY_RELEASED).
 * PIR recovery is equivalent to a key raise event (@ref KEY_RELEASED). If you need the PIR wakeup function, you can define the key corresponding to the PIR as the wakeup source.
 * @remarks For detailed usage of the API, please refer to sample-keyevent.c.
 * @attention None.
 * @attention None.
 */
int SU_Key_ReadEvent(int evfd, int *keyCode, SUKeyEvent *event);

/**
 * @fn int SU_Key_DisableEvent(int keyCode)
 * @fn int SU_Key_DisableEvent(int keyCode)
 * Disable key event.
 * @param[in] keyCode
 * @param[in] keyCode Key code.
 * @retval 0 Success.
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * * @remarks
 * @remarks If the key is configured as a wakeup source, then pressing the key while the system is SUSPENDING (whether the key is Opened or not) causes the system to wake up.
 * After a Disable key event, the system turns off interrupts for key events, and the key will not wake up the system.
 * @remarks This API can be used to disable PIR "key press" to wake up the system.
 * @remarks This API can be used to disable PIR "key" wakeup.
 * @attention None.
 */
int SU_Key_DisableEvent(int keyCode).

/**
 * @fn int SU_Key_EnableEvent(int keyCode)
 * @fn int SU_Key_EnableEvent(int keyCode)
 * Enable key event.
 *
 * @param[in] keyCode Key code.
 * @retval 0 Success.
 * @retval 0 Success.
 * @retval Non-zero Failure.
 * * @remarks As an inverse process of the Disable key event.
 * @remarks As an inverse procedure for the Disable key event. See @ref SU_Key_DisableEvent(int keyCode) for details.
 *
 * @attention None.
 */
int SU_Key_EnableEvent(int keyCode).

/**
 * @fn int SU_LED_Command(int ledNum, SULedCmd cmd)
 *
 * Sends an LED command.
 *
 * @param[in] ledNum LED number.
 * @param[in] cmd LED behavior command.
 *
 * @retval 0 Success.
 * @retval Non-0 Failure.
 * @retval 0 success. * @retval non 0 failure.
 * @remarks LED numbers vary depending on the development board.LED numbers are defined in the kernel board-level file and registered as Linux standard
 * The LED number is defined in the kernel board-level file and registered as a Linux standard Fixed Regulator device. In the board level file, you need to define the GPIO number, active level, power recursion relationship, etc. of the LEDs.
 * information in the board-level file. The following is an example of a fixed regulator with two LEDs defined:
 * @code
    FIXED_REGULATOR_DEF( //define fixed regulator
            led0, //Code FIXED_REGULATOR_DEF(
            "LED0", 3300000, GPIO_PA(14),
            
            "ldo7", "vled0", NULL);

    FIXED_REGULATOR_DEF(
            led1.
            "LED1", 3300000, GPIO_PA(15),
            high_enable, un_at_boot, 0.
            "ldo7", "vled1", NULL).

    static struct platform_device *fixed_regulator_devices[] __initdata = {
            &gsensor_regulator_device, &led0_regulator_device, __initdata = {
            
            &led1_regulator_device, &led1_regulator_device, &led1_regulator_device, &led1_regulator_device
    };

    static int __init fix_regulator_init(void) //Register regulator in subsys_initcall_sync
    {
            int i.

            for (i = 0; i < ARRAY_SIZE(fixed_regulator_devices); i++)
                    fixed_regulator_devices[i]->id = i;

            return platform_add_devices(fixed_regulator_devices,
                                        ARRAY_SIZE(fixed_regulator_devices)); }
    }
    subsys_initcall_sync(fix_regulator_init);
 * @endcode
 * @remarks Example usage of this API:
 * @code
   if (SU_LED_Command(0, LED_ON) < 0) // enable LED0
       printf("LED0 turn on error\n");
   printf("LED0 turn on error\n"); if (SU_LED_Command(1, LED_ON) < 0) //enable LED1
       printf("LED0 turn on error\n"); if (SU_LED_Command(1, LED_ON) < 0) // enable LED1
   printf("LED0 turn on error\n"); if (SU_LED_Command(0, LED_OFF) < 0) //turn off LED0
       printf("LED1 turn off error\n"); if (SU_LED_Command(0, LED_OFF) < 0) //Off LED0)
   printf("LED1 turn off error\n"); if (SU_LED_Command(1, LED_OFF) < 0) //turn off LED1
       printf("LED1 turn off error\n");
 * @endcode
 * @attention None.
 */
int SU_LED_Command(int ledNum, SULedCmd cmd);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __SU_MISC_H__ */
