@@ -1028,7 +1028,6 @@ static int alloc_addbyter(int output, FILE *data)
   infop->len++;
 
   return output; /* fputc() returns like this on success */
-
 }
 
 char *curl_maprintf(const char *format, ...)
@@ -1044,12 +1043,17 @@ char *curl_maprintf(const char *format, ...)
   va_start(ap_save, format);
   retcode = dprintf_formatf(&info, alloc_addbyter, format, ap_save);
   va_end(ap_save);
-  if(info.len) {
+  if(-1 == retcode) {
+    if(info.alloc)
+      free(info.buffer);
+    return NULL;
+  }
+  if(info.alloc) {
     info.buffer[info.len] = 0; /* we terminate this with a zero byte */
     return info.buffer;
   }
   else
-    return NULL;
+    return strdup("");
 }
 
 char *curl_mvaprintf(const char *format, va_list ap_save)
@@ -1062,13 +1066,18 @@ char *curl_mvaprintf(const char *format, va_list ap_save)
   info.alloc = 0;
 
   retcode = dprintf_formatf(&info, alloc_addbyter, format, ap_save);
-  info.buffer[info.len] = 0; /* we terminate this with a zero byte */
-  if(info.len) {
+  if(-1 == retcode) {
+    if(info.alloc)
+      free(info.buffer);
+    return NULL;
+  }
+
+  if(info.alloc) {
     info.buffer[info.len] = 0; /* we terminate this with a zero byte */
     return info.buffer;
   }
   else
-    return NULL;
+    return strdup("");
 }
 
 static int storebuffer(int output, FILE *data)