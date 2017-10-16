   select(0, NULL,  NULL, NULL, &timeout);
 #endif
 
 #endif
 }
 
-struct OutStruct {
-  char *filename;
-  FILE *stream;
-  struct Configurable *config;
-  curl_off_t bytes; /* amount written so far */
-  curl_off_t init;  /* original size (non-zero when appending) */
-};
-
-static int my_fwrite(void *buffer, size_t sz, size_t nmemb, void *stream)
+static size_t my_fwrite(void *buffer, size_t sz, size_t nmemb, void *stream)
 {
-  int rc;
+  size_t rc;
   struct OutStruct *out=(struct OutStruct *)stream;
   struct Configurable *config = out->config;
-  curl_off_t size = (curl_off_t)(sz * nmemb); /* typecast to prevent
-                                                 warnings when converting from
-                                                 unsigned to signed */
+
   if(out && !out->stream) {
     /* open file for writing */
     out->stream=fopen(out->filename, "wb");
     if(!out->stream) {
       warnf(config, "Failed to create the file %s\n", out->filename);
-      return -1; /* failure */
-    }
-  }
-
-  if(config->recvpersecond) {
-    /*
-     * We know when we received data the previous time. We know how much data
-     * we get now. Make sure that this is not faster than we are told to run.
-     * If we're faster, sleep a while *before* doing the fwrite() here.
-     */
-
-    struct timeval now;
-    long timediff;
-    long sleep_time;
-
-    static curl_off_t addit = 0;
-
-    now = curlx_tvnow();
-    timediff = curlx_tvdiff(now, config->lastrecvtime); /* milliseconds */
-
-    if((config->recvpersecond > CURL_MAX_WRITE_SIZE) && (timediff < 100) ) {
-      /* If we allow a rather speedy transfer, add this amount for later
-       * checking. Also, do not modify the lastrecvtime as we will use a
-       * longer scope due to this addition.  We wait for at least 100 ms to
-       * pass to get better values to do better math for the sleep. */
-      addit += size;
-    }
-    else {
-      size += addit; /* add up the possibly added bonus rounds from the
-                        zero timediff calls */
-      addit = 0; /* clear the addition pool */
-
-      if( size*1000 > config->recvpersecond*timediff) {
-        /* figure out how many milliseconds to rest */
-        sleep_time = (long)(size*1000/config->recvpersecond - timediff);
-
-        /*
-         * Make sure we don't sleep for so long that we trigger the speed
-         * limit.  This won't limit the bandwidth quite the way we've been
-         * asked to, but at least the transfer has a chance.
-         */
-        if (config->low_speed_time > 0)
-          sleep_time = MIN(sleep_time,(config->low_speed_time * 1000) / 2);
-
-        if(sleep_time > 0) {
-          go_sleep(sleep_time);
-          now = curlx_tvnow();
-        }
-      }
-      config->lastrecvtime = now;
+      /*
+       * Once that libcurl has called back my_fwrite() the returned value
+       * is checked against the amount that was intended to be written, if
+       * it does not match then it fails with CURLE_WRITE_ERROR. So at this
+       * point returning a value different from sz*nmemb indicates failure.
+       */
+      rc = (0 == (sz * nmemb)) ? 1 : 0;
+      return rc; /* failure */
     }
   }
 
   rc = fwrite(buffer, sz, nmemb, out->stream);
 
-  if((int)(sz * nmemb) == rc) {
+  if((sz * nmemb) == rc) {
     /* we added this amount of data to the output */
     out->bytes += (sz * nmemb);
   }
 
   if(config->nobuffer)
     /* disable output buffering */
