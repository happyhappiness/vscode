 /* Curl_infof() is for info message along the way */
 
 void Curl_infof(struct SessionHandle *data, const char *fmt, ...)
 {
   va_list ap;
   if(data->set.verbose) {
+    char print_buffer[1024 + 1];
     va_start(ap, fmt);
-    fputs("* ", data->set.err);
-    vfprintf(data->set.err, fmt, ap);
+    vsnprintf(print_buffer, 1024, fmt, ap);
     va_end(ap);
+    Curl_debug(data, CURLINFO_TEXT, print_buffer, strlen(print_buffer));
   }
 }
 
-/* Curl_failf() is for messages stating why we failed, the LAST one will be
-   returned for the user (if requested) */
+/* Curl_failf() is for messages stating why we failed.
+ * The message SHALL NOT include any LF or CR.
+ */
 
 void Curl_failf(struct SessionHandle *data, const char *fmt, ...)
 {
   va_list ap;
   va_start(ap, fmt);
-  if(data->set.errorbuffer)
+  if(data->set.errorbuffer && !data->state.errorbuf) {
     vsnprintf(data->set.errorbuffer, CURL_ERROR_SIZE, fmt, ap);
+    data->state.errorbuf = TRUE; /* wrote error string */
+  }
   va_end(ap);
 }
 
 /* Curl_sendf() sends formated data to the server */
-size_t Curl_sendf(int sockfd, struct connectdata *conn,
-                  const char *fmt, ...)
+CURLcode Curl_sendf(int sockfd, struct connectdata *conn,
+                    const char *fmt, ...)
 {
   struct SessionHandle *data = conn->data;
-  size_t bytes_written;
+  ssize_t bytes_written;
+  ssize_t write_len;
+  CURLcode res;
   char *s;
+  char *sptr;
   va_list ap;
   va_start(ap, fmt);
   s = vaprintf(fmt, ap); /* returns an allocated string */
   va_end(ap);
   if(!s)
-    return 0; /* failure */
-  if(data->set.verbose)
-    fprintf(data->set.err, "> %s", s);
+    return CURLE_OUT_OF_MEMORY; /* failure */
+
+  bytes_written=0;
+  write_len = strlen(s);
+  sptr = s;
+
+  do {
+    /* Write the buffer to the socket */
+    res = Curl_write(conn, sockfd, sptr, write_len, &bytes_written);
+
+    if(CURLE_OK != res)
+      break;
+
+    if(data->set.verbose)
+      Curl_debug(data, CURLINFO_DATA_OUT, sptr, bytes_written);
+
+    if(bytes_written != write_len) {
+      /* if not all was written at once, we must advance the pointer, decrease
+         the size left and try again! */
+      write_len -= bytes_written;
+      sptr += bytes_written;
+    }
+    else
+      break;
 
-  /* Write the buffer to the socket */
-  Curl_write(conn, sockfd, s, strlen(s), &bytes_written);
+  } while(1);
 
   free(s); /* free the output string */
 
-  return bytes_written;
+  return res;
 }
 
 /*
  * Curl_write() is an internal write function that sends plain (binary) data
  * to the server. Works with plain sockets, SSL or kerberos.
  *
  */
 CURLcode Curl_write(struct connectdata *conn, int sockfd,
                     void *mem, size_t len,
-                    size_t *written)
+                    ssize_t *written)
 {
-  size_t bytes_written;
+  ssize_t bytes_written;
 
 #ifdef USE_SSLEAY
   /* SSL_write() is said to return 'int' while write() and send() returns
      'size_t' */
-  int ssl_bytes;
   if (conn->ssl.use) {
-    int loop=100; /* just a precaution to never loop endlessly */
-    while(loop--) {
-      ssl_bytes = SSL_write(conn->ssl.handle, mem, len);
-      if((0 >= ssl_bytes) ||
-         (SSL_ERROR_WANT_WRITE != SSL_get_error(conn->ssl.handle,
-                                                ssl_bytes) )) {
-        /* this converts from signed to unsigned... */
-        bytes_written = ssl_bytes;
-        break;
+    int err;
+    int rc = SSL_write(conn->ssl.handle, mem, len);
+
+    if(rc < 0) {
+      err = SSL_get_error(conn->ssl.handle, rc);
+    
+      switch(err) {
+      case SSL_ERROR_WANT_READ:
+      case SSL_ERROR_WANT_WRITE:
+        /* this is basicly the EWOULDBLOCK equivalent */
+        *written = 0;
+        return CURLE_OK;
       }
+      /* a true error */
+      failf(conn->data, "SSL_write() return error %d\n", err);
+      return CURLE_SEND_ERROR;
     }
+    bytes_written = rc;
   }
   else {
 #endif
 #ifdef KRB4
     if(conn->sec_complete) {
       bytes_written = Curl_sec_write(conn, sockfd, mem, len);
     }
     else
 #endif /* KRB4 */
+    {
       bytes_written = swrite(sockfd, mem, len);
+    }
+    if(-1 == bytes_written) {
+#ifdef WIN32
+      if(WSAEWOULDBLOCK == GetLastError())
+#else
+      if(EWOULDBLOCK == errno)
+#endif
+      {
+        /* this is just a case of EWOULDBLOCK */
+        *written=0;
+        return CURLE_OK;
+      }
+    }
 #ifdef USE_SSLEAY
   }
 #endif
 
   *written = bytes_written;
-  return CURLE_OK;
+  return (-1 != bytes_written)?CURLE_OK:CURLE_SEND_ERROR;
 }
 
 /* client_write() sends data to the write callback(s)
 
    The bit pattern defines to what "streams" to write to. Body and/or header.
    The defines are in sendf.h of course.
