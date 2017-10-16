 static size_t my_fwrite(void *buffer, size_t sz, size_t nmemb, void *stream)
 {
   size_t rc;
   struct OutStruct *out=(struct OutStruct *)stream;
   struct Configurable *config = out->config;
 
-  if(out && !out->stream) {
+  if(!out->stream) {
     /* open file for writing */
     out->stream=fopen(out->filename, "wb");
     if(!out->stream) {
       warnf(config, "Failed to create the file %s\n", out->filename);
       /*
        * Once that libcurl has called back my_fwrite() the returned value
