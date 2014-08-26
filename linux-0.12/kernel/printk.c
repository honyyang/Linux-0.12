/*
 *  linux/kernel/printk.c
 *
 *  (C) 1991  Linus Torvalds
 */

/*
 * When in kernel-mode, we cannot use printf, as fs is liable to
 * point to 'interesting' things. Make a printf with fs-saving, and
 * all is well.
 */
#include <stdarg.h>
#include <stddef.h>

#include <linux/kernel.h>

static char buf[1024];

extern int vsprintf(char * buf, const char * fmt, va_list args);

int printk(const char *fmt, ...)
{
	va_list args;
	int i;

	asm (".globl __printk01\n\t__printk01:"::);
	va_start(args, fmt);
	asm (".globl __printk02\n\t__printk02:"::);
	i=vsprintf(buf,fmt,args);
	asm (".globl __printk03\n\t__printk03:"::);
	va_end(args);
	asm (".globl __printk04\n\t__printk04:"::);
	console_print(buf);
	asm (".globl __printk05\n\t__printk05:"::);
	return i;
}
