       }
       else {
         /* this is meant as a variable to output */
         char *end;
         char keepit;
         int i;
-        if(('{' == ptr[1]) && ((end = strchr(ptr, '}')) != NULL)) {
+        if('{' == ptr[1]) {
           bool match = FALSE;
+          end = strchr(ptr, '}');
           ptr += 2; /* pass the % and the { */
+          if(!end) {
+            fputs("%{", stream);
+            continue;
+          }
           keepit = *end;
           *end = 0; /* zero terminate */
           for(i = 0; replacements[i].name; i++) {
             if(curl_strequal(ptr, replacements[i].name)) {
               match = TRUE;
               switch(replacements[i].id) {
