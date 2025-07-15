/******************************************************************************
 * Module       : Standard Types
 * File Name    : std_types.h
 * Author       : A7la Team :)
 * Created on   : 13/10/2024
 * Description  : Header file for standard types and definitions
 *******************************************************************************/

#ifndef STANDARD_TYPES_H_
#define STANDARD_TYPES_H_

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/

/* Enum to define timer clock types */
typedef enum
{
    NO_CLOCK,    /* No clock source (Timer is stopped) */
    F_CPU_CLOCK, /* Use CPU clock as the timer clock source */
    F_CPU_8,     /* Use CPU clock divided by 8 as the timer clock source */
    F_CPU_64,    /* Use CPU clock divided by 64 as the timer clock source */
    F_CPU_256,   /* Use CPU clock divided by 256 as the timer clock source */
    F_CPU_1024   /* Use CPU clock divided by 1024 as the timer clock source */
} Timer_ClockType;

/*******************************************************************************
 *                              Definitions                                   *
 *******************************************************************************/

/* Boolean Values */
#ifndef FALSE
#define FALSE               (0u)  /* Boolean false value */
#endif

#ifndef TRUE
#define TRUE                (1u)  /* Boolean true value */
#endif

#define LOGIC_HIGH          (1u)  /* Logical high value */
#define LOGIC_LOW           (0u)  /* Logical low value */

#define NULL_PTR            ((void*)0)  /* Null pointer definition */

/*******************************************************************************
 *                              Standard Types                                 *
 *******************************************************************************/

typedef unsigned char         uint8;   /* Unsigned 8-bit integer (0 to 255) */
typedef signed char           sint8;   /* Signed 8-bit integer (-128 to +127) */
typedef unsigned short        uint16;  /* Unsigned 16-bit integer (0 to 65535) */
typedef signed short          sint16;  /* Signed 16-bit integer (-32768 to +32767) */
typedef unsigned long         uint32;  /* Unsigned 32-bit integer (0 to 4294967295) */
typedef signed long           sint32;  /* Signed 32-bit integer (-2147483648 to +2147483647) */
typedef unsigned long long    uint64;  /* Unsigned 64-bit integer (0 to 18446744073709551615) */
typedef signed long long      sint64;  /* Signed 64-bit integer (-9223372036854775808 to 9223372036854775807) */
typedef float                 float32; /* Single precision floating point (32-bit) */
typedef double                float64; /* Double precision floating point (64-bit) */

#endif /* STANDARD_TYPES_H_ */
