     return inl;
 }
 
 static long bio_filter_out_ctrl(BIO *bio, int cmd, long num, void *ptr)
 {
     long ret = 1;
-    bio_filter_out_ctx_t *outctx = (bio_filter_out_ctx_t *)(bio->ptr);
+    bio_filter_out_ctx_t *outctx = (bio_filter_out_ctx_t *)BIO_get_data(bio);
 
     switch (cmd) {
     case BIO_CTRL_RESET:
     case BIO_CTRL_EOF:
     case BIO_C_SET_BUF_MEM_EOF_RETURN:
         ap_log_cerror(APLOG_MARK, APLOG_TRACE4, 0, outctx->c,
