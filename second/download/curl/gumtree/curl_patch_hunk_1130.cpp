     }
   }
 
   /* Single header file for all URLs */
   if(config->headerfile) {
     /* open file for output: */
-    if(!curlx_strequal(config->headerfile, "-")) {
+    if(strcmp(config->headerfile, "-")) {
       FILE *newfile = fopen(config->headerfile, "wb");
       if(!newfile) {
         warnf(config->global, "Failed to open %s\n", config->headerfile);
         result = CURLE_WRITE_ERROR;
         goto quit_curl;
       }
