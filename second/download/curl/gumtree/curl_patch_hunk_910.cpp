             /* unknown prefix, skip to next block */
             char *unknown = NULL;
             unknown = get_param_word(&ptr, &word_end);
             semicolon = (';' == *ptr) ? TRUE : FALSE;
             if(*unknown) {
               *word_end = '\0';
-              warnf(config, "skip unknown form field: %s\n", unknown);
+              warnf(config->global, "skip unknown form field: %s\n", unknown);
             }
           }
         }
         /* now ptr point to comma or string end */
 
 
         /* if type == NULL curl_formadd takes care of the problem */
 
         if(*contp && !AddMultiFiles(contp, type, filename, &multi_start,
                           &multi_current)) {
-          warnf(config, "Error building form post!\n");
+          warnf(config->global, "Error building form post!\n");
           Curl_safefree(contents);
           FreeMultiInfo(&multi_start, &multi_current);
           return 3;
         }
 
         /* *ptr could be '\0', so we just check with the string end */
