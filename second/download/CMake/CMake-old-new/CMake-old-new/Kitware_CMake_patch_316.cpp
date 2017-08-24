@@ -7,7 +7,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2006, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2013, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -20,7 +20,6 @@
  * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
  * KIND, either express or implied.
  *
- * $Id$
  ***************************************************************************/
 
 #include <stdarg.h>
@@ -35,11 +34,13 @@ extern "C" {
 CURL_EXTERN int curl_mprintf(const char *format, ...);
 CURL_EXTERN int curl_mfprintf(FILE *fd, const char *format, ...);
 CURL_EXTERN int curl_msprintf(char *buffer, const char *format, ...);
-CURL_EXTERN int curl_msnprintf(char *buffer, size_t maxlength, const char *format, ...);
+CURL_EXTERN int curl_msnprintf(char *buffer, size_t maxlength,
+                               const char *format, ...);
 CURL_EXTERN int curl_mvprintf(const char *format, va_list args);
 CURL_EXTERN int curl_mvfprintf(FILE *fd, const char *format, va_list args);
 CURL_EXTERN int curl_mvsprintf(char *buffer, const char *format, va_list args);
-CURL_EXTERN int curl_mvsnprintf(char *buffer, size_t maxlength, const char *format, va_list args);
+CURL_EXTERN int curl_mvsnprintf(char *buffer, size_t maxlength,
+                                const char *format, va_list args);
 CURL_EXTERN char *curl_maprintf(const char *format, ...);
 CURL_EXTERN char *curl_mvaprintf(const char *format, va_list args);
 
@@ -57,7 +58,7 @@ CURL_EXTERN char *curl_mvaprintf(const char *format, va_list args);
 # define printf curl_mprintf
 # define fprintf curl_mfprintf
 #ifdef CURLDEBUG
-/* When built with CURLDEBUG we define away the sprintf() functions since we
+/* When built with CURLDEBUG we define away the sprintf functions since we
    don't want internal code to be using them */
 # define sprintf sprintf_was_used
 # define vsprintf vsprintf_was_used