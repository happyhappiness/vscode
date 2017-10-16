
#ifndef H_MPRINTF
#define H_MPRINTF

#include <stdarg.h>

int curl_mprintf(const char *format, ...);
int curl_mfprintf(FILE *fd, const char *format, ...);
int curl_msprintf(char *buffer, const char *format, ...);
int curl_msnprintf(char *buffer, size_t maxlength, const char *format, ...);
int curl_mvprintf(const char *format, va_list args);
int curl_mvfprintf(FILE *fd, const char *format, va_list args);
int curl_mvsprintf(char *buffer, const char *format, va_list args);
int curl_mvsnprintf(char *buffer, size_t maxlength, const char *format, va_list args);
char *curl_maprintf(const char *format, ...);
char *curl_mvaprintf(const char *format, va_list args);

#ifdef _MPRINTF_REPLACE
# define printf curl_mprintf
# define fprintf curl_mfprintf
# define sprintf curl_msprintf
# define snprintf curl_msnprintf
# define vprintf curl_mvprintf
# define vfprintf curl_mvfprintf
# define vsprintf curl_mvsprintf
# define vsnprintf curl_mvsnprintf
# define aprintf curl_maprintf
# define vaprintf curl_mvaprintf
#endif

#endif /* H_MPRINTF */
