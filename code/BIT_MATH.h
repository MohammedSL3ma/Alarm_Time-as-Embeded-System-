/*
 * BIT_MATH.h
 *
 * Created: 27/10/2020 13:21:43
 *  Author: 20114
 */ 


#ifndef BIT_MATH_H_
#define BIT_MATH_H_

#define SET_BIT(REG,BIT)     (REG|=(1<<BIT))
#define CLR_BIT(REG,BIT)     (REG&=~(1<<BIT))
#define TOGGLE_BIT(REG,BIT)  (REG^=(1<<BIT))
#define GET_BIT(REG,BIT)     ((REG>>BIT)&(0x01))

#endif /* BIT_MATH_H_ */