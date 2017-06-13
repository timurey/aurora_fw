/*------------------------------------------------------------------------*/
/* Universal string handler for user console interface  (C)ChaN, 2011     */
/*------------------------------------------------------------------------*/

#ifndef _STRFUNC
#define _STRFUNC

#define _USE_XFUNC_OUT	1	/* 1: Use output functions */
#define	_CR_CRLF		1	/* 1: Convert \n ==> \r\n in the output char */

#define _USE_XFUNC_IN	1	/* 1: Use input function */
#define	_LINE_ECHO		0	/* 1: Echo back input chars in xgets function */
#define _USE_COLOURFUL_OUT 1 /* 1: use colors in output */

#if _USE_COLOURFUL_OUT
#define PRIESC              "\033"
#define PRIdefault           "\033[0m"    // Normal (default).
#define PRIblod             "\033[1m"    // Bold.
#define PRIfaint            "\033[2m"    // Faint, decreased intensity (ISO 6429).
#define PRIitalicized       "\033[3m"    // Italicized (ISO 6429).
#define PRIunderlined       "\033[4m"    // Underlined.
#define PRIblink            "\033[5m"    // Blink (appears as Bold).
#define PRIinverse          "\033[7m"    // Inverse.
#define PRIhidden           "\033[8m"    // Invisible, i.e., hidden (VT300).
#define PRIcrossedout       "\033[9m"    // Crossed-out characters (ISO 6429).
#define PRIdoublyunderlined "\033[21m"   // Doubly-underlined (ISO 6429).
#define PRInormal           "\033[22m"   // Normal (neither bold nor faint).
#define PRInotitaliczed     "\033[23m"   // Not italicized (ISO 6429).
#define PRInotunderlined    "\033[24m"   // Not underlined.
#define PRIsteady           "\033[25m"   // Steady (not blinking).
#define PRIpositive         "\033[27m"   // Positive (not inverse).
#define PRIvisible          "\033[28m"   // Visible, i.e., not hidden (VT300).
#define PRInotcrossedout    "\033[29m"   // Not crossed-out (ISO 6429).
#define PRIfgBlack          "\033[30m"   // Set foreground color to Black.
#define PRIfgRed            "\033[31m"   // Set foreground color to Red.
#define PRIfgGreen          "\033[32m"   // Set foreground color to Green.
#define PRIfgYEllow         "\033[33m"   // Set foreground color to Yellow.
#define PRIfgBlue           "\033[34m"   // Set foreground color to Blue.
#define PRIfgMagenta        "\033[35m"   // Set foreground color to Magenta.
#define PRIfgCyan           "\033[36m"   // Set foreground color to Cyan.
#define PRIfgWhite          "\033[37m"   // Set foreground color to White.
#define PRIfgDefault        "\033[39m"   // Set foreground color to default (original).
#define PRIbgBlack          "\033[40m"   // Set background color to Black.
#define PRIbgRed            "\033[41m"   // Set background color to Red.
#define PRIbgGreen          "\033[42m"   // Set background color to Green.
#define PRIbgYellow         "\033[43m"   // Set background color to Yellow.
#define PRIbgBlue           "\033[44m"   // Set background color to Blue.
#define PRIbgMagenta        "\033[45m"   // Set background color to Magenta.
#define PRIbgCyan           "\033[46m"   // Set background color to Cyan.
#define PRIbgWhite          "\033[47m"   // Set background color to White.
#define PRIbgDefault        "\033[49m"   // Set background color to default (original).
#endif

#if _USE_XFUNC_OUT
#define xdev_out(func) xfunc_out = (void(*)(unsigned char))(func)
extern void (*xfunc_out)(unsigned char);
void xputc (char c);
void xputs (const char* str);
void xfputs (void (*func)(unsigned char), const char* str);
void xprintf (const char* fmt, ...);
void xsprintf (char* buff, const char* fmt, ...);
void xfprintf (void (*func)(unsigned char), const char*	fmt, ...);
void put_dump (const void* buff, unsigned long addr, int len, int width);
#define DW_CHAR		sizeof(char)
#define DW_SHORT	sizeof(short)
#define DW_LONG		sizeof(long)
#endif

#if _USE_XFUNC_IN
#define xdev_in(func) xfunc_in = (unsigned char(*)(void))(func)
extern unsigned char (*xfunc_in)(void);
int xgets (char* buff, int len);
int xfgets (unsigned char (*func)(void), char* buff, int len);
int xatoi (char** str, long* res);
#endif

#endif
