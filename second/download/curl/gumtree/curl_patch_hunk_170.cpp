 CURL_EXTERN char *curl_maprintf(const char *format, ...);
 CURL_EXTERN char *curl_mvaprintf(const char *format, va_list args);
 
 #ifdef _MPRINTF_REPLACE
 # define printf curl_mprintf
 # define fprintf curl_mfprintf
+#ifdef CURLDEBUG
+/* When built with CURLDEBUG we define away the sprintf() functions since we
+   don't want internal code to be using them */
+# define sprintf sprintf_was_used
+# define vsprintf vsprintf_was_used
+#else
 # define sprintf curl_msprintf
+# define vsprintf curl_mvsprintf
+#endif
 # define snprintf curl_msnprintf
 # define vprintf curl_mvprintf
 # define vfprintf curl_mvfprintf
-# define vsprintf curl_mvsprintf
 # define vsnprintf curl_mvsnprintf
 # define aprintf curl_maprintf
 # define vaprintf curl_mvaprintf
 #endif
 
-#endif /* H_MPRINTF */
+#endif /* __CURL_MPRINTF_H */
