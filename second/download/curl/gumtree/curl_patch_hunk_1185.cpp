 #ifdef MALLOCDEBUG
 #include "memdebug.h"
 #endif
 
 /* infof() is for info message along the way */
 
-void infof(struct UrlData *data, char *fmt, ...)
+void Curl_infof(struct UrlData *data, char *fmt, ...)
 {
   va_list ap;
   if(data->bits.verbose) {
     va_start(ap, fmt);
     fputs("* ", data->err);
     vfprintf(data->err, fmt, ap);
