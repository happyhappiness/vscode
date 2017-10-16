 ************************************************************************/

#ifndef H_MPRINTF
#define H_MPRINTF

#include <stdarg.h>
#include <stdio.h> /* needed for FILE */

int curl_mprintf(const char *format, ...);
int curl_mfprintf(FILE *fd, const char *format, ...);
int curl_msprintf(char *buffer, const char *format, ...);
int curl_msnprintf(char *buffer, size_t maxlength, const char *format, ...);
int curl_mvprintf(const char *format, va_list args);
