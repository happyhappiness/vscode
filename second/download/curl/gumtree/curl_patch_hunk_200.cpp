  * copies of the Software, and permit persons to whom the Software is
  * furnished to do so, under the terms of the COPYING file.
  *
  * This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
  * KIND, either express or implied.
  *
- * $Id: mprintf.h,v 1.13 2006-03-28 10:08:54 bagder Exp $
+ * $Id: mprintf.h,v 1.14 2006-10-30 16:26:24 giva Exp $
  ***************************************************************************/
 
 #include <stdarg.h>
 #include <stdio.h> /* needed for FILE */
 
 #include "curl.h"
 
+#ifdef  __cplusplus
+extern "C" {
+#endif
+
 CURL_EXTERN int curl_mprintf(const char *format, ...);
 CURL_EXTERN int curl_mfprintf(FILE *fd, const char *format, ...);
 CURL_EXTERN int curl_msprintf(char *buffer, const char *format, ...);
 CURL_EXTERN int curl_msnprintf(char *buffer, size_t maxlength, const char *format, ...);
 CURL_EXTERN int curl_mvprintf(const char *format, va_list args);
 CURL_EXTERN int curl_mvfprintf(FILE *fd, const char *format, va_list args);
