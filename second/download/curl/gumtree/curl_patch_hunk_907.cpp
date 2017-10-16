       if(!outs->stream || outs->s_isreg || outs->fopened)
         check_fails = TRUE;
       if(outs->alloc_filename || outs->is_cd_filename || outs->init)
         check_fails = TRUE;
     }
     if(check_fails) {
-      warnf(config, "Invalid output struct data for write callback\n");
+      warnf(config->global, "Invalid output struct data for write callback\n");
       return failure;
     }
   }
 #endif
 
-  if(!outs->stream) {
-    FILE *file;
-
-    if(!outs->filename || !*outs->filename) {
-      warnf(config, "Remote filename has no length!\n");
-      return failure;
-    }
-
-    if(outs->is_cd_filename) {
-      /* don't overwrite existing files */
-      file = fopen(outs->filename, "rb");
-      if(file) {
-        fclose(file);
-        warnf(config, "Refusing to overwrite %s: %s\n", outs->filename,
-              strerror(EEXIST));
-        return failure;
-      }
-    }
-
-    /* open file for writing */
-    file = fopen(outs->filename, "wb");
-    if(!file) {
-      warnf(config, "Failed to create the file %s: %s\n", outs->filename,
-            strerror(errno));
-      return failure;
-    }
-    outs->s_isreg = TRUE;
-    outs->fopened = TRUE;
-    outs->stream = file;
-    outs->bytes = 0;
-    outs->init = 0;
-  }
+  if(!outs->stream && !tool_create_output_file(outs))
+    return failure;
 
   rc = fwrite(buffer, sz, nmemb, outs->stream);
 
   if((sz * nmemb) == rc)
     /* we added this amount of data to the output */
     outs->bytes += (sz * nmemb);
