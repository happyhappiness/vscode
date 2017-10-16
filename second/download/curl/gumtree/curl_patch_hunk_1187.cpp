   
   return CURLE_OK;
 }
 
 
 /*
- * add_buffer_init() returns a fine buffer struct
+ * Internal read-from-socket function. This is meant to deal with plain
+ * sockets, SSL sockets and kerberos sockets.
  */
-send_buffer *add_buffer_init(void)
+CURLcode Curl_read(struct connectdata *conn, int sockfd,
+                   char *buf, size_t buffersize,
+                   size_t *n)
 {
-  send_buffer *blonk;
-  blonk=(send_buffer *)malloc(sizeof(send_buffer));
-  if(blonk) {
-    memset(blonk, 0, sizeof(send_buffer));
-    return blonk;
-  }
-  return NULL; /* failed, go home */
-}
+  struct UrlData *data = conn->data;
+  size_t nread;
 
-/*
- * add_buffer_send() sends a buffer and frees all associated memory.
- */
-size_t add_buffer_send(int sockfd, struct connectdata *conn, send_buffer *in)
-{
-  size_t amount;
-  if(conn->data->bits.verbose) {
-    fputs("> ", conn->data->err);
-    /* this data _may_ contain binary stuff */
-    fwrite(in->buffer, in->size_used, 1, conn->data->err);
+#ifdef USE_SSLEAY
+  if (data->ssl.use) {
+    int loop=100; /* just a precaution to never loop endlessly */
+    while(loop--) {
+      nread = SSL_read(data->ssl.handle, buf, buffersize);
+      if((-1 != nread) ||
+         (SSL_ERROR_WANT_READ != SSL_get_error(data->ssl.handle, nread) ))
+        break;
+    }
   }
-
-  amount = ssend(sockfd, conn, in->buffer, in->size_used);
-
-  if(in->buffer)
-    free(in->buffer);
-  free(in);
-
-  return amount;
-}
-
-
-/* 
- * add_bufferf() builds a buffer from the formatted input
- */
-CURLcode add_bufferf(send_buffer *in, char *fmt, ...)
-{
-  CURLcode result = CURLE_OUT_OF_MEMORY;
-  char *s;
-  va_list ap;
-  va_start(ap, fmt);
-  s = mvaprintf(fmt, ap); /* this allocs a new string to append */
-  va_end(ap);
-
-  if(s) {
-    result = add_buffer(in, s, strlen(s));
-    free(s);
+  else {
+#endif
+#ifdef KRB4
+    if(conn->sec_complete)
+      nread = sec_read(conn, sockfd, buf, buffersize);
+    else
+#endif
+      nread = sread (sockfd, buf, buffersize);
+#ifdef USE_SSLEAY
   }
-  return result;
+#endif /* USE_SSLEAY */
+  *n = nread;
+  return CURLE_OK;
 }
 
 /*
- * add_buffer() appends a memory chunk to the existing one
+ * The public read function reads from the 'sockfd' file descriptor only.
+ * Use the Curl_read() internally when you want to specify fd.
  */
-CURLcode add_buffer(send_buffer *in, void *inptr, size_t size)
-{
-  char *new_rb;
-  int new_size;
-
-  if(size > 0) {
-    if(!in->buffer ||
-       ((in->size_used + size) > (in->size_max - 1))) {
-      new_size = (in->size_used+size)*2;
-      if(in->buffer)
-        /* we have a buffer, enlarge the existing one */
-        new_rb = (char *)realloc(in->buffer, new_size);
-      else
-        /* create a new buffer */
-        new_rb = (char *)malloc(new_size);
 
-      if(!new_rb)
-        return CURLE_OUT_OF_MEMORY;
+CURLcode curl_read(CURLconnect *c_conn, char *buf, size_t buffersize,
+                   size_t *n)
+{
+  struct connectdata *conn = (struct connectdata *)c_conn;
 
-      in->buffer = new_rb;
-      in->size_max = new_size;
-    }
-    memcpy(&in->buffer[in->size_used], inptr, size);
-      
-    in->size_used += size;
-  }
+  if(!n || !conn || (conn->handle != STRUCT_CONNECT))
+    return CURLE_FAILED_INIT;
 
-  return CURLE_OK;
+  return Curl_read(conn, conn->sockfd, buf, buffersize, n);
 }
 
