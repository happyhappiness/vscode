@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2014, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -59,14 +59,12 @@
 #include "getinfo.h"
 #include "transfer.h"
 #include "url.h"
-#include "curl_memory.h"
 #include "parsedate.h" /* for the week day and month names */
 #include "warnless.h"
+#include "curl_printf.h"
 
-#define _MPRINTF_REPLACE /* use our functions only */
-#include <curl/mprintf.h>
-
-/* The last #include file should be: */
+/* The last #include files should be: */
+#include "curl_memory.h"
 #include "memdebug.h"
 
 #if defined(WIN32) || defined(MSDOS) || defined(__EMX__) || \
@@ -196,8 +194,9 @@ static CURLcode file_connect(struct connectdata *conn, bool *done)
   int i;
   char *actual_path;
 #endif
+  int real_path_len;
 
-  real_path = curl_easy_unescape(data, data->state.path, 0, NULL);
+  real_path = curl_easy_unescape(data, data->state.path, 0, &real_path_len);
   if(!real_path)
     return CURLE_OUT_OF_MEMORY;
 
@@ -222,16 +221,23 @@ static CURLcode file_connect(struct connectdata *conn, bool *done)
      (actual_path[2] == ':' || actual_path[2] == '|')) {
     actual_path[2] = ':';
     actual_path++;
+    real_path_len--;
   }
 
   /* change path separators from '/' to '\\' for DOS, Windows and OS/2 */
-  for(i=0; actual_path[i] != '\0'; ++i)
+  for(i=0; i < real_path_len; ++i)
     if(actual_path[i] == '/')
       actual_path[i] = '\\';
+    else if(!actual_path[i]) /* binary zero */
+      return CURLE_URL_MALFORMAT;
 
   fd = open_readonly(actual_path, O_RDONLY|O_BINARY);
   file->path = actual_path;
 #else
+  if(memchr(real_path, 0, real_path_len))
+    /* binary zeroes indicate foul play */
+    return CURLE_URL_MALFORMAT;
+
   fd = open_readonly(real_path, O_RDONLY);
   file->path = real_path;
 #endif
@@ -295,7 +301,7 @@ static CURLcode file_upload(struct connectdata *conn)
   const char *dir = strchr(file->path, DIRSEP);
   int fd;
   int mode;
-  CURLcode res=CURLE_OK;
+  CURLcode result = CURLE_OK;
   struct SessionHandle *data = conn->data;
   char *buf = data->state.buffer;
   size_t nread;
@@ -309,8 +315,6 @@ static CURLcode file_upload(struct connectdata *conn)
    * Since FILE: doesn't do the full init, we need to provide some extra
    * assignments here.
    */
-  conn->fread_func = data->set.fread_func;
-  conn->fread_in = data->set.in;
   conn->data->req.upload_fromhere = buf;
 
   if(!dir)
@@ -351,10 +355,10 @@ static CURLcode file_upload(struct connectdata *conn)
       data->state.resume_from = (curl_off_t)file_stat.st_size;
   }
 
-  while(res == CURLE_OK) {
+  while(!result) {
     int readcount;
-    res = Curl_fillreadbuffer(conn, BUFSIZE, &readcount);
-    if(res)
+    result = Curl_fillreadbuffer(conn, BUFSIZE, &readcount);
+    if(result)
       break;
 
     if(readcount <= 0)  /* fix questionable compare error. curlvms */
@@ -381,7 +385,7 @@ static CURLcode file_upload(struct connectdata *conn)
     /* write the data to the target */
     nwrite = write(fd, buf2, nread);
     if(nwrite != nread) {
-      res = CURLE_SEND_ERROR;
+      result = CURLE_SEND_ERROR;
       break;
     }
 
@@ -390,16 +394,16 @@ static CURLcode file_upload(struct connectdata *conn)
     Curl_pgrsSetUploadCounter(data, bytecount);
 
     if(Curl_pgrsUpdate(conn))
-      res = CURLE_ABORTED_BY_CALLBACK;
+      result = CURLE_ABORTED_BY_CALLBACK;
     else
-      res = Curl_speedcheck(data, now);
+      result = Curl_speedcheck(data, now);
   }
-  if(!res && Curl_pgrsUpdate(conn))
-    res = CURLE_ABORTED_BY_CALLBACK;
+  if(!result && Curl_pgrsUpdate(conn))
+    result = CURLE_ABORTED_BY_CALLBACK;
 
   close(fd);
 
-  return res;
+  return result;
 }
 
 /*
@@ -417,7 +421,7 @@ static CURLcode file_do(struct connectdata *conn, bool *done)
      are supported. This means that files on remotely mounted directories
      (via NFS, Samba, NT sharing) can be accessed through a file:// URL
   */
-  CURLcode res = CURLE_OK;
+  CURLcode result = CURLE_OK;
   struct_stat statbuf; /* struct_stat instead of struct stat just to allow the
                           Windows version to have a different struct without
                           having to redefine the simple word 'stat' */
@@ -464,7 +468,6 @@ static CURLcode file_do(struct connectdata *conn, bool *done)
      information. Which for FILE can't be much more than the file size and
      date. */
   if(data->set.opt_no_body && data->set.include_header && fstated) {
-    CURLcode result;
     snprintf(buf, sizeof(data->state.buffer),
              "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n", expected_size);
     result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);
@@ -546,7 +549,7 @@ static CURLcode file_do(struct connectdata *conn, bool *done)
 
   Curl_pgrsTime(data, TIMER_STARTTRANSFER);
 
-  while(res == CURLE_OK) {
+  while(!result) {
     /* Don't fill a whole buffer if we want less than all data */
     size_t bytestoread =
       (expected_size < CURL_OFF_T_C(BUFSIZE) - CURL_OFF_T_C(1)) ?
@@ -563,21 +566,21 @@ static CURLcode file_do(struct connectdata *conn, bool *done)
     bytecount += nread;
     expected_size -= nread;
 
-    res = Curl_client_write(conn, CLIENTWRITE_BODY, buf, nread);
-    if(res)
-      return res;
+    result = Curl_client_write(conn, CLIENTWRITE_BODY, buf, nread);
+    if(result)
+      return result;
 
     Curl_pgrsSetDownloadCounter(data, bytecount);
 
     if(Curl_pgrsUpdate(conn))
-      res = CURLE_ABORTED_BY_CALLBACK;
+      result = CURLE_ABORTED_BY_CALLBACK;
     else
-      res = Curl_speedcheck(data, now);
+      result = Curl_speedcheck(data, now);
   }
   if(Curl_pgrsUpdate(conn))
-    res = CURLE_ABORTED_BY_CALLBACK;
+    result = CURLE_ABORTED_BY_CALLBACK;
 
-  return res;
+  return result;
 }
 
 #endif