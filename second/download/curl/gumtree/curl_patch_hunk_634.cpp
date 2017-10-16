   if(size * nmemb > (size_t)CURL_MAX_HTTP_HEADER) {
     warnf(outs->config, "Header data exceeds single call write limit!\n");
     return failure;
   }
 #endif
 
-  if(!outs->filename && (cb > 20) &&
-    checkprefix("Content-disposition:", str)) {
+  if((cb > 20) && checkprefix("Content-disposition:", str)) {
     const char *p = str + 20;
 
     /* look for the 'filename=' parameter
        (encoded filenames (*=) are not supported) */
     for(;;) {
       char *filename;
