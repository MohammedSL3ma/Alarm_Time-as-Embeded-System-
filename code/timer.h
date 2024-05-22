#ifndef TIMER0_H_
#define TIMER0_H_

#define NUMBER_OF_OVERLOWS 62

void timer0_init(void);
void timer0_setCallback(void(*a_ptr)(void));

#endif /* TIMER0_H_ */