@@ -5,11 +5,11 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2015, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
- * are also available at http://curl.haxx.se/docs/copyright.html.
+ * are also available at https://curl.haxx.se/docs/copyright.html.
  *
  * You may opt to use, copy, modify, merge, publish, distribute and/or sell
  * copies of the Software, and permit persons to whom the Software is
@@ -61,9 +61,8 @@
 #include "url.h"
 #include "parsedate.h" /* for the week day and month names */
 #include "warnless.h"
+/* The last 3 #include files should be in this order */
 #include "curl_printf.h"
-
-/* The last #include files should be: */
 #include "curl_memory.h"
 #include "memdebug.h"
 
@@ -136,7 +135,7 @@ static CURLcode file_range(struct connectdata *conn)
   curl_off_t totalsize=-1;
   char *ptr;
   char *ptr2;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
 
   if(data->state.use_range && data->state.range) {
     from=curlx_strtoofft(data->state.range, &ptr, 0);
@@ -186,7 +185,7 @@ static CURLcode file_range(struct connectdata *conn)
  */
 static CURLcode file_connect(struct connectdata *conn, bool *done)
 {
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   char *real_path;
   struct FILEPROTO *file = data->req.protop;
   int fd;
@@ -228,15 +227,19 @@ static CURLcode file_connect(struct connectdata *conn, bool *done)
   for(i=0; i < real_path_len; ++i)
     if(actual_path[i] == '/')
       actual_path[i] = '\\';
-    else if(!actual_path[i]) /* binary zero */
+    else if(!actual_path[i]) { /* binary zero */
+      Curl_safefree(real_path);
       return CURLE_URL_MALFORMAT;
+    }
 
   fd = open_readonly(actual_path, O_RDONLY|O_BINARY);
   file->path = actual_path;
 #else
-  if(memchr(real_path, 0, real_path_len))
+  if(memchr(real_path, 0, real_path_len)) {
     /* binary zeroes indicate foul play */
+    Curl_safefree(real_path);
     return CURLE_URL_MALFORMAT;
+  }
 
   fd = open_readonly(real_path, O_RDONLY);
   file->path = real_path;
@@ -302,7 +305,7 @@ static CURLcode file_upload(struct connectdata *conn)
   int fd;
   int mode;
   CURLcode result = CURLE_OK;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   char *buf = data->state.buffer;
   size_t nread;
   size_t nwrite;
@@ -368,7 +371,7 @@ static CURLcode file_upload(struct connectdata *conn)
 
     /*skip bytes before resume point*/
     if(data->state.resume_from) {
-      if((curl_off_t)nread <= data->state.resume_from ) {
+      if((curl_off_t)nread <= data->state.resume_from) {
         data->state.resume_from -= nread;
         nread = 0;
         buf2 = buf;
@@ -426,9 +429,10 @@ static CURLcode file_do(struct connectdata *conn, bool *done)
                           Windows version to have a different struct without
                           having to redefine the simple word 'stat' */
   curl_off_t expected_size=0;
+  bool size_known;
   bool fstated=FALSE;
   ssize_t nread;
-  struct SessionHandle *data = conn->data;
+  struct Curl_easy *data = conn->data;
   char *buf = data->state.buffer;
   curl_off_t bytecount = 0;
   int fd;
@@ -468,6 +472,9 @@ static CURLcode file_do(struct connectdata *conn, bool *done)
      information. Which for FILE can't be much more than the file size and
      date. */
   if(data->set.opt_no_body && data->set.include_header && fstated) {
+    time_t filetime;
+    struct tm buffer;
+    const struct tm *tm = &buffer;
     snprintf(buf, sizeof(data->state.buffer),
              "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n", expected_size);
     result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);
@@ -479,29 +486,24 @@ static CURLcode file_do(struct connectdata *conn, bool *done)
     if(result)
       return result;
 
-    if(fstated) {
-      time_t filetime = (time_t)statbuf.st_mtime;
-      struct tm buffer;
-      const struct tm *tm = &buffer;
-      result = Curl_gmtime(filetime, &buffer);
-      if(result)
-        return result;
-
-      /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
-      snprintf(buf, BUFSIZE-1,
-               "Last-Modified: %s, %02d %s %4d %02d:%02d:%02d GMT\r\n",
-               Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
-               tm->tm_mday,
-               Curl_month[tm->tm_mon],
-               tm->tm_year + 1900,
-               tm->tm_hour,
-               tm->tm_min,
-               tm->tm_sec);
-      result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);
-    }
-    /* if we fstat()ed the file, set the file size to make it available post-
-       transfer */
-    if(fstated)
+    filetime = (time_t)statbuf.st_mtime;
+    result = Curl_gmtime(filetime, &buffer);
+    if(result)
+      return result;
+
+    /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
+    snprintf(buf, BUFSIZE-1,
+             "Last-Modified: %s, %02d %s %4d %02d:%02d:%02d GMT\r\n",
+             Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
+             tm->tm_mday,
+             Curl_month[tm->tm_mon],
+             tm->tm_year + 1900,
+             tm->tm_hour,
+             tm->tm_min,
+             tm->tm_sec);
+    result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);
+    if(!result)
+      /* set the file size to make it available post transfer */
       Curl_pgrsSetDownloadSize(data, expected_size);
     return result;
   }
@@ -531,8 +533,10 @@ static CURLcode file_do(struct connectdata *conn, bool *done)
   if(data->req.maxdownload > 0)
     expected_size = data->req.maxdownload;
 
-  if(fstated && (expected_size == 0))
-    return CURLE_OK;
+  if(!fstated || (expected_size == 0))
+    size_known = FALSE;
+  else
+    size_known = TRUE;
 
   /* The following is a shortcut implementation of file reading
      this is both more efficient than the former call to download() and
@@ -551,20 +555,27 @@ static CURLcode file_do(struct connectdata *conn, bool *done)
 
   while(!result) {
     /* Don't fill a whole buffer if we want less than all data */
-    size_t bytestoread =
-      (expected_size < CURL_OFF_T_C(BUFSIZE) - CURL_OFF_T_C(1)) ?
-      curlx_sotouz(expected_size) : BUFSIZE - 1;
+    size_t bytestoread;
+
+    if(size_known) {
+      bytestoread =
+        (expected_size < CURL_OFF_T_C(BUFSIZE) - CURL_OFF_T_C(1)) ?
+        curlx_sotouz(expected_size) : BUFSIZE - 1;
+    }
+    else
+      bytestoread = BUFSIZE-1;
 
     nread = read(fd, buf, bytestoread);
 
     if(nread > 0)
       buf[nread] = 0;
 
-    if(nread <= 0 || expected_size == 0)
+    if(nread <= 0 || (size_known && (expected_size == 0)))
       break;
 
     bytecount += nread;
-    expected_size -= nread;
+    if(size_known)
+      expected_size -= nread;
 
     result = Curl_client_write(conn, CLIENTWRITE_BODY, buf, nread);
     if(result)