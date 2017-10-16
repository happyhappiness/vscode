  */
 
 void Curl_failf(struct Curl_easy *data, const char *fmt, ...)
 {
   va_list ap;
   size_t len;
+  char error[CURL_ERROR_SIZE + 2];
   va_start(ap, fmt);
 
-  vsnprintf(data->state.buffer, BUFSIZE, fmt, ap);
+  vsnprintf(error, CURL_ERROR_SIZE, fmt, ap);
+  len = strlen(error);
 
   if(data->set.errorbuffer && !data->state.errorbuf) {
-    snprintf(data->set.errorbuffer, CURL_ERROR_SIZE, "%s", data->state.buffer);
+    strcpy(data->set.errorbuffer, error);
     data->state.errorbuf = TRUE; /* wrote error string */
   }
   if(data->set.verbose) {
-    len = strlen(data->state.buffer);
-    if(len < BUFSIZE - 1) {
-      data->state.buffer[len] = '\n';
-      data->state.buffer[++len] = '\0';
-    }
-    Curl_debug(data, CURLINFO_TEXT, data->state.buffer, len, NULL);
+    error[len] = '\n';
+    error[++len] = '\0';
+    Curl_debug(data, CURLINFO_TEXT, error, len, NULL);
   }
 
   va_end(ap);
 }
 
 /* Curl_sendf() sends formatted data to the server */
