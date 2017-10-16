 
       /* we use the @-letter to indicate file name(s) */
 
       struct multi_files *multi_start = NULL;
       struct multi_files *multi_current = NULL;
 
-      contp++;
+      char *ptr = contp;
+      char *end = ptr + strlen(ptr);
 
       do {
         /* since this was a file, it may have a content-type specifier
            at the end too, or a filename. Or both. */
-        char *ptr;
         char *filename = NULL;
-
-        sep = strchr(contp, ';');
-        sep2 = strchr(contp, ',');
-
-        /* pick the closest */
-        if(sep2 && (sep2 < sep)) {
-          sep = sep2;
-
-          /* no type was specified! */
-        }
+        char *word_end;
+        bool semicolon;
 
         type = NULL;
 
-        if(sep) {
-          bool semicolon = (';' == *sep) ? TRUE : FALSE;
-
-          *sep = '\0'; /* terminate file name at separator */
-
-          ptr = sep+1; /* point to the text following the separator */
-
-          while(semicolon && ptr && (','!= *ptr)) {
-
-            /* pass all white spaces */
-            while(ISSPACE(*ptr))
-              ptr++;
-
-            if(checkprefix("type=", ptr)) {
-              /* set type pointer */
-              type = &ptr[5];
-
-              /* verify that this is a fine type specifier */
-              if(2 != sscanf(type, "%127[^/]/%127[^;,\n]",
-                             type_major, type_minor)) {
-                warnf(config, "Illegally formatted content-type field!\n");
-                Curl_safefree(contents);
-                FreeMultiInfo(&multi_start, &multi_current);
-                return 2; /* illegal content-type syntax! */
-              }
-
-              /* now point beyond the content-type specifier */
-              sep = (char *)type + strlen(type_major)+strlen(type_minor)+1;
-
-              /* there's a semicolon following - we check if it is a filename
-                 specified and if not we simply assume that it is text that
-                 the user wants included in the type and include that too up
-                 to the next zero or semicolon. */
-              if(*sep==';') {
-                if(!checkprefix(";filename=", sep)) {
-                  sep2 = strchr(sep+1, ';');
-                  if(sep2)
-                    sep = sep2;
-                  else
-                    sep = sep + strlen(sep); /* point to end of string */
-                }
-              }
-              else
-                semicolon = FALSE;
+        ++ptr;
+        contp = get_param_word(&ptr, &word_end);
+        semicolon = (';' == *ptr) ? TRUE : FALSE;
+        *word_end = '\0'; /* terminate the contp */
+
+        /* have other content, continue parse */
+        while(semicolon) {
+          /* have type or filename field */
+          ++ptr;
+          while(*ptr && (ISSPACE(*ptr)))
+            ++ptr;
+
+          if(checkprefix("type=", ptr)) {
+            /* set type pointer */
+            type = &ptr[5];
+
+            /* verify that this is a fine type specifier */
+            if(2 != sscanf(type, "%127[^/]/%127[^;,\n]",
+                           type_major, type_minor)) {
+              warnf(config, "Illegally formatted content-type field!\n");
+              Curl_safefree(contents);
+              FreeMultiInfo(&multi_start, &multi_current);
+              return 2; /* illegal content-type syntax! */
+            }
 
-              if(*sep) {
-                *sep = '\0'; /* zero terminate type string */
+            /* now point beyond the content-type specifier */
+            sep = (char *)type + strlen(type_major)+strlen(type_minor)+1;
 
-                ptr = sep+1;
-              }
-              else
-                ptr = NULL; /* end */
-            }
-            else if(checkprefix("filename=", ptr)) {
-              filename = &ptr[9];
-              ptr = strchr(filename, ';');
-              if(!ptr) {
-                ptr = strchr(filename, ',');
-              }
-              if(ptr) {
-                *ptr = '\0'; /* zero terminate */
-                ptr++;
+            /* there's a semicolon following - we check if it is a filename
+               specified and if not we simply assume that it is text that
+               the user wants included in the type and include that too up
+               to the next sep. */
+            ptr = sep;
+            if(*sep==';') {
+              if(!checkprefix(";filename=", sep)) {
+                ptr = sep + 1;
+                (void)get_param_word(&ptr, &sep);
+                semicolon = (';' == *ptr) ? TRUE : FALSE;
               }
             }
             else
-              /* confusion, bail out of loop */
-              break;
-          }
+              semicolon = FALSE;
 
-          sep = ptr;
+            if(*sep)
+              *sep = '\0'; /* zero terminate type string */
+          }
+          else if(checkprefix("filename=", ptr)) {
+            ptr += 9;
+            filename = get_param_word(&ptr, &word_end);
+            semicolon = (';' == *ptr) ? TRUE : FALSE;
+            *word_end = '\0';
+          }
+          else {
+            /* unknown prefix, skip to next block */
+            char *unknown = NULL;
+            unknown = get_param_word(&ptr, &word_end);
+            semicolon = (';' == *ptr) ? TRUE : FALSE;
+            if(*unknown) {
+              *word_end = '\0';
+              warnf(config, "skip unknown form field: %s\n", unknown);
+            }
+          }
         }
+        /* now ptr point to comma or string end */
+
 
         /* if type == NULL curl_formadd takes care of the problem */
 
-        if(!AddMultiFiles(contp, type, filename, &multi_start,
+        if(*contp && !AddMultiFiles(contp, type, filename, &multi_start,
                           &multi_current)) {
           warnf(config, "Error building form post!\n");
           Curl_safefree(contents);
           FreeMultiInfo(&multi_start, &multi_current);
           return 3;
         }
-        contp = sep; /* move the contents pointer to after the separator */
 
-      } while(sep && *sep); /* loop if there's another file name */
+        /* *ptr could be '\0', so we just check with the string end */
+      } while(ptr < end); /* loop if there's another file name */
 
       /* now we add the multiple files section */
       if(multi_start) {
         struct curl_forms *forms = NULL;
-        struct multi_files *ptr = multi_start;
+        struct multi_files *start = multi_start;
         unsigned int i, count = 0;
-        while(ptr) {
-          ptr = ptr->next;
+        while(start) {
+          start = start->next;
           ++count;
         }
         forms = malloc((count+1)*sizeof(struct curl_forms));
         if(!forms) {
           fprintf(config->errors, "Error building form post!\n");
           Curl_safefree(contents);
           FreeMultiInfo(&multi_start, &multi_current);
           return 4;
         }
-        for(i = 0, ptr = multi_start; i < count; ++i, ptr = ptr->next) {
-          forms[i].option = ptr->form.option;
-          forms[i].value = ptr->form.value;
+        for(i = 0, start = multi_start; i < count; ++i, start = start->next) {
+          forms[i].option = start->form.option;
+          forms[i].value = start->form.value;
         }
         forms[count].option = CURLFORM_END;
         FreeMultiInfo(&multi_start, &multi_current);
         if(curl_formadd(httppost, last_post,
                         CURLFORM_COPYNAME, name,
                         CURLFORM_ARRAY, forms, CURLFORM_END) != 0) {
