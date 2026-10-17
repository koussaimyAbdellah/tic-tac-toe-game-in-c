#ifndef INTERFACE_H
#define INTERFACE_H

typedef void (*interface)();

/**
 * main user interface,here is where we move to other interface
 * contain two interface 0 and 1. 
 */
void interface0(interface i1,interface i2);

/**
 * multuplayer interface ,after you chose these interface 
 * you can start play with others after you chose your mark
 * or get back to main interface
 */
void interface1();

/**
 * solo interface ,after you chose it you can play with bot after
 * you chose difficlty ,with mark to play with or get back to 
 * main interface.
 */
void interface2();

#endif