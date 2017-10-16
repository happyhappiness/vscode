             /* set type pointer */
             type = &ptr[5];
 
             /* verify that this is a fine type specifier */
             if(2 != sscanf(type, "%127[^/]/%127[^;,\n]",
                            type_major, type_minor)) {
-              warnf(config, "Illegally formatted content-type field!\n");
+              warnf(config->global,
+                    "Illegally formatted content-type field!\n");
               Curl_safefree(contents);
               FreeMultiInfo(&multi_start, &multi_current);
               return 2; /* illegal content-type syntax! */
             }
 
             /* now point beyond the content-type specifier */
