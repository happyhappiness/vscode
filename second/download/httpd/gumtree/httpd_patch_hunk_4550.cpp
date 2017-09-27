     }
     else {
         /* graceful shutdown. we will continue processing all streams
          * we have, but no longer accept new ones. Report the max stream
          * we have received and discard all new ones. */
     }
-    nghttp2_submit_goaway(session->ngh2, NGHTTP2_FLAG_NONE, 
-                          session->local.accepted_max, 
-                          error, (uint8_t*)msg, msg? strlen(msg):0);
+    
     session->local.accepting = 0;
     session->local.shutdown = 1;
-    status = nghttp2_session_send(session->ngh2);
-    if (status == APR_SUCCESS) {
-        status = h2_conn_io_flush(&session->io);
+    if (!session->c->aborted) {
+        nghttp2_submit_goaway(session->ngh2, NGHTTP2_FLAG_NONE, 
+                              session->local.accepted_max, 
+                              error, (uint8_t*)msg, msg? strlen(msg):0);
+        status = nghttp2_session_send(session->ngh2);
+        if (status == APR_SUCCESS) {
+            status = h2_conn_io_flush(&session->io);
+        }
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, 
+                      H2_SSSN_LOG(APLOGNO(03069), session, 
+                                  "sent GOAWAY, err=%d, msg=%s"), error, msg? msg : "");
     }
-    ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, session->c, APLOGNO(03069)
-                  "session(%ld): sent GOAWAY, err=%d, msg=%s", 
-                  session->id, error, msg? msg : "");
     dispatch_event(session, H2_SESSION_EV_LOCAL_GOAWAY, error, msg);
-    
-    if (force_close) {
-        apr_brigade_cleanup(session->bbtmp);
-        h2_mplx_abort(session->mplx);
-    }
-    
     return status;
 }
 
-static apr_status_t session_pool_cleanup(void *data)
+static apr_status_t session_cleanup(h2_session *session, const char *trigger)
 {
-    h2_session *session = data;
-    /* On a controlled connection shutdown, this gets never
-     * called as we deregister and destroy our pool manually.
-     * However when we have an async mpm, and handed it our idle
-     * connection, it will just cleanup once the connection is closed
-     * from the other side (and sometimes even from out side) and
-     * here we arrive then.
-     */
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
-                  "session(%ld): pool_cleanup", session->id);
+    conn_rec *c = session->c;
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
+                  H2_SSSN_MSG(session, "pool_cleanup"));
     
-    if (session->state != H2_SESSION_ST_DONE) {
+    if (session->state != H2_SESSION_ST_DONE
+        && session->state != H2_SESSION_ST_INIT) {
         /* Not good. The connection is being torn down and we have
          * not sent a goaway. This is considered a protocol error and
          * the client has to assume that any streams "in flight" may have
          * been processed and are not safe to retry.
          * As clients with idle connection may only learn about a closed
          * connection when sending the next request, this has the effect
          * that at least this one request will fail.
          */
-        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, session->c, APLOGNO(03199)
-                      "session(%ld): connection disappeared without proper "
-                      "goodbye, clients will be confused, should not happen", 
-                      session->id);
-    }
-    /* keep us from destroying the pool, since that is already ongoing. */
-    session->pool = NULL;
-    h2_session_destroy(session);
-    return APR_SUCCESS;
-}
-
-static void *session_malloc(size_t size, void *ctx)
-{
-    h2_session *session = ctx;
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE6, 0, session->c,
-                  "h2_session(%ld): malloc(%ld)",
-                  session->id, (long)size);
-    return malloc(size);
-}
-
-static void session_free(void *p, void *ctx)
-{
-    h2_session *session = ctx;
-
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE6, 0, session->c,
-                  "h2_session(%ld): free()",
-                  session->id);
-    free(p);
-}
-
-static void *session_calloc(size_t n, size_t size, void *ctx)
-{
-    h2_session *session = ctx;
+        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, c,
+                      H2_SSSN_LOG(APLOGNO(03199), session, 
+                      "connection disappeared without proper "
+                      "goodbye, clients will be confused, should not happen"));
+    }
 
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE6, 0, session->c,
-                  "h2_session(%ld): calloc(%ld, %ld)",
-                  session->id, (long)n, (long)size);
-    return calloc(n, size);
+    transit(session, trigger, H2_SESSION_ST_CLEANUP);
+    h2_mplx_release_and_join(session->mplx, session->iowait);
+    session->mplx = NULL;
+
+    ap_assert(session->ngh2);
+    nghttp2_session_del(session->ngh2);
+    session->ngh2 = NULL;
+    h2_ctx_clear(c);
+    
+    
+    return APR_SUCCESS;
 }
 
