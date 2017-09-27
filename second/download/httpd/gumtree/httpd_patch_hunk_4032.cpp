                   session->id, (long)size);
     return realloc(p, size);
 }
 
 static h2_session *h2_session_create_int(conn_rec *c,
                                          request_rec *r,
-                                         const h2_config *config, 
+                                         h2_ctx *ctx, 
                                          h2_workers *workers)
 {
     nghttp2_session_callbacks *callbacks = NULL;
     nghttp2_option *options = NULL;
+    uint32_t n;
 
     apr_pool_t *pool = NULL;
-    apr_status_t status = apr_pool_create(&pool, r? r->pool : c->pool);
+    apr_status_t status = apr_pool_create(&pool, c->pool);
     h2_session *session;
     if (status != APR_SUCCESS) {
         return NULL;
     }
+    apr_pool_tag(pool, "h2_session");
 
     session = apr_pcalloc(pool, sizeof(h2_session));
     if (session) {
         int rv;
         nghttp2_mem *mem;
         
         session->id = c->id;
         session->c = c;
         session->r = r;
-        session->config = config;
-        
+        session->s = h2_ctx_server_get(ctx);
         session->pool = pool;
+        session->config = h2_config_sget(session->s);
+        session->workers = workers;
+        
+        session->state = H2_SESSION_ST_INIT;
+        session->local.accepting = 1;
+        session->remote.accepting = 1;
+        
         apr_pool_pre_cleanup_register(pool, session, session_pool_cleanup);
         
-        session->max_stream_count = h2_config_geti(config, H2_CONF_MAX_STREAMS);
-        session->max_stream_mem = h2_config_geti(config, H2_CONF_STREAM_MAX_MEM);
+        session->max_stream_count = h2_config_geti(session->config, 
+                                                   H2_CONF_MAX_STREAMS);
+        session->max_stream_mem = h2_config_geti(session->config, 
+                                                 H2_CONF_STREAM_MAX_MEM);
 
         status = apr_thread_cond_create(&session->iowait, session->pool);
         if (status != APR_SUCCESS) {
             return NULL;
         }
         
-        session->streams = h2_stream_set_create(session->pool, session->max_stream_count);
-        
-        session->workers = workers;
-        session->mplx = h2_mplx_create(c, session->pool, config, workers);
+        session->streams = h2_ihash_create(session->pool,
+                                           offsetof(h2_stream, id));
+        session->mplx = h2_mplx_create(c, session->pool, session->config, 
+                                       session->s->timeout, workers);
         
         h2_mplx_set_consumed_cb(session->mplx, update_window, session);
         
-        h2_conn_io_init(&session->io, c, config, session->pool);
+        /* Install the connection input filter that feeds the session */
+        session->cin = h2_filter_cin_create(session->pool, 
+                                            h2_session_receive, session);
+        ap_add_input_filter("H2_IN", session->cin, r, c);
+
+        h2_conn_io_init(&session->io, c, session->config, session->pool);
         session->bbtmp = apr_brigade_create(session->pool, c->bucket_alloc);
         
         status = init_callbacks(c, &callbacks);
         if (status != APR_SUCCESS) {
             ap_log_cerror(APLOG_MARK, APLOG_ERR, status, c, APLOGNO(02927) 
                           "nghttp2: error in init_callbacks");
