@@ -149,7 +149,7 @@ static void pre_receive_plain(struct connectdata *conn, int num)
       /* Have some incoming data */
       if(!psnd->buffer) {
         /* Use buffer double default size for intermediate buffer */
-        psnd->allocated_size = 2 * BUFSIZE;
+        psnd->allocated_size = 2 * conn->data->set.buffer_size;
         psnd->buffer = malloc(psnd->allocated_size);
         psnd->recv_size = 0;
         psnd->recv_processed = 0;
@@ -243,21 +243,20 @@ void Curl_failf(struct Curl_easy *data, const char *fmt, ...)
 {
   va_list ap;
   size_t len;
+  char error[CURL_ERROR_SIZE + 2];
   va_start(ap, fmt);
 
-  vsnprintf(data->state.buffer, BUFSIZE, fmt, ap);
+  vsnprintf(error, CURL_ERROR_SIZE, fmt, ap);
+  len = strlen(error);
 
   if(data->set.errorbuffer && !data->state.errorbuf) {
-    snprintf(data->set.errorbuffer, CURL_ERROR_SIZE, "%s", data->state.buffer);
+    strcpy(data->set.errorbuffer, error);
     data->state.errorbuf = TRUE; /* wrote error string */
   }
   if(data->set.verbose) {
-    len = strlen(data->state.buffer);
-    if(len < BUFSIZE - 1) {
-      data->state.buffer[len] = '\n';
-      data->state.buffer[++len] = '\0';
-    }
-    Curl_debug(data, CURLINFO_TEXT, data->state.buffer, len, NULL);
+    error[len] = '\n';
+    error[++len] = '\0';
+    Curl_debug(data, CURLINFO_TEXT, error, len, NULL);
   }
 
   va_end(ap);
@@ -694,9 +693,10 @@ CURLcode Curl_read(struct connectdata *conn, /* connection data */
   ssize_t nread = 0;
   size_t bytesfromsocket = 0;
   char *buffertofill = NULL;
+  struct Curl_easy *data = conn->data;
 
   /* if HTTP/1 pipelining is both wanted and possible */
-  bool pipelining = Curl_pipeline_wanted(conn->data->multi, CURLPIPE_HTTP1) &&
+  bool pipelining = Curl_pipeline_wanted(data->multi, CURLPIPE_HTTP1) &&
     (conn->bundle->multiuse == BUNDLE_PIPELINING);
 
   /* Set 'num' to 0 or 1, depending on which socket that has been sent here.
@@ -722,13 +722,11 @@ CURLcode Curl_read(struct connectdata *conn, /* connection data */
     }
     /* If we come here, it means that there is no data to read from the buffer,
      * so we read from the socket */
-    bytesfromsocket = CURLMIN(sizerequested, BUFSIZE * sizeof(char));
+    bytesfromsocket = CURLMIN(sizerequested, MASTERBUF_SIZE);
     buffertofill = conn->master_buffer;
   }
   else {
-    bytesfromsocket = CURLMIN((long)sizerequested,
-                              conn->data->set.buffer_size ?
-                              conn->data->set.buffer_size : BUFSIZE);
+    bytesfromsocket = CURLMIN(sizerequested, (size_t)data->set.buffer_size);
     buffertofill = buf;
   }
 
@@ -753,21 +751,19 @@ static int showit(struct Curl_easy *data, curl_infotype type,
 {
   static const char s_infotype[CURLINFO_END][3] = {
     "* ", "< ", "> ", "{ ", "} ", "{ ", "} " };
+  int rc = 0;
 
 #ifdef CURL_DOES_CONVERSIONS
-  char buf[BUFSIZE+1];
+  char *buf = NULL;
   size_t conv_size = 0;
 
   switch(type) {
   case CURLINFO_HEADER_OUT:
-    /* assume output headers are ASCII */
-    /* copy the data into my buffer so the original is unchanged */
-    if(size > BUFSIZE) {
-      size = BUFSIZE; /* truncate if necessary */
-      buf[BUFSIZE] = '\0';
-    }
+    buf = Curl_memdup(ptr, size);
+    if(!buf)
+      return 1;
     conv_size = size;
-    memcpy(buf, ptr, size);
+
     /* Special processing is needed for this block if it
      * contains both headers and data (separated by CRLFCRLF).
      * We want to convert just the headers, leaving the data as-is.
@@ -795,26 +791,29 @@ static int showit(struct Curl_easy *data, curl_infotype type,
 #endif /* CURL_DOES_CONVERSIONS */
 
   if(data->set.fdebug)
-    return (*data->set.fdebug)(data, type, ptr, size,
-                               data->set.debugdata);
-
-  switch(type) {
-  case CURLINFO_TEXT:
-  case CURLINFO_HEADER_OUT:
-  case CURLINFO_HEADER_IN:
-    fwrite(s_infotype[type], 2, 1, data->set.err);
-    fwrite(ptr, size, 1, data->set.err);
+    rc = (*data->set.fdebug)(data, type, ptr, size, data->set.debugdata);
+  else {
+    switch(type) {
+    case CURLINFO_TEXT:
+    case CURLINFO_HEADER_OUT:
+    case CURLINFO_HEADER_IN:
+      fwrite(s_infotype[type], 2, 1, data->set.err);
+      fwrite(ptr, size, 1, data->set.err);
 #ifdef CURL_DOES_CONVERSIONS
-    if(size != conv_size) {
-      /* we had untranslated data so we need an explicit newline */
-      fwrite("\n", 1, 1, data->set.err);
-    }
+      if(size != conv_size) {
+        /* we had untranslated data so we need an explicit newline */
+        fwrite("\n", 1, 1, data->set.err);
+      }
 #endif
-    break;
-  default: /* nada */
-    break;
+      break;
+    default: /* nada */
+      break;
+    }
   }
-  return 0;
+#ifdef CURL_DOES_CONVERSIONS
+  free(buf);
+#endif
+  return rc;
 }
 
 int Curl_debug(struct Curl_easy *data, curl_infotype type,