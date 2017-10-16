   /* Single header file for all URLs */
   if(config->headerfile) {
     /* open file for output: */
     if(!curlx_strequal(config->headerfile, "-")) {
       FILE *newfile = fopen(config->headerfile, "wb");
       if(!newfile) {
-        warnf(config, "Failed to open %s\n", config->headerfile);
+        warnf(config->global, "Failed to open %s\n", config->headerfile);
         result = CURLE_WRITE_ERROR;
         goto quit_curl;
       }
       else {
         heads.filename = config->headerfile;
         heads.s_isreg = TRUE;
