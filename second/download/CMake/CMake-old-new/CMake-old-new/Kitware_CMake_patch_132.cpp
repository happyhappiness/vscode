@@ -60,7 +60,7 @@
 #include "curl_sec.h"
 #include "ftp.h"
 #include "sendf.h"
-#include "rawstr.h"
+#include "strcase.h"
 #include "warnless.h"
 
 /* The last #include file should be: */
@@ -122,7 +122,7 @@ static int ftp_send_command(struct connectdata *conn, const char *message, ...)
   vsnprintf(print_buffer, sizeof(print_buffer), message, args);
   va_end(args);
 
-  if(Curl_ftpsendf(conn, print_buffer)) {
+  if(Curl_ftpsend(conn, print_buffer)) {
     ftp_code = -1;
   }
   else {
@@ -192,15 +192,18 @@ static CURLcode read_data(struct connectdata *conn,
                           struct krb5buffer *buf)
 {
   int len;
-  void* tmp;
+  void *tmp = NULL;
   CURLcode result;
 
   result = socket_read(fd, &len, sizeof(len));
   if(result)
     return result;
 
-  len = ntohl(len);
-  tmp = realloc(buf->data, len);
+  if(len) {
+    /* only realloc if there was a length */
+    len = ntohl(len);
+    tmp = realloc(buf->data, len);
+  }
   if(tmp == NULL)
     return CURLE_OUT_OF_MEMORY;
 