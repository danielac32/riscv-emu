#ifndef __CONSOLE_H__
#define __CONSOLE_H__

#include <stdint.h>

//-----------------------------------------------------------------
// Prototypes:
//-----------------------------------------------------------------
void console_init();
void console_putstr(const char *s);
void console_putchar(int ch);
int  console_getchar(void);

#endif

