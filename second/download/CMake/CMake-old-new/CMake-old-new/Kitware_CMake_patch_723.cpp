@@ -154,9 +154,19 @@ void Curl_failf(struct SessionHandle *data, const char *fmt, ...)
     vsnprintf(data->set.errorbuffer, CURL_ERROR_SIZE, fmt, ap);
     data->state.errorbuf = TRUE; /* wrote error string */
 
-    if(data->set.verbose)
-      Curl_debug(data, CURLINFO_TEXT, data->set.errorbuffer,
-                 strlen(data->set.errorbuffer));
+    if(data->set.verbose) {
+      int len = strlen(data->set.errorbuffer);
+      bool doneit=FALSE;
+      if(len < CURL_ERROR_SIZE) {
+        doneit = TRUE;
+        data->set.errorbuffer[len] = '\n';
+        data->set.errorbuffer[++len] = '\0';
+      }
+      Curl_debug(data, CURLINFO_TEXT, data->set.errorbuffer, len);
+      if(doneit)
+        /* cut off the newline again */
+        data->set.errorbuffer[--len]=0;
+    }
   }
   va_end(ap);
 }
@@ -235,6 +245,9 @@ CURLcode Curl_write(struct connectdata *conn, int sockfd,
         /* this is basicly the EWOULDBLOCK equivalent */
         *written = 0;
         return CURLE_OK;
+      case SSL_ERROR_SYSCALL:
+        failf(conn->data, "SSL_write() returned SYSCALL, errno = %d\n", errno);
+        return CURLE_SEND_ERROR;
       }
       /* a true error */
       failf(conn->data, "SSL_write() return error %d\n", err);
@@ -328,36 +341,29 @@ int Curl_read(struct connectdata *conn,
               ssize_t *n)
 {
   ssize_t nread;
+  *n=0; /* reset amount to zero */
 
 #ifdef USE_SSLEAY
   if (conn->ssl.use) {
-    bool loop=TRUE;
-    int err;
-    do {
-      nread = SSL_read(conn->ssl.handle, buf, buffersize);
+    nread = SSL_read(conn->ssl.handle, buf, buffersize);
 
-      if(nread >= 0)
-        /* successful read */
-        break;
-
-      err = SSL_get_error(conn->ssl.handle, nread);
+    if(nread < 0) {
+      /* failed SSL_read */
+      int err = SSL_get_error(conn->ssl.handle, nread);
 
       switch(err) {
       case SSL_ERROR_NONE: /* this is not an error */
       case SSL_ERROR_ZERO_RETURN: /* no more data */
-        loop=0; /* get out of loop */
         break;
       case SSL_ERROR_WANT_READ:
       case SSL_ERROR_WANT_WRITE:
-        /* if there's data pending, then we re-invoke SSL_read() */
-        break;
+        /* there's data pending, re-invoke SSL_read() */
+        return -1; /* basicly EWOULDBLOCK */
       default:
         failf(conn->data, "SSL read error: %d", err);
         return CURLE_RECV_ERROR;
       }
-    } while(loop);
-    if(loop && SSL_pending(conn->ssl.handle))
-      return -1; /* basicly EWOULDBLOCK */
+    }
   }
   else {
 #endif