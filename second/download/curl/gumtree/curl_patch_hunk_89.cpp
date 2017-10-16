 }
 
 /* fputc() look-alike */
 static int alloc_addbyter(int output, FILE *data)
 {
   struct asprintf *infop=(struct asprintf *)data;
+  unsigned char outc = (unsigned char)output;
  
   if(!infop->buffer) {
     infop->buffer=(char *)malloc(32);
-    if(!infop->buffer)
+    if(!infop->buffer) {
+      infop->fail = TRUE;
       return -1; /* fail */
+    }
     infop->alloc = 32;
     infop->len =0;
   }
   else if(infop->len+1 >= infop->alloc) {
     char *newptr;
 
     newptr = (char *)realloc(infop->buffer, infop->alloc*2);
 
     if(!newptr) {
+      infop->fail = TRUE;
       return -1;
     }
     infop->buffer = newptr;
     infop->alloc *= 2;
   }
 
-  infop->buffer[ infop->len ] = (char)output;
+  infop->buffer[ infop->len ] = outc;
 
   infop->len++;
 
-  return output; /* fputc() returns like this on success */
+  return outc; /* fputc() returns like this on success */
 }
 
 char *curl_maprintf(const char *format, ...)
 {
   va_list ap_save; /* argument pointer */
   int retcode;
   struct asprintf info;
 
   info.buffer = NULL;
   info.len = 0;
   info.alloc = 0;
+  info.fail = FALSE;
 
   va_start(ap_save, format);
   retcode = dprintf_formatf(&info, alloc_addbyter, format, ap_save);
   va_end(ap_save);
-  if(-1 == retcode) {
+  if((-1 == retcode) || info.fail) {
     if(info.alloc)
       free(info.buffer);
     return NULL;
   }
   if(info.alloc) {
     info.buffer[info.len] = 0; /* we terminate this with a zero byte */