-static void *session_realloc(void *p, size_t size, void *ctx)
+static apr_status_t session_pool_cleanup(void *data)
 {
-    h2_session *session = ctx;
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE6, 0, session->c,
-                  "h2_session(%ld): realloc(%ld)",
-                  session->id, (long)size);
-    return realloc(p, size);
+    conn_rec *c = data;
+    h2_session *session;
+    h2_ctx *ctx = h2_ctx_get(c, 0);
+    
+    if (ctx && (session = h2_ctx_session_get(ctx))) {
+        /* if the session is still there, now is the last chance
+         * to perform cleanup. Normally, cleanup should have happened
+         * earlier in the connection pre_close. Main reason is that
+         * any ongoing requests on slave connections might still access
+         * data which has, at this time, already been freed. An example
+         * is mod_ssl that uses request hooks. */
+        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, c,
+                      H2_SSSN_LOG(APLOGNO(10020), session, 
+                      "session cleanup triggered by pool cleanup. "
+                      "this should have happened earlier already."));
+        return session_cleanup(session, "pool cleanup");
+    }
+    return APR_SUCCESS;
 }
 
-static h2_session *h2_session_create_int(conn_rec *c,
-                                         request_rec *r,
-                                         h2_ctx *ctx, 
-                                         h2_workers *workers)
+static apr_status_t h2_session_create_int(h2_session **psession,
+                                          conn_rec *c,
+                                          request_rec *r,
+                                          h2_ctx *ctx, 
+                                          h2_workers *workers)
 {
     nghttp2_session_callbacks *callbacks = NULL;
     nghttp2_option *options = NULL;
+    apr_allocator_t *allocator;
+    apr_thread_mutex_t *mutex;
     uint32_t n;
-
     apr_pool_t *pool = NULL;
-    apr_status_t status = apr_pool_create(&pool, c->pool);
     h2_session *session;
+    apr_status_t status;
+    int rv;
+
+    *psession = NULL;
+    status = apr_allocator_create(&allocator);
     if (status != APR_SUCCESS) {
-        return NULL;
+        return status;
+    }
+    apr_allocator_max_free_set(allocator, ap_max_mem_free);
+    apr_pool_create_ex(&pool, c->pool, NULL, allocator);
+    if (!pool) {
+        apr_allocator_destroy(allocator);
+        return APR_ENOMEM;
     }
     apr_pool_tag(pool, "h2_session");
-
+    apr_allocator_owner_set(allocator, pool);
+    status = apr_thread_mutex_create(&mutex, APR_THREAD_MUTEX_DEFAULT, pool);
+    if (status != APR_SUCCESS) {
+        apr_pool_destroy(pool);
+        return APR_ENOMEM;
+    }
+    apr_allocator_mutex_set(allocator, mutex);
+    
     session = apr_pcalloc(pool, sizeof(h2_session));
-    if (session) {
-        int rv;
-        nghttp2_mem *mem;
-        
-        session->id = c->id;
-        session->c = c;
-        session->r = r;
-        session->s = h2_ctx_server_get(ctx);
-        session->pool = pool;
-        session->config = h2_config_sget(session->s);
-        session->workers = workers;
-        
-        session->state = H2_SESSION_ST_INIT;
-        session->local.accepting = 1;
-        session->remote.accepting = 1;
-        
-        apr_pool_pre_cleanup_register(pool, session, session_pool_cleanup);
-        
-        session->max_stream_count = h2_config_geti(session->config, 
-                                                   H2_CONF_MAX_STREAMS);
-        session->max_stream_mem = h2_config_geti(session->config, 
-                                                 H2_CONF_STREAM_MAX_MEM);
-
-        status = apr_thread_cond_create(&session->iowait, session->pool);
-        if (status != APR_SUCCESS) {
-            return NULL;
-        }
-        
-        session->mplx = h2_mplx_create(c, session->pool, session->config, 
-                                       session->s->timeout, workers);
-        
-        h2_mplx_set_consumed_cb(session->mplx, update_window, session);
-        
-        /* Install the connection input filter that feeds the session */
-        session->cin = h2_filter_cin_create(session->pool, 
-                                            h2_session_receive, session);
-        ap_add_input_filter("H2_IN", session->cin, r, c);
-
-        h2_conn_io_init(&session->io, c, session->config);
-        session->bbtmp = apr_brigade_create(session->pool, c->bucket_alloc);
-        
-        status = init_callbacks(c, &callbacks);
-        if (status != APR_SUCCESS) {
-            ap_log_cerror(APLOG_MARK, APLOG_ERR, status, c, APLOGNO(02927) 
-                          "nghttp2: error in init_callbacks");
-            h2_session_destroy(session);
-            return NULL;
-        }
-        
-        rv = nghttp2_option_new(&options);
-        if (rv != 0) {
-            ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, c,
-                          APLOGNO(02928) "nghttp2_option_new: %s", 
-                          nghttp2_strerror(rv));
-            h2_session_destroy(session);
-            return NULL;
-        }
-        nghttp2_option_set_peer_max_concurrent_streams(
-            options, (uint32_t)session->max_stream_count);
-        /* We need to handle window updates ourself, otherwise we
-         * get flooded by nghttp2. */
-        nghttp2_option_set_no_auto_window_update(options, 1);
-        
-        if (APLOGctrace6(c)) {
-            mem = apr_pcalloc(session->pool, sizeof(nghttp2_mem));
-            mem->mem_user_data = session;
-            mem->malloc    = session_malloc;
-            mem->free      = session_free;
-            mem->calloc    = session_calloc;
-            mem->realloc   = session_realloc;
-            
-            rv = nghttp2_session_server_new3(&session->ngh2, callbacks,
-                                             session, options, mem);
-        }
-        else {
-            rv = nghttp2_session_server_new2(&session->ngh2, callbacks,
-                                             session, options);
-        }
-        nghttp2_session_callbacks_del(callbacks);
-        nghttp2_option_del(options);
-        
-        if (rv != 0) {
-            ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, c,
-                          APLOGNO(02929) "nghttp2_session_server_new: %s",
-                          nghttp2_strerror(rv));
-            h2_session_destroy(session);
-            return NULL;
-        }
-         
-        n = h2_config_geti(session->config, H2_CONF_PUSH_DIARY_SIZE);
-        session->push_diary = h2_push_diary_create(session->pool, n);
-        
-        if (APLOGcdebug(c)) {
-            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(03200)
-                          "h2_session(%ld) created, max_streams=%d, "
-                          "stream_mem=%d, workers_limit=%d, workers_max=%d, "
-                          "push_diary(type=%d,N=%d)",
-                          session->id, (int)session->max_stream_count, 
-                          (int)session->max_stream_mem,
-                          session->mplx->workers_limit, 
-                          session->mplx->workers_max, 
-                          session->push_diary->dtype, 
-                          (int)session->push_diary->N);
-        }
+    if (!session) {
+        return APR_ENOMEM;
+    }
+    
+    *psession = session;
+    session->id = c->id;
+    session->c = c;
+    session->r = r;
+    session->s = h2_ctx_server_get(ctx);
+    session->pool = pool;
+    session->config = h2_config_sget(session->s);
+    session->workers = workers;
+    
+    session->state = H2_SESSION_ST_INIT;
+    session->local.accepting = 1;
+    session->remote.accepting = 1;
+    
+    session->max_stream_count = h2_config_geti(session->config, 
+                                               H2_CONF_MAX_STREAMS);
+    session->max_stream_mem = h2_config_geti(session->config, 
+                                             H2_CONF_STREAM_MAX_MEM);
+    
+    status = apr_thread_cond_create(&session->iowait, session->pool);
+    if (status != APR_SUCCESS) {
+        apr_pool_destroy(pool);
+        return status;
+    }
+    
+    session->in_pending = h2_iq_create(session->pool, (int)session->max_stream_count);
+    if (session->in_pending == NULL) {
+        apr_pool_destroy(pool);
+        return APR_ENOMEM;
     }
