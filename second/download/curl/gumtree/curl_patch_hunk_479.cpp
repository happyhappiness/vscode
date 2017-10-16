           while(ptr && (FORM_FILE_SEPARATOR!= *ptr)) {
 
             /* pass all white spaces */
             while(ISSPACE(*ptr))
               ptr++;
 
-            if(curlx_strnequal("type=", ptr, 5)) {
+            if(checkprefix("type=", ptr)) {
               /* set type pointer */
               type = &ptr[5];
 
               /* verify that this is a fine type specifier */
               if(2 != sscanf(type, "%127[^/]/%127[^;,\n]",
                              major, minor)) {
                 warnf(config, "Illegally formatted content-type field!\n");
                 free(contents);
-                FreeMultiInfo (multi_start);
+                FreeMultiInfo(multi_start);
                 return 2; /* illegal content-type syntax! */
               }
+
               /* now point beyond the content-type specifier */
               sep = (char *)type + strlen(major)+strlen(minor)+1;
 
+              /* there's a semicolon following - we check if it is a filename
+                 specified and if not we simply assume that it is text that
+                 the user wants included in the type and include that too up
+                 to the next zero or semicolon. */
+              if((*sep==';') && !checkprefix(";filename=", sep)) {
+                sep2 = strchr(sep+1, ';');
+                if(sep2)
+                  sep = sep2;
+                else
+                  sep = sep+strlen(sep); /* point to end of string */
+              }
+
               if(*sep) {
                 *sep=0; /* zero terminate type string */
 
                 ptr=sep+1;
               }
               else
                 ptr = NULL; /* end */
             }
-            else if(curlx_strnequal("filename=", ptr, 9)) {
+            else if(checkprefix("filename=", ptr)) {
               filename = &ptr[9];
               ptr=strchr(filename, FORM_TYPE_SEPARATOR);
               if(!ptr) {
                 ptr=strchr(filename, FORM_FILE_SEPARATOR);
               }
               if(ptr) {
