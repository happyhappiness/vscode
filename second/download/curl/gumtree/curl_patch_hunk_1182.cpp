     infop->length++; /* we are now one byte larger */
     return output; /* fputc() returns like this on success */
   }
   return -1;
 }
 
-int msnprintf(char *buffer, size_t maxlength, const char *format, ...)
+int curl_msnprintf(char *buffer, size_t maxlength, const char *format, ...)
 {
   va_list ap_save; /* argument pointer */
   int retcode;
   struct nsprintf info;
 
   info.buffer = buffer;
