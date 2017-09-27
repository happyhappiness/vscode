     return -1;
 }
 
 static int bio_filter_out_write(BIO *bio, const char *in, int inl)
 {
     bio_filter_out_ctx_t *outctx = (bio_filter_out_ctx_t *)(bio->ptr);
-    
+    apr_bucket *e;
+
     /* Abort early if the client has initiated a renegotiation. */
     if (outctx->filter_ctx->config->reneg_state == RENEG_ABORT) {
         outctx->rc = APR_ECONNABORTED;
         return -1;
     }
-    
+
     /* when handshaking we'll have a small number of bytes.
      * max size SSL will pass us here is about 16k.
      * (16413 bytes to be exact)
      */
     BIO_clear_retry_flags(bio);
 
-    if (!outctx->length && (inl + outctx->blen < sizeof(outctx->buffer)) &&
-        !outctx->filter_ctx->nobuffer) {
-        /* the first two SSL_writes (of 1024 and 261 bytes)
-         * need to be in the same packet (vec[0].iov_base)
-         */
-        /* XXX: could use apr_brigade_write() to make code look cleaner
-         * but this way we avoid the malloc(APR_BUCKET_BUFF_SIZE)
-         * and free() of it later
-         */
-        memcpy(&outctx->buffer[outctx->blen], in, inl);
-        outctx->blen += inl;
-    }
-    else {
-        /* pass along the encrypted data
-         * need to flush since we're using SSL's malloc-ed buffer
-         * which will be overwritten once we leave here
-         */
-        apr_bucket *bucket = apr_bucket_transient_create(in, inl,
-                                             outctx->bb->bucket_alloc);
-
-        outctx->length += inl;
-        APR_BRIGADE_INSERT_TAIL(outctx->bb, bucket);
+    /* Use a transient bucket for the output data - any downstream
+     * filter must setaside if necessary. */
+    e = apr_bucket_transient_create(in, inl, outctx->bb->bucket_alloc);
+    APR_BRIGADE_INSERT_TAIL(outctx->bb, e);
 
-        if (bio_filter_out_flush(bio) < 0) {
-            return -1;
-        }
+    if (bio_filter_out_pass(outctx) < 0) {
+        return -1;
     }
 
     return inl;
 }
 
 static long bio_filter_out_ctrl(BIO *bio, int cmd, long num, void *ptr)
 {
     long ret = 1;
-    char **pptr;
-
     bio_filter_out_ctx_t *outctx = (bio_filter_out_ctx_t *)(bio->ptr);
 
     switch (cmd) {
-      case BIO_CTRL_RESET:
-        outctx->blen = outctx->length = 0;
-        break;
-      case BIO_CTRL_EOF:
-        ret = (long)((outctx->blen + outctx->length) == 0);
-        break;
-      case BIO_C_SET_BUF_MEM_EOF_RETURN:
-        outctx->blen = outctx->length = (apr_size_t)num;
+    case BIO_CTRL_RESET:
+    case BIO_CTRL_EOF:
+    case BIO_C_SET_BUF_MEM_EOF_RETURN:
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, outctx->c,
+                      "output bio: unhandled control %d", cmd);
+        ret = 0;
         break;
-      case BIO_CTRL_INFO:
-        ret = (long)(outctx->blen + outctx->length);
-        if (ptr) {
-            pptr = (char **)ptr;
-            *pptr = (char *)&(outctx->buffer[0]);
-        }
+    case BIO_CTRL_WPENDING:
+    case BIO_CTRL_PENDING:
+    case BIO_CTRL_INFO:
+        ret = 0;
         break;
-      case BIO_CTRL_GET_CLOSE:
+    case BIO_CTRL_GET_CLOSE:
         ret = (long)bio->shutdown;
         break;
       case BIO_CTRL_SET_CLOSE:
         bio->shutdown = (int)num;
         break;
-      case BIO_CTRL_PENDING:
-        /* _PENDING is interpreted as "pending to read" - since this
-         * is a *write* buffer, return zero. */
-        ret = 0L;
-        break;
-      case BIO_CTRL_WPENDING:
-        /* _WPENDING is interpreted as "pending to write" - return the
-         * number of bytes in ->bb plus buffer. */
-        ret = (long)(outctx->blen + outctx->length);
-        break;
       case BIO_CTRL_FLUSH:
         ret = bio_filter_out_flush(bio);
         break;
       case BIO_CTRL_DUP:
         ret = 1;
         break;
