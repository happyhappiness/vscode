     /* unknown tag and its companion, just ignore: */
     return CURLE_READ_ERROR; /* correct this */
   }
   return CURLE_OK;
 }
 
-
-/*
- * Read everything until a newline.
- */
-
-int GetLine(int sockfd, char *buf, struct UrlData *data)
-{
-  int nread;
-  int read_rc=1;
-  char *ptr;
-  ptr=buf;
-
-  /* get us a full line, terminated with a newline */
-  for(nread=0;
-      (nread<BUFSIZE) && read_rc;
-      nread++, ptr++) {
-#ifdef USE_SSLEAY
-    if (data->ssl.use) {
-      read_rc = SSL_read(data->ssl.handle, ptr, 1);
-    }
-    else {
-#endif
-      read_rc = sread(sockfd, ptr, 1);
-#ifdef USE_SSLEAY
-    }
-#endif /* USE_SSLEAY */
-    if (*ptr == '\n')
-      break;
-  }
-  *ptr=0; /* zero terminate */
-
-  if(data->bits.verbose) {
-    fputs("< ", data->err);
-    fwrite(buf, 1, nread, data->err);
-    fputs("\n", data->err);
-  }
-  return nread;
-}
-
-
-#ifndef WIN32
+#if !defined(WIN32)||defined(__CYGWIN32__)
 #ifndef RETSIGTYPE
 #define RETSIGTYPE void
 #endif
+static
 RETSIGTYPE alarmfunc(int signal)
 {
   /* this is for "-ansi -Wall -pedantic" to stop complaining!   (rabe) */
   (void)signal;
   return;
 }
 #endif
 
-CURLcode curl_write(CURLconnect *c_conn, char *buf, size_t amount,
-                   size_t *n)
-{
-  struct connectdata *conn = (struct connectdata *)c_conn;
-  struct UrlData *data;
-  size_t bytes_written;
-
-  if(!n || !conn || (conn->handle != STRUCT_CONNECT))
-    return CURLE_FAILED_INIT;
-  data = conn->data;
-
-#ifdef USE_SSLEAY
-  if (data->ssl.use) {
-    bytes_written = SSL_write(data->ssl.handle, buf, amount);
-  }
-  else {
-#endif
-#ifdef KRB4
-    if(conn->sec_complete)
-      bytes_written = sec_write(conn, conn->writesockfd, buf, amount);
-    else
-#endif
-      bytes_written = swrite(conn->writesockfd, buf, amount);
-#ifdef USE_SSLEAY
-  }
-#endif /* USE_SSLEAY */
-
-  *n = bytes_written;
-  return CURLE_OK;
-}
-
-CURLcode curl_read(CURLconnect *c_conn, char *buf, size_t buffersize,
-                   size_t *n)
-{
-  struct connectdata *conn = (struct connectdata *)c_conn;
-  struct UrlData *data;
-  size_t nread;
-
-  if(!n || !conn || (conn->handle != STRUCT_CONNECT))
-    return CURLE_FAILED_INIT;
-  data = conn->data;
-
-#ifdef USE_SSLEAY
-  if (data->ssl.use) {
-    nread = SSL_read (data->ssl.handle, buf, buffersize);
-  }
-  else {
-#endif
-#ifdef KRB4
-    if(conn->sec_complete)
-      nread = sec_read(conn, conn->sockfd, buf, buffersize);
-    else
-#endif
-      nread = sread (conn->sockfd, buf, buffersize);
-#ifdef USE_SSLEAY
-  }
-#endif /* USE_SSLEAY */
-  *n = nread;
-  return CURLE_OK;
-}
-
 CURLcode curl_disconnect(CURLconnect *c_connect)
 {
   struct connectdata *conn = c_connect;
 
   struct UrlData *data = conn->data;
 
