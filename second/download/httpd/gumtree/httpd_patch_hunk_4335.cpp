 } rl_state_e;
 
 typedef struct rl_ctx_t
 {
     int speed;
     int chunk_size;
+    int burst;
     rl_state_e state;
     apr_bucket_brigade *tmpbb;
     apr_bucket_brigade *holdingbb;
 } rl_ctx_t;
 
-#if 0
+#if defined(RLFDEBUG)
 static void brigade_dump(request_rec *r, apr_bucket_brigade *bb)
 {
     apr_bucket *e;
     int i = 0;
 
     for (e = APR_BRIGADE_FIRST(bb);
          e != APR_BRIGADE_SENTINEL(bb); e = APR_BUCKET_NEXT(e), i++) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(03193)
                       "brigade: [%d] %s", i, e->type->name);
 
     }
 }
-#endif
+#endif /* RLFDEBUG */
 
 static apr_status_t
 rate_limit_filter(ap_filter_t *f, apr_bucket_brigade *input_bb)
 {
     apr_status_t rv = APR_SUCCESS;
     rl_ctx_t *ctx = f->ctx;
