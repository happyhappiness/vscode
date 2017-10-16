  * the old curl_formparse code.
  *
  ***************************************************************************/
 
 int formparse(struct OperationConfig *config,
               const char *input,
-              struct curl_httppost **httppost,
-              struct curl_httppost **last_post,
+              curl_mime **mimepost,
+              curl_mime **mimecurrent,
               bool literal_value)
 {
-  /* nextarg MUST be a string in the format 'name=contents' and we'll
+  /* input MUST be a string in the format 'name=contents' and we'll
      build a linked list with the info */
-  char name[256];
+  char *name = NULL;
   char *contents = NULL;
-  char type_major[128] = "";
-  char type_minor[128] = "";
   char *contp;
+  char *data;
   char *type = NULL;
-  char *sep;
-
-  if((1 == sscanf(input, "%255[^=]=", name)) &&
-     ((contp = strchr(input, '=')) != NULL)) {
-    /* the input was using the correct format */
-
-    /* Allocate the contents */
-    contents = strdup(contp+1);
-    if(!contents) {
-      fprintf(config->global->errors, "out of memory\n");
+  char *filename = NULL;
+  char *encoder = NULL;
+  struct curl_slist *headers = NULL;
+  curl_mimepart *part = NULL;
+  CURLcode res;
+  int sep = '\0';
+
+  /* Allocate the main mime structure if needed. */
+  if(!*mimepost) {
+    *mimepost = curl_mime_init(config->easy);
+    if(!*mimepost) {
+      warnf(config->global, "curl_mime_init failed!\n");
       return 1;
     }
-    contp = contents;
+    *mimecurrent = *mimepost;
+  }
 
-    if('@' == contp[0] && !literal_value) {
+  /* Make a copy we can overwrite. */
+  contents = strdup(input);
+  if(!contents) {
+    fprintf(config->global->errors, "out of memory\n");
+    return 2;
+  }
 
-      /* we use the @-letter to indicate file name(s) */
+  /* Scan for the end of the name. */
+  contp = strchr(contents, '=');
+  if(contp) {
+    if(contp > contents)
+      name = contents;
+    *contp++ = '\0';
+
+    if(*contp == '(' && !literal_value) {
+      curl_mime *subparts;
+
+      /* Starting a multipart. */
+      sep = get_param_part(config, &contp, &data, &type, NULL, NULL, &headers);
+      if(sep < 0) {
+        Curl_safefree(contents);
+        return 3;
+      }
+      subparts = curl_mime_init(config->easy);
+      if(!subparts) {
+        warnf(config->global, "curl_mime_init failed!\n");
+        curl_slist_free_all(headers);
+        Curl_safefree(contents);
+        return 4;
+      }
+      part = curl_mime_addpart(*mimecurrent);
+      if(!part) {
+        warnf(config->global, "curl_mime_addpart failed!\n");
+        curl_mime_free(subparts);
+        curl_slist_free_all(headers);
+        Curl_safefree(contents);
+        return 5;
+      }
+      if(curl_mime_subparts(part, subparts)) {
+        warnf(config->global, "curl_mime_subparts failed!\n");
+        curl_mime_free(subparts);
+        curl_slist_free_all(headers);
+        Curl_safefree(contents);
+        return 6;
+      }
+      *mimecurrent = subparts;
+      if(curl_mime_headers(part, headers, 1)) {
+        warnf(config->global, "curl_mime_headers failed!\n");
+        curl_slist_free_all(headers);
+        Curl_safefree(contents);
+        return 7;
+      }
+      if(curl_mime_type(part, type)) {
+        warnf(config->global, "curl_mime_type failed!\n");
+        Curl_safefree(contents);
+        return 8;
+      }
+    }
+    else if(!name && !strcmp(contp, ")") && !literal_value) {
+      /* Ending a mutipart. */
+      if(*mimecurrent == *mimepost) {
+        warnf(config->global, "no multipart to terminate!\n");
+        Curl_safefree(contents);
+        return 9;
+        }
+      *mimecurrent = (*mimecurrent)->parent->parent;
+    }
+    else if('@' == contp[0] && !literal_value) {
 
-      struct multi_files *multi_start = NULL;
-      struct multi_files *multi_current = NULL;
+      /* we use the @-letter to indicate file name(s) */
 
-      char *ptr = contp;
-      char *end = ptr + strlen(ptr);
+      curl_mime *subparts = NULL;
 
       do {
         /* since this was a file, it may have a content-type specifier
            at the end too, or a filename. Or both. */
-        char *filename = NULL;
-        char *word_end;
-        bool semicolon;
-
-        type = NULL;
-
-        ++ptr;
-        contp = get_param_word(&ptr, &word_end);
-        semicolon = (';' == *ptr) ? TRUE : FALSE;
-        *word_end = '\0'; /* terminate the contp */
-
-        /* have other content, continue parse */
-        while(semicolon) {
-          /* have type or filename field */
-          ++ptr;
-          while(*ptr && (ISSPACE(*ptr)))
-            ++ptr;
-
-          if(checkprefix("type=", ptr)) {
-            /* set type pointer */
-            type = &ptr[5];
-
-            /* verify that this is a fine type specifier */
-            if(2 != sscanf(type, "%127[^/]/%127[^;,\n]",
-                           type_major, type_minor)) {
-              warnf(config->global,
-                    "Illegally formatted content-type field!\n");
-              Curl_safefree(contents);
-              FreeMultiInfo(&multi_start, &multi_current);
-              return 2; /* illegal content-type syntax! */
-            }
-
-            /* now point beyond the content-type specifier */
-            sep = type + strlen(type_major)+strlen(type_minor)+1;
-
-            /* there's a semicolon following - we check if it is a filename
-               specified and if not we simply assume that it is text that
-               the user wants included in the type and include that too up
-               to the next sep. */
-            ptr = sep;
-            if(*sep==';') {
-              if(!checkprefix(";filename=", sep)) {
-                ptr = sep + 1;
-                (void)get_param_word(&ptr, &sep);
-                semicolon = (';' == *ptr) ? TRUE : FALSE;
-              }
-            }
-            else
-              semicolon = FALSE;
+        ++contp;
+        sep = get_param_part(config, &contp,
+                             &data, &type, &filename, &encoder, &headers);
+        if(sep < 0) {
+          if(subparts != *mimecurrent)
+            curl_mime_free(subparts);
+          Curl_safefree(contents);
+          return 10;
+        }
 
-            if(*sep)
-              *sep = '\0'; /* zero terminate type string */
-          }
-          else if(checkprefix("filename=", ptr)) {
-            ptr += 9;
-            filename = get_param_word(&ptr, &word_end);
-            semicolon = (';' == *ptr) ? TRUE : FALSE;
-            *word_end = '\0';
-          }
+        /* now contp point to comma or string end.
+           If more files to come, make sure we have multiparts. */
+        if(!subparts) {
+          if(sep != ',')    /* If there is a single file. */
+            subparts = *mimecurrent;
           else {
-            /* unknown prefix, skip to next block */
-            char *unknown = NULL;
-            unknown = get_param_word(&ptr, &word_end);
-            semicolon = (';' == *ptr) ? TRUE : FALSE;
-            if(*unknown) {
-              *word_end = '\0';
-              warnf(config->global, "skip unknown form field: %s\n", unknown);
+            subparts = curl_mime_init(config->easy);
+            if(!subparts) {
+              warnf(config->global, "curl_mime_init failed!\n");
+              curl_slist_free_all(headers);
+              Curl_safefree(contents);
+              return 11;
             }
           }
         }
-        /* now ptr point to comma or string end */
 
+        /* Allocate a part for that file. */
+        part = curl_mime_addpart(subparts);
+        if(!part) {
+          warnf(config->global, "curl_mime_addpart failed!\n");
+          if(subparts != *mimecurrent)
+            curl_mime_free(subparts);
+          curl_slist_free_all(headers);
+          Curl_safefree(contents);
+          return 12;
+        }
 
-        /* if type == NULL curl_formadd takes care of the problem */
+        /* Set part headers. */
+        if(curl_mime_headers(part, headers, 1)) {
+          warnf(config->global, "curl_mime_headers failed!\n");
+          if(subparts != *mimecurrent)
+            curl_mime_free(subparts);
+          curl_slist_free_all(headers);
+          Curl_safefree(contents);
+          return 13;
+        }
 
-        if(*contp && !AddMultiFiles(contp, type, filename, &multi_start,
-                          &multi_current)) {
-          warnf(config->global, "Error building form post!\n");
+        /* Setup file in part. */
+        res = file_or_stdin(part, data);
+        if(res) {
+          warnf(config->global, "setting file %s  failed!\n", data);
+          if(res != CURLE_READ_ERROR) {
+            if(subparts != *mimecurrent)
+              curl_mime_free(subparts);
+            Curl_safefree(contents);
+            return 14;
+          }
+        }
+        if(filename && curl_mime_filename(part, filename)) {
+          warnf(config->global, "curl_mime_filename failed!\n");
+          if(subparts != *mimecurrent)
+            curl_mime_free(subparts);
           Curl_safefree(contents);
-          FreeMultiInfo(&multi_start, &multi_current);
-          return 3;
+          return 15;
+        }
+        if(curl_mime_type(part, type)) {
+          warnf(config->global, "curl_mime_type failed!\n");
+          if(subparts != *mimecurrent)
+            curl_mime_free(subparts);
+          Curl_safefree(contents);
+          return 16;
+        }
+        if(curl_mime_encoder(part, encoder)) {
+          warnf(config->global, "curl_mime_encoder failed!\n");
+          if(subparts != *mimecurrent)
+            curl_mime_free(subparts);
+          Curl_safefree(contents);
+          return 17;
         }
 
-        /* *ptr could be '\0', so we just check with the string end */
-      } while(ptr < end); /* loop if there's another file name */
+        /* *contp could be '\0', so we just check with the delimiter */
+      } while(sep); /* loop if there's another file name */
 
       /* now we add the multiple files section */
-      if(multi_start) {
-        struct curl_forms *forms = NULL;
-        struct multi_files *start = multi_start;
-        unsigned int i, count = 0;
-        while(start) {
-          start = start->next;
-          ++count;
-        }
-        forms = malloc((count+1)*sizeof(struct curl_forms));
-        if(!forms) {
-          fprintf(config->global->errors, "Error building form post!\n");
-          Curl_safefree(contents);
-          FreeMultiInfo(&multi_start, &multi_current);
-          return 4;
-        }
-        for(i = 0, start = multi_start; i < count; ++i, start = start->next) {
-          forms[i].option = start->form.option;
-          forms[i].value = start->form.value;
-        }
-        forms[count].option = CURLFORM_END;
-        FreeMultiInfo(&multi_start, &multi_current);
-        if(curl_formadd(httppost, last_post,
-                        CURLFORM_COPYNAME, name,
-                        CURLFORM_ARRAY, forms, CURLFORM_END) != 0) {
-          warnf(config->global, "curl_formadd failed!\n");
-          Curl_safefree(forms);
+      if(subparts != *mimecurrent) {
+        part = curl_mime_addpart(*mimecurrent);
+        if(!part) {
+          warnf(config->global, "curl_mime_addpart failed!\n");
+          curl_mime_free(subparts);
           Curl_safefree(contents);
-          return 5;
+          return 18;
+        }
+        if(curl_mime_subparts(part, subparts)) {
+          warnf(config->global, "curl_mime_subparts failed!\n");
+          curl_mime_free(subparts);
+          Curl_safefree(contents);
+          return 19;
         }
-        Curl_safefree(forms);
       }
     }
     else {
-      struct curl_forms info[4];
-      int i = 0;
-      char *ct = literal_value ? NULL : strstr(contp, ";type=");
-
-      info[i].option = CURLFORM_COPYNAME;
-      info[i].value = name;
-      i++;
-
-      if(ct) {
-        info[i].option = CURLFORM_CONTENTTYPE;
-        info[i].value = &ct[6];
-        i++;
-        ct[0] = '\0'; /* zero terminate here */
-      }
-
-      if(contp[0]=='<' && !literal_value) {
-        info[i].option = CURLFORM_FILECONTENT;
-        info[i].value = contp+1;
-        i++;
-        info[i].option = CURLFORM_END;
-
-        if(curl_formadd(httppost, last_post,
-                        CURLFORM_ARRAY, info, CURLFORM_END) != 0) {
-          warnf(config->global, "curl_formadd failed, possibly the file %s is "
-                "bad!\n", contp + 1);
+        /* Allocate a mime part. */
+        part = curl_mime_addpart(*mimecurrent);
+        if(!part) {
+          warnf(config->global, "curl_mime_addpart failed!\n");
           Curl_safefree(contents);
-          return 6;
+          return 20;
+        }
+
+      if(*contp == '<' && !literal_value) {
+        ++contp;
+        sep = get_param_part(config, &contp,
+                             &data, &type, &filename, &encoder, &headers);
+        if(sep < 0) {
+          Curl_safefree(contents);
+          return 21;
+        }
+
+        /* Set part headers. */
+        if(curl_mime_headers(part, headers, 1)) {
+          warnf(config->global, "curl_mime_headers failed!\n");
+          curl_slist_free_all(headers);
+          Curl_safefree(contents);
+          return 22;
+        }
+
+        /* Setup file in part. */
+        res = file_or_stdin(part, data);
+        if(res) {
+          warnf(config->global, "setting file %s failed!\n", data);
+          if(res != CURLE_READ_ERROR) {
+            Curl_safefree(contents);
+            return 23;
+          }
         }
       }
       else {
+        if(literal_value)
+          data = contp;
+        else {
+          sep = get_param_part(config, &contp,
+                               &data, &type, &filename, &encoder, &headers);
+          if(sep < 0) {
+            Curl_safefree(contents);
+            return 24;
+          }
+        }
+
+        /* Set part headers. */
+        if(curl_mime_headers(part, headers, 1)) {
+          warnf(config->global, "curl_mime_headers failed!\n");
+          curl_slist_free_all(headers);
+          Curl_safefree(contents);
+          return 25;
+        }
+
 #ifdef CURL_DOES_CONVERSIONS
-        if(convert_to_network(contp, strlen(contp))) {
+        if(convert_to_network(data, strlen(data))) {
           warnf(config->global, "curl_formadd failed!\n");
           Curl_safefree(contents);
-          return 7;
+          return 26;
         }
 #endif
-        info[i].option = CURLFORM_COPYCONTENTS;
-        info[i].value = contp;
-        i++;
-        info[i].option = CURLFORM_END;
-        if(curl_formadd(httppost, last_post,
-                        CURLFORM_ARRAY, info, CURLFORM_END) != 0) {
-          warnf(config->global, "curl_formadd failed!\n");
+
+        if(curl_mime_data(part, data, CURL_ZERO_TERMINATED)) {
+          warnf(config->global, "curl_mime_data failed!\n");
           Curl_safefree(contents);
-          return 8;
+          return 27;
         }
       }
+
+      if(curl_mime_filename(part, filename)) {
+        warnf(config->global, "curl_mime_filename failed!\n");
+        Curl_safefree(contents);
+        return 28;
+      }
+      if(curl_mime_type(part, type)) {
+        warnf(config->global, "curl_mime_type failed!\n");
+        Curl_safefree(contents);
+        return 29;
+      }
+      if(curl_mime_encoder(part, encoder)) {
+        warnf(config->global, "curl_mime_encoder failed!\n");
+        Curl_safefree(contents);
+        return 30;
+      }
+
+      if(sep) {
+        *contp = (char) sep;
+        warnf(config->global,
+              "garbage at end of field specification: %s\n", contp);
+      }
     }
 
+    /* Set part name. */
+    if(name && curl_mime_name(part, name)) {
+      warnf(config->global, "curl_mime_name failed!\n");
+      Curl_safefree(contents);
+      return 31;
+    }
   }
   else {
     warnf(config->global, "Illegally formatted input field!\n");
-    return 1;
+    Curl_safefree(contents);
+    return 32;
   }
   Curl_safefree(contents);
   return 0;
 }
