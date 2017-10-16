 
 size_t tool_write_cb(char *buffer, size_t sz, size_t nmemb, void *userdata)
 {
   size_t rc;
   struct OutStruct *outs = userdata;
   struct OperationConfig *config = outs->config;
+  size_t bytes = sz * nmemb;
+  bool is_tty = config->global->isatty;
 
   /*
    * Once that libcurl has called back tool_write_cb() the returned value
    * is checked against the amount that was intended to be written, if
    * it does not match then it fails with CURLE_WRITE_ERROR. So at this
    * point returning a value different from sz*nmemb indicates failure.
    */
-  const size_t failure = (sz && nmemb) ? 0 : 1;
-
-  if(!config)
-    return failure;
+  const size_t failure = bytes ? 0 : 1;
 
 #ifdef DEBUGBUILD
+  {
+    char *tty = curlx_getenv("CURL_ISATTY");
+    if(tty) {
+      is_tty = TRUE;
+      curl_free(tty);
+    }
+  }
+
   if(config->include_headers) {
-    if(sz * nmemb > (size_t)CURL_MAX_HTTP_HEADER) {
+    if(bytes > (size_t)CURL_MAX_HTTP_HEADER) {
       warnf(config->global, "Header data size exceeds single call write "
             "limit!\n");
       return failure;
     }
   }
   else {
-    if(sz * nmemb > (size_t)CURL_MAX_WRITE_SIZE) {
+    if(bytes > (size_t)CURL_MAX_WRITE_SIZE) {
       warnf(config->global, "Data size exceeds single call write limit!\n");
       return failure;
     }
   }
 
   {
