 CURL_EXTERN int curl_mvsprintf(char *buffer, const char *format, va_list args);
 CURL_EXTERN int curl_mvsnprintf(char *buffer, size_t maxlength,
                                 const char *format, va_list args);
 CURL_EXTERN char *curl_maprintf(const char *format, ...);
 CURL_EXTERN char *curl_mvaprintf(const char *format, va_list args);
 
-#ifdef _MPRINTF_REPLACE
-# undef printf
-# undef fprintf
-# undef sprintf
-# undef vsprintf
-# undef snprintf
-# undef vprintf
-# undef vfprintf
-# undef vsnprintf
-# undef aprintf
-# undef vaprintf
-# define printf curl_mprintf
-# define fprintf curl_mfprintf
-# define sprintf curl_msprintf
-# define vsprintf curl_mvsprintf
-# define snprintf curl_msnprintf
-# define vprintf curl_mvprintf
-# define vfprintf curl_mvfprintf
-# define vsnprintf curl_mvsnprintf
-# define aprintf curl_maprintf
-# define vaprintf curl_mvaprintf
-#endif
-
 #ifdef  __cplusplus
 }
 #endif
 
 #endif /* __CURL_MPRINTF_H */
