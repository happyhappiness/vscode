   infop->len++;
 
   return output; /* fputc() returns like this on success */
 
 }
 
-char *maprintf(const char *format, ...)
+char *curl_maprintf(const char *format, ...)
 {
   va_list ap_save; /* argument pointer */
   int retcode;
   struct asprintf info;
 
   info.buffer = NULL;
