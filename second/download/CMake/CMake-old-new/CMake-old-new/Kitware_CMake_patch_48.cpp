@@ -1096,8 +1096,7 @@ char *curl_maprintf(const char *format, ...)
     info.buffer[info.len] = 0; /* we terminate this with a zero byte */
     return info.buffer;
   }
-  else
-    return strdup("");
+  return strdup("");
 }
 
 char *curl_mvaprintf(const char *format, va_list ap_save)
@@ -1121,8 +1120,7 @@ char *curl_mvaprintf(const char *format, va_list ap_save)
     info.buffer[info.len] = 0; /* we terminate this with a zero byte */
     return info.buffer;
   }
-  else
-    return strdup("");
+  return strdup("");
 }
 
 static int storebuffer(int output, FILE *data)