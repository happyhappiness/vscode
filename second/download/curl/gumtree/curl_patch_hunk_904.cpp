 
   if(!heads->config)
     return failure;
 
 #ifdef DEBUGBUILD
   if(size * nmemb > (size_t)CURL_MAX_HTTP_HEADER) {
-    warnf(heads->config, "Header data exceeds single call write limit!\n");
+    warnf(heads->config->global, "Header data exceeds single call write "
+          "limit!\n");
     return failure;
   }
 #endif
 
   /*
    * Write header data when curl option --dump-header (-D) is given.
