   if(data && data->set.verbose) {
     va_list ap;
     char print_buffer[1024 + 1];
     va_start(ap, fmt);
     vsnprintf(print_buffer, 1024, fmt, ap);
     va_end(ap);
-    Curl_debug(data, CURLINFO_TEXT, print_buffer, strlen(print_buffer));
+    Curl_debug(data, CURLINFO_TEXT, print_buffer, strlen(print_buffer), NULL);
   }
 }
 
 /* Curl_failf() is for messages stating why we failed.
  * The message SHALL NOT include any LF or CR.
  */
 
 void Curl_failf(struct SessionHandle *data, const char *fmt, ...)
 {
   va_list ap;
+  size_t len;
   va_start(ap, fmt);
+
+  vsnprintf(data->state.buffer, BUFSIZE, fmt, ap);
+
   if(data->set.errorbuffer && !data->state.errorbuf) {
-    vsnprintf(data->set.errorbuffer, CURL_ERROR_SIZE, fmt, ap);
+    snprintf(data->set.errorbuffer, CURL_ERROR_SIZE, "%s", data->state.buffer);
     data->state.errorbuf = TRUE; /* wrote error string */
-
-    if(data->set.verbose) {
-      size_t len = strlen(data->set.errorbuffer);
-      bool doneit=FALSE;
-      if(len < CURL_ERROR_SIZE - 1) {
-        doneit = TRUE;
-        data->set.errorbuffer[len] = '\n';
-        data->set.errorbuffer[++len] = '\0';
-      }
-      Curl_debug(data, CURLINFO_TEXT, data->set.errorbuffer, len);
-      if(doneit)
-        /* cut off the newline again */
-        data->set.errorbuffer[--len]=0;
+  }
+  if(data->set.verbose) {
+    len = strlen(data->state.buffer);
+    if(len < BUFSIZE - 1) {
+      data->state.buffer[len] = '\n';
+      data->state.buffer[++len] = '\0';
     }
+    Curl_debug(data, CURLINFO_TEXT, data->state.buffer, len, NULL);
   }
+
   va_end(ap);
 }
 
 /* Curl_sendf() sends formated data to the server */
 CURLcode Curl_sendf(curl_socket_t sockfd, struct connectdata *conn,
                     const char *fmt, ...)
