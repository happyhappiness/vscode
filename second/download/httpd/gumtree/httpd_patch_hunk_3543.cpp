     }
     if (snprintf_res >= sizeof(_request)) {
         err("Request too long\n");
     }
 
     if (verbosity >= 2)
-        printf("INFO: %s header == \n---\n%s\n---\n", 
+        printf("INFO: %s header == \n---\n%s\n---\n",
                method_str[method], request);
 
     reqlen = strlen(request);
 
     /*
      * Combine headers and (optional) post file into one continuous buffer
