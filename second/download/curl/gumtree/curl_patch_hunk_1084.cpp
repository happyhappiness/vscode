 }
 
 /* Curl_failf() is for messages stating why we failed.
  * The message SHALL NOT include any LF or CR.
  */
 
-void Curl_failf(struct SessionHandle *data, const char *fmt, ...)
+void Curl_failf(struct Curl_easy *data, const char *fmt, ...)
 {
   va_list ap;
   size_t len;
   va_start(ap, fmt);
 
   vsnprintf(data->state.buffer, BUFSIZE, fmt, ap);
