/******************************************************************************
 * Module       : Common Macros
 * File Name    : common_macros.h
 * Author       : A7la Team :)
 * Created on   : 14/10/2024
 * Description  : Header file for common macros used for bit manipulation
 *******************************************************************************/

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/*******************************************************************************
 *                              Bit Manipulation Macros                        *
 *******************************************************************************/

/* Set a specific bit in a register */
#define SET_BIT(REG, BIT) (REG |= (1 << BIT))

/* Clear a specific bit in a register */
#define CLEAR_BIT(REG, BIT) (REG &= (~(1 << BIT)))

/* Toggle a specific bit in a register */
#define TOGGLE_BIT(REG, BIT) (REG ^= (1 << BIT))

/* Rotate right the register value by a specific number of rotates */
#define ROR(REG, NUM) (REG = (REG >> NUM) | (REG << (8 - NUM)))

/* Rotate left the register value by a specific number of rotates */
#define ROL(REG, NUM) (REG = (REG << NUM) | (REG >> (8 - NUM)))

/* Check if a specific bit is set in a register and return true if yes */
#define BIT_IS_SET(REG, BIT) (REG & (1 << BIT))

/* Check if a specific bit is cleared in a register and return true if yes */
#define BIT_IS_CLEAR(REG, BIT) (!(REG & (1 << BIT)))

/* Get the value of a specific bit in a register */
#define GET_BIT(REG, BIT) ((REG & (1 << BIT)) >> BIT)

#endif /* COMMON_MACROS_H_ */
