 /*
 ** callback for CURLOPT_HEADERFUNCTION
 */
 
 size_t tool_header_cb(void *ptr, size_t size, size_t nmemb, void *userdata)
 {
-  struct OutStruct *outs = userdata;
+  struct HdrCbData *hdrcbdata = userdata;
+  struct OutStruct *outs = hdrcbdata->outs;
+  struct OutStruct *heads = hdrcbdata->heads;
   const char *str = ptr;
   const size_t cb = size * nmemb;
   const char *end = (char*)ptr + cb;
 
   /*
    * Once that libcurl has called back tool_header_cb() the returned value
    * is checked against the amount that was intended to be written, if
    * it does not match then it fails with CURLE_WRITE_ERROR. So at this
    * point returning a value different from sz*nmemb indicates failure.
    */
   size_t failure = (size * nmemb) ? 0 : 1;
 
-  if(!outs->config)
+  if(!heads->config)
     return failure;
 
 #ifdef DEBUGBUILD
   if(size * nmemb > (size_t)CURL_MAX_HTTP_HEADER) {
-    warnf(outs->config, "Header data exceeds single call write limit!\n");
+    warnf(heads->config, "Header data exceeds single call write limit!\n");
     return failure;
   }
 #endif
 
-  if((cb > 20) && checkprefix("Content-disposition:", str)) {
+  /*
+   * Write header data when curl option --dump-header (-D) is given.
+   */
+
+  if(heads->config->headerfile && heads->stream) {
+    size_t rc = fwrite(ptr, size, nmemb, heads->stream);
+    if(rc != cb)
+      return rc;
+  }
+
+  /*
+   * This callback sets the filename where output shall be written when
+   * curl options --remote-name (-O) and --remote-header-name (-J) have
+   * been simultaneously given and additionally server returns an HTTP
+   * Content-Disposition header specifying a filename property.
+   */
+
+  if(hdrcbdata->honor_cd_filename &&
+     (cb > 20) && checkprefix("Content-disposition:", str)) {
     const char *p = str + 20;
 
     /* look for the 'filename=' parameter
        (encoded filenames (*=) are not supported) */
     for(;;) {
       char *filename;
