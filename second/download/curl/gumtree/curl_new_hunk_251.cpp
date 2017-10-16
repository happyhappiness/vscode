CURL_EXTERN int curl_mvsprintf(char *buffer, const char *format, va_list args);
CURL_EXTERN int curl_mvsnprintf(char *buffer, size_t maxlength, const char *format, va_list args);
CURL_EXTERN char *curl_maprintf(const char *format, ...);
CURL_EXTERN char *curl_mvaprintf(const char *format, va_list args);

#ifdef _MPRINTF_REPLACE
# undef printf
# undef fprintf
# undef sprintf
# undef vsprintf
# undef snprintf
# undef vprintf
# undef vfprintf
# undef vsnprintf
# undef aprintf
# undef vaprintf
# define printf curl_mprintf
# define fprintf curl_mfprintf
#ifdef CURLDEBUG
/* When built with CURLDEBUG we define away the sprintf() functions since we
   don't want internal code to be using them */
# define sprintf sprintf_was_used
