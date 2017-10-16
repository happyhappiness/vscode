     if(!out)
       warnf(config, "Failed to open %s to write libcurl code!\n", o);
     else {
       int i;
       const char *c;
 
-      for(i=0; (c = srchead[i]); i++) {
-        if(!memcmp((char *)c, "[m]", 3)) {
-#if defined(_FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS > 32)
-          fprintf(out, "#define _FILE_OFFSET_BITS %d "
-                  "/* for pre libcurl 7.19.0 curl_off_t magic */\n",
-                  _FILE_OFFSET_BITS);
-#endif
-        }
-        else
-          fprintf(out, "%s\n", c);
-      }
+      for(i=0; ((c = srchead[i]) != '\0'); i++)
+        fprintf(out, "%s\n", c);
 
       ptr = easycode;
       while(ptr) {
         fprintf(out, "  %s\n", ptr->data);
         ptr = ptr->next;
       }
