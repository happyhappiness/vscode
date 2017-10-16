 void Curl_failf(struct UrlData *data, char *fmt, ...)
 {
   va_list ap;
   va_start(ap, fmt);
   if(data->errorbuffer)
     vsnprintf(data->errorbuffer, CURL_ERROR_SIZE, fmt, ap);
-  else if(!data->bits.mute) {
-    /* no errorbuffer receives this, write to data->err instead */
-    vfprintf(data->err, fmt, ap);
-    fprintf(data->err, "\n");
-  }
   va_end(ap);
 }
 
 /* Curl_sendf() sends formated data to the server */
 size_t Curl_sendf(int sockfd, struct connectdata *conn,
                   char *fmt, ...)
