
#ifndef H_MPRINTF
#define H_MPRINTF

#include <stdarg.h>

int mprintf(const char *format, ...);
int mfprintf(FILE *fd, const char *format, ...);
int msprintf(char *buffer, const char *format, ...);
int msnprintf(char *buffer, size_t maxlength, const char *format, ...);
int mvprintf(const char *format, va_list args);
int mvfprintf(FILE *fd, const char *format, va_list args);
int mvsprintf(char *buffer, const char *format, va_list args);
int mvsnprintf(char *buffer, size_t maxlength, const char *format, va_list args);
char *maprintf(const char *format, ...);
char *mvaprintf(const char *format, va_list args);

#ifdef _MPRINTF_REPLACE
# define printf mprintf
# define fprintf mfprintf
# define sprintf msprintf
# define snprintf msnprintf
# define vprintf mvprintf
# define vfprintf mvfprintf
# define vsprintf mvsprintf
# define vsnprintf mvsnprintf
#endif

#endif /* H_MPRINTF */
