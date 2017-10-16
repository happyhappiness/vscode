   }
 }
 
 /* failf() is for messages stating why we failed, the LAST one will be
    returned for the user (if requested) */
 
-void failf(struct UrlData *data, char *fmt, ...)
+void Curl_failf(struct UrlData *data, char *fmt, ...)
 {
   va_list ap;
   va_start(ap, fmt);
   if(data->errorbuffer)
     vsnprintf(data->errorbuffer, CURL_ERROR_SIZE, fmt, ap);
   else /* no errorbuffer receives this, write to data->err instead */
     vfprintf(data->err, fmt, ap);
   va_end(ap);
 }
 
-/* sendf() sends the formated data to the server */
-size_t sendf(int fd, struct UrlData *data, char *fmt, ...)
+/* Curl_sendf() sends formated data to the server */
+size_t Curl_sendf(int sockfd, struct connectdata *conn,
+                  char *fmt, ...)
 {
+  struct UrlData *data = conn->data;
   size_t bytes_written;
   char *s;
   va_list ap;
   va_start(ap, fmt);
-  s = mvaprintf(fmt, ap);
+  s = vaprintf(fmt, ap); /* returns an allocated string */
   va_end(ap);
   if(!s)
     return 0; /* failure */
   if(data->bits.verbose)
     fprintf(data->err, "> %s", s);
 
-#ifndef USE_SSLEAY
-  bytes_written = swrite(fd, s, strlen(s));
-#else /* USE_SSLEAY */
-  if (data->ssl.use) {
-    bytes_written = SSL_write(data->ssl.handle, s, strlen(s));
-  } else {
-    bytes_written = swrite(fd, s, strlen(s));
-  }
-#endif /* USE_SSLEAY */
+  /* Write the buffer to the socket */
+  Curl_write(conn, sockfd, s, strlen(s), &bytes_written);
+
   free(s); /* free the output string */
-  return(bytes_written);
+
+  return bytes_written;
 }
 
 /*
- * ftpsendf() sends the formated string as a ftp command to a ftp server
- *
- * NOTE: we build the command in a fixed-length buffer, which sets length
- * restrictions on the command!
+ * Curl_write() is an internal write function that sends plain (binary) data
+ * to the server. Works with plain sockets, SSL or kerberos.
  *
  */
-size_t ftpsendf(int fd, struct connectdata *conn, char *fmt, ...)
-{
-  size_t bytes_written;
-  char s[256];
-
-  va_list ap;
-  va_start(ap, fmt);
-  vsnprintf(s, 250, fmt, ap);
-  va_end(ap);
-
-  if(conn->data->bits.verbose)
-    fprintf(conn->data->err, "> %s\n", s);
-
-  strcat(s, "\r\n"); /* append a trailing CRLF */
-
-#ifdef KRB4
-  if(conn->sec_complete && conn->data->cmdchannel) {
-    bytes_written = sec_fprintf(conn, conn->data->cmdchannel, s);
-    fflush(conn->data->cmdchannel);
-  }
-  else
-#endif /* KRB4 */
-    {
-      bytes_written = swrite(fd, s, strlen(s));
-    }
-  return(bytes_written);
-}
-
-/* ssend() sends plain (binary) data to the server */
-size_t ssend(int fd, struct connectdata *conn, void *mem, size_t len)
+CURLcode Curl_write(struct connectdata *conn, int sockfd,
+                    void *mem, size_t len,
+                    size_t *written)
 {
   size_t bytes_written;
   struct UrlData *data=conn->data; /* conn knows data, not vice versa */
 
 #ifdef USE_SSLEAY
   if (data->ssl.use) {
-    bytes_written = SSL_write(data->ssl.handle, mem, len);
+    int loop=100; /* just a precaution to never loop endlessly */
+    while(loop--) {
+      bytes_written = SSL_write(data->ssl.handle, mem, len);
+      if((-1 != bytes_written) ||
+         (SSL_ERROR_WANT_WRITE != SSL_get_error(data->ssl.handle,
+                                                bytes_written) ))
+        break;
+    }
   }
   else {
 #endif
 #ifdef KRB4
     if(conn->sec_complete) {
-      bytes_written = sec_write(conn, fd, mem, len);
+      bytes_written = sec_write(conn, sockfd, mem, len);
     }
     else
 #endif /* KRB4 */
-      bytes_written = swrite(fd, mem, len);
+      bytes_written = swrite(sockfd, mem, len);
 #ifdef USE_SSLEAY
   }
 #endif
 
-  return bytes_written;
+  *written = bytes_written;
+  return CURLE_OK;
 }
 
+/*
+ * External write-function, writes to the data-socket.
+ * Takes care of plain sockets, SSL or kerberos transparently.
+ */
+CURLcode curl_write(CURLconnect *c_conn, char *buf, size_t amount,
+                   size_t *n)
+{
+  struct connectdata *conn = (struct connectdata *)c_conn;
+
+  if(!n || !conn || (conn->handle != STRUCT_CONNECT))
+    return CURLE_FAILED_INIT;
+
+  return Curl_write(conn, conn->sockfd, buf, amount, n);
+}
+
+
+
 /* client_write() sends data to the write callback(s)
 
    The bit pattern defines to what "streams" to write to. Body and/or header.
    The defines are in sendf.h of course.
  */
-CURLcode client_write(struct UrlData *data,
-                      int type,
-                      char *ptr,
-                      size_t len)
+CURLcode Curl_client_write(struct UrlData *data,
+                           int type,
+                           char *ptr,
+                           size_t len)
 {
   size_t wrote;
 
   if(0 == len)
     len = strlen(ptr);
 
