    * it does not match then it fails with CURLE_WRITE_ERROR. So at this
    * point returning a value different from sz*nmemb indicates failure.
    */
   const size_t err_rc = (sz * nmemb) ? 0 : 1;
 
   if(!out->stream) {
+    out->bytes = 0; /* nothing written yet */
     if (!out->filename) {
       warnf(config, "Remote filename has no length!\n");
       return err_rc; /* Failure */
     }
 
     if (config->content_disposition) {