-    return session;
-}
 
-h2_session *h2_session_create(conn_rec *c, h2_ctx *ctx, h2_workers *workers)
-{
-    return h2_session_create_int(c, NULL, ctx, workers);
+    session->in_process = h2_iq_create(session->pool, (int)session->max_stream_count);
+    if (session->in_process == NULL) {
+        apr_pool_destroy(pool);
+        return APR_ENOMEM;
+    }
+    
+    session->monitor = apr_pcalloc(pool, sizeof(h2_stream_monitor));
+    if (session->monitor == NULL) {
+        apr_pool_destroy(pool);
+        return APR_ENOMEM;
+    }
+    session->monitor->ctx = session;
+    session->monitor->on_state_enter = on_stream_state_enter;
+    session->monitor->on_state_event = on_stream_state_event;
+    session->monitor->on_event = on_stream_event;
+    
+    session->mplx = h2_mplx_create(c, session->pool, session->config, 
+                                   workers);
+    
+    /* connection input filter that feeds the session */
+    session->cin = h2_filter_cin_create(session);
+    ap_add_input_filter("H2_IN", session->cin, r, c);
+    
+    h2_conn_io_init(&session->io, c, session->config);
+    session->bbtmp = apr_brigade_create(session->pool, c->bucket_alloc);
+    
+    status = init_callbacks(c, &callbacks);
+    if (status != APR_SUCCESS) {
+        ap_log_cerror(APLOG_MARK, APLOG_ERR, status, c, APLOGNO(02927) 
+                      "nghttp2: error in init_callbacks");
+        apr_pool_destroy(pool);
+        return status;
+    }
+    
+    rv = nghttp2_option_new(&options);
+    if (rv != 0) {
+        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, c,
+                      APLOGNO(02928) "nghttp2_option_new: %s", 
+                      nghttp2_strerror(rv));
+        apr_pool_destroy(pool);
+        return status;
+    }
+    nghttp2_option_set_peer_max_concurrent_streams(
+                                                   options, (uint32_t)session->max_stream_count);
+    /* We need to handle window updates ourself, otherwise we
+     * get flooded by nghttp2. */
+    nghttp2_option_set_no_auto_window_update(options, 1);
+    
+    rv = nghttp2_session_server_new2(&session->ngh2, callbacks,
+                                     session, options);
+    nghttp2_session_callbacks_del(callbacks);
+    nghttp2_option_del(options);
+    
+    if (rv != 0) {
+        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_EGENERAL, c,
+                      APLOGNO(02929) "nghttp2_session_server_new: %s",
+                      nghttp2_strerror(rv));
+        apr_pool_destroy(pool);
+        return APR_ENOMEM;
+    }
+    
+    n = h2_config_geti(session->config, H2_CONF_PUSH_DIARY_SIZE);
+    session->push_diary = h2_push_diary_create(session->pool, n);
+    
+    if (APLOGcdebug(c)) {
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, 
+                      H2_SSSN_LOG(APLOGNO(03200), session, 
+                                  "created, max_streams=%d, stream_mem=%d, "
+                                  "workers_limit=%d, workers_max=%d, "
+                                  "push_diary(type=%d,N=%d)"),
+                      (int)session->max_stream_count, 
+                      (int)session->max_stream_mem,
+                      session->mplx->limit_active, 
+                      session->mplx->max_active, 
+                      session->push_diary->dtype, 
+                      (int)session->push_diary->N);
+    }
+    
+    apr_pool_pre_cleanup_register(pool, c, session_pool_cleanup);    
+    return APR_SUCCESS;
 }
 
-h2_session *h2_session_rcreate(request_rec *r, h2_ctx *ctx, h2_workers *workers)
+apr_status_t h2_session_create(h2_session **psession, 
+                               conn_rec *c, h2_ctx *ctx, h2_workers *workers)
 {
-    return h2_session_create_int(r->connection, r, ctx, workers);
+    return h2_session_create_int(psession, c, NULL, ctx, workers);
 }
 
-void h2_session_eoc_callback(h2_session *session)
+apr_status_t h2_session_rcreate(h2_session **psession, 
+                                request_rec *r, h2_ctx *ctx, h2_workers *workers)
 {
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c,
-                  "session(%ld): cleanup and destroy", session->id);
-    apr_pool_cleanup_kill(session->pool, session, session_pool_cleanup);
-    h2_session_destroy(session);
+    return h2_session_create_int(psession, r->connection, r, ctx, workers);
 }
 
 static apr_status_t h2_session_start(h2_session *session, int *rv)
 {
     apr_status_t status = APR_SUCCESS;
     nghttp2_settings_entry settings[3];
