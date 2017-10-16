 
 #ifndef H_MPRINTF
 #define H_MPRINTF
 
 #include <stdarg.h>
 
-int mprintf(const char *format, ...);
-int mfprintf(FILE *fd, const char *format, ...);
-int msprintf(char *buffer, const char *format, ...);
-int msnprintf(char *buffer, size_t maxlength, const char *format, ...);
-int mvprintf(const char *format, va_list args);
-int mvfprintf(FILE *fd, const char *format, va_list args);
-int mvsprintf(char *buffer, const char *format, va_list args);
-int mvsnprintf(char *buffer, size_t maxlength, const char *format, va_list args);
-char *maprintf(const char *format, ...);
-char *mvaprintf(const char *format, va_list args);
+int curl_mprintf(const char *format, ...);
+int curl_mfprintf(FILE *fd, const char *format, ...);
+int curl_msprintf(char *buffer, const char *format, ...);
+int curl_msnprintf(char *buffer, size_t maxlength, const char *format, ...);
+int curl_mvprintf(const char *format, va_list args);
+int curl_mvfprintf(FILE *fd, const char *format, va_list args);
+int curl_mvsprintf(char *buffer, const char *format, va_list args);
+int curl_mvsnprintf(char *buffer, size_t maxlength, const char *format, va_list args);
+char *curl_maprintf(const char *format, ...);
+char *curl_mvaprintf(const char *format, va_list args);
 
 #ifdef _MPRINTF_REPLACE
-# define printf mprintf
-# define fprintf mfprintf
-# define sprintf msprintf
-# define snprintf msnprintf
-# define vprintf mvprintf
-# define vfprintf mvfprintf
-# define vsprintf mvsprintf
-# define vsnprintf mvsnprintf
+# define printf curl_mprintf
+# define fprintf curl_mfprintf
+# define sprintf curl_msprintf
+# define snprintf curl_msnprintf
+# define vprintf curl_mvprintf
+# define vfprintf curl_mvfprintf
+# define vsprintf curl_mvsprintf
+# define vsnprintf curl_mvsnprintf
+# define aprintf curl_maprintf
+# define vaprintf curl_mvaprintf
 #endif
 
 #endif /* H_MPRINTF */
