@@ -5,7 +5,7 @@
  *                            | (__| |_| |  _ <| |___
  *                             \___|\___/|_| \_\_____|
  *
- * Copyright (C) 1998 - 2016, Daniel Stenberg, <daniel@haxx.se>, et al.
+ * Copyright (C) 1998 - 2017, Daniel Stenberg, <daniel@haxx.se>, et al.
  *
  * This software is licensed as described in the file COPYING, which
  * you should have received as part of this distribution. The terms
@@ -311,7 +311,6 @@ static CURLcode file_upload(struct connectdata *conn)
   size_t nread;
   size_t nwrite;
   curl_off_t bytecount = 0;
-  struct timeval now = Curl_tvnow();
   struct_stat file_stat;
   const char *buf2;
 
@@ -360,7 +359,7 @@ static CURLcode file_upload(struct connectdata *conn)
 
   while(!result) {
     int readcount;
-    result = Curl_fillreadbuffer(conn, BUFSIZE, &readcount);
+    result = Curl_fillreadbuffer(conn, (int)data->set.buffer_size, &readcount);
     if(result)
       break;
 
@@ -399,7 +398,7 @@ static CURLcode file_upload(struct connectdata *conn)
     if(Curl_pgrsUpdate(conn))
       result = CURLE_ABORTED_BY_CALLBACK;
     else
-      result = Curl_speedcheck(data, now);
+      result = Curl_speedcheck(data, Curl_tvnow());
   }
   if(!result && Curl_pgrsUpdate(conn))
     result = CURLE_ABORTED_BY_CALLBACK;
@@ -436,7 +435,6 @@ static CURLcode file_do(struct connectdata *conn, bool *done)
   char *buf = data->state.buffer;
   curl_off_t bytecount = 0;
   int fd;
-  struct timeval now = Curl_tvnow();
   struct FILEPROTO *file;
 
   *done = TRUE; /* unconditionally */
@@ -475,9 +473,10 @@ static CURLcode file_do(struct connectdata *conn, bool *done)
     time_t filetime;
     struct tm buffer;
     const struct tm *tm = &buffer;
-    snprintf(buf, CURL_BUFSIZE(data->set.buffer_size),
+    char header[80];
+    snprintf(header, sizeof(header),
              "Content-Length: %" CURL_FORMAT_CURL_OFF_T "\r\n", expected_size);
-    result = Curl_client_write(conn, CLIENTWRITE_BOTH, buf, 0);
+    result = Curl_client_write(conn, CLIENTWRITE_BOTH, header, 0);
     if(result)
       return result;
 
@@ -492,7 +491,7 @@ static CURLcode file_do(struct connectdata *conn, bool *done)
       return result;
 
     /* format: "Tue, 15 Nov 1994 12:45:26 GMT" */
-    snprintf(buf, BUFSIZE-1,
+    snprintf(header, sizeof(header),
              "Last-Modified: %s, %02d %s %4d %02d:%02d:%02d GMT\r\n",
              Curl_wkday[tm->tm_wday?tm->tm_wday-1:6],
              tm->tm_mday,
@@ -557,12 +556,11 @@ static CURLcode file_do(struct connectdata *conn, bool *done)
     size_t bytestoread;
 
     if(size_known) {
-      bytestoread =
-        (expected_size < CURL_OFF_T_C(BUFSIZE) - CURL_OFF_T_C(1)) ?
-        curlx_sotouz(expected_size) : BUFSIZE - 1;
+      bytestoread = (expected_size < data->set.buffer_size) ?
+        curlx_sotouz(expected_size) : (size_t)data->set.buffer_size;
     }
     else
-      bytestoread = BUFSIZE-1;
+      bytestoread = data->set.buffer_size-1;
 
     nread = read(fd, buf, bytestoread);
 
@@ -585,7 +583,7 @@ static CURLcode file_do(struct connectdata *conn, bool *done)
     if(Curl_pgrsUpdate(conn))
       result = CURLE_ABORTED_BY_CALLBACK;
     else
-      result = Curl_speedcheck(data, now);
+      result = Curl_speedcheck(data, Curl_tvnow());
   }
   if(Curl_pgrsUpdate(conn))
     result = CURLE_ABORTED_BY_CALLBACK;