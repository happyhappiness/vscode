     ap_register_input_filter("H2_TO_H1", h2_filter_stream_input,
                              NULL, AP_FTYPE_NETWORK);
     ap_register_output_filter("H1_TO_H2", h2_filter_stream_output,
                               NULL, AP_FTYPE_NETWORK);
     ap_register_output_filter("H1_TO_H2_RESP", h2_filter_read_response,
                               NULL, AP_FTYPE_PROTOCOL);
+    ap_register_output_filter("H2_TRAILERS", h2_response_trailers_filter,
+                              NULL, AP_FTYPE_PROTOCOL);
 }
 
 static int h2_task_pre_conn(conn_rec* c, void *arg)
 {
     
     h2_ctx *ctx = h2_ctx_get(c);
     
     (void)arg;
     if (h2_ctx_is_task(ctx)) {
-        h2_task_env *env = h2_ctx_get_task(ctx);
-        
-        /* This connection is a pseudo-connection used for a h2_task.
-         * Since we read/write directly from it ourselves, we need
-         * to disable a possible ssl connection filter.
-         */
-        h2_tls_disable(c);
+        h2_task *task = h2_ctx_get_task(ctx);
         
         ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                       "h2_h2, pre_connection, found stream task");
         
         /* Add our own, network level in- and output filters.
          */
-        ap_add_input_filter("H2_TO_H1", env, NULL, c);
-        ap_add_output_filter("H1_TO_H2", env, NULL, c);
+        ap_add_input_filter("H2_TO_H1", task, NULL, c);
+        ap_add_output_filter("H1_TO_H2", task, NULL, c);
     }
     return OK;
 }
 
-static int h2_task_process_conn(conn_rec* c)
+h2_task *h2_task_create(long session_id, const h2_request *req, 
+                        apr_pool_t *pool, h2_mplx *mplx, int eos)
 {
-    h2_ctx *ctx = h2_ctx_get(c);
-    
-    if (h2_ctx_is_task(ctx)) {
-        if (!ctx->task_env->serialize_headers) {
-            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c, 
-                          "h2_h2, processing request directly");
-            h2_task_process_request(ctx->task_env);
-            return DONE;
-        }
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c, 
-                      "h2_task(%s), serialized handling", ctx->task_env->id);
-    }
-    return DECLINED;
-}
-
-
-h2_task *h2_task_create(long session_id,
-                        int stream_id,
-                        apr_pool_t *stream_pool,
-                        h2_mplx *mplx, conn_rec *c)
-{
-    h2_task *task = apr_pcalloc(stream_pool, sizeof(h2_task));
+    h2_task *task = apr_pcalloc(pool, sizeof(h2_task));
     if (task == NULL) {
-        ap_log_perror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, stream_pool,
+        ap_log_perror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, pool,
                       APLOGNO(02941) "h2_task(%ld-%d): create stream task", 
-                      session_id, stream_id);
-        h2_mplx_out_close(mplx, stream_id);
+                      session_id, req->id);
+        h2_mplx_out_close(mplx, req->id, NULL);
         return NULL;
     }
     
-    APR_RING_ELEM_INIT(task, link);
+    task->id        = apr_psprintf(pool, "%ld-%d", session_id, req->id);
+    task->stream_id = req->id;
+    task->pool      = pool;
+    task->mplx      = mplx;
+    task->c         = h2_conn_create(mplx->c, task->pool);
 
-    task->id = apr_psprintf(stream_pool, "%ld-%d", session_id, stream_id);
-    task->stream_id = stream_id;
-    task->mplx = mplx;
+    task->request   = req;
+    task->input_eos = eos;    
     
-    task->c = c;
-    
-    ap_log_perror(APLOG_MARK, APLOG_DEBUG, 0, stream_pool,
-                  "h2_task(%s): created", task->id);
     return task;
 }
 
-void h2_task_set_request(h2_task *task, 
-                         const char *method, 
-                         const char *scheme, 
-                         const char *authority, 
-                         const char *path, 
-                         apr_table_t *headers, int eos)
-{
-    task->method = method;
-    task->scheme = scheme;
-    task->authority = authority;
-    task->path = path;
-    task->headers = headers;
-    task->input_eos = eos;
-}
-
 apr_status_t h2_task_destroy(h2_task *task)
 {
     (void)task;
     return APR_SUCCESS;
 }
 
 apr_status_t h2_task_do(h2_task *task, h2_worker *worker)
 {
     apr_status_t status = APR_SUCCESS;
-    h2_config *cfg = h2_config_get(task->mplx->c);
-    h2_task_env env; 
     
     AP_DEBUG_ASSERT(task);
     
-    memset(&env, 0, sizeof(env));
-    
-    env.id = task->id;
-    env.stream_id = task->stream_id;
-    env.mplx = task->mplx;
-    task->mplx = NULL;
-    
-    env.input_eos = task->input_eos;
-    env.serialize_headers = h2_config_geti(cfg, H2_CONF_SER_HEADERS);
-    
-    /* Create a subpool from the worker one to be used for all things
-     * with life-time of this task_env execution.
-     */
-    apr_pool_create(&env.pool, h2_worker_get_pool(worker));
+    task->serialize_headers = h2_config_geti(task->request->config, H2_CONF_SER_HEADERS);
 
-    /* Link the env to the worker which provides useful things such
-     * as mutex, a socket etc. */
-    env.io = h2_worker_get_cond(worker);
-    
-    /* Clone fields, so that lifetimes become (more) independent. */
-    env.method    = apr_pstrdup(env.pool, task->method);
-    env.scheme    = apr_pstrdup(env.pool, task->scheme);
-    env.authority = apr_pstrdup(env.pool, task->authority);
-    env.path      = apr_pstrdup(env.pool, task->path);
-    env.headers   = apr_table_clone(env.pool, task->headers);
-    
-    /* Setup the pseudo connection to use our own pool and bucket_alloc */
-    env.c = *task->c;
-    task->c = NULL;
-    status = h2_conn_setup(&env, worker);
-    
-    /* save in connection that this one is a pseudo connection, prevents
-     * other hooks from messing with it. */
-    h2_ctx_create_for(&env.c, &env);
+    status = h2_worker_setup_task(worker, task);
+    
+    /* save in connection that this one is a pseudo connection */
+    h2_ctx_create_for(task->c, task);
 
     if (status == APR_SUCCESS) {
-        env.input = h2_task_input_create(&env, env.pool, 
-                                         env.c.bucket_alloc);
-        env.output = h2_task_output_create(&env, env.pool,
-                                           env.c.bucket_alloc);
-        status = h2_conn_process(&env.c, h2_worker_get_socket(worker));
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, &env.c,
-                      "h2_task(%s): processing done", env.id);
+        task->input = h2_task_input_create(task, task->pool, 
+                                           task->c->bucket_alloc);
+        task->output = h2_task_output_create(task, task->pool);
+        
+        ap_process_connection(task->c, h2_worker_get_socket(worker));
+        
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
+                      "h2_task(%s): processing done", task->id);
     }
     else {
-        ap_log_cerror(APLOG_MARK, APLOG_WARNING, status, &env.c,
-                      APLOGNO(02957) "h2_task(%s): error setting up h2_task_env", 
-                      env.id);
+        ap_log_cerror(APLOG_MARK, APLOG_WARNING, status, task->c,
+                      APLOGNO(02957) "h2_task(%s): error setting up h2_task", 
+                      task->id);
     }
     
-    if (env.input) {
-        h2_task_input_destroy(env.input);
-        env.input = NULL;
+    if (task->input) {
+        h2_task_input_destroy(task->input);
+        task->input = NULL;
     }
     
-    if (env.output) {
-        h2_task_output_close(env.output);
-        h2_task_output_destroy(env.output);
-        env.output = NULL;
+    if (task->output) {
+        h2_task_output_close(task->output);
+        h2_task_output_destroy(task->output);
+        task->output = NULL;
     }
 
-    h2_task_set_finished(task);
-    if (env.io) {
-        apr_thread_cond_signal(env.io);
-    }
-    
-    if (env.pool) {
-        apr_pool_destroy(env.pool);
-        env.pool = NULL;
+    if (task->io) {
+        apr_thread_cond_signal(task->io);
     }
     
-    if (env.c.id) {
-        h2_conn_post(&env.c, worker);
-    }
-    
-    h2_mplx_task_done(env.mplx, env.stream_id);
+    h2_worker_release_task(worker, task);
+    h2_mplx_task_done(task->mplx, task->stream_id);
     
     return status;
 }
 
-int h2_task_has_started(h2_task *task)
-{
-    AP_DEBUG_ASSERT(task);
-    return apr_atomic_read32(&task->has_started);
-}
-
-void h2_task_set_started(h2_task *task)
+static apr_status_t h2_task_process_request(const h2_request *req, conn_rec *c)
 {
-    AP_DEBUG_ASSERT(task);
-    apr_atomic_set32(&task->has_started, 1);
-}
-
-int h2_task_has_finished(h2_task *task)
-{
-    return apr_atomic_read32(&task->has_finished);
-}
-
-void h2_task_set_finished(h2_task *task)
-{
-    apr_atomic_set32(&task->has_finished, 1);
-}
-
-void h2_task_die(h2_task_env *env, int status, request_rec *r)
-{
-    (void)env;
-    ap_die(status, r);
-}
-
-static request_rec *h2_task_create_request(h2_task_env *env)
-{
-    conn_rec *conn = &env->c;
-    request_rec *r;
-    apr_pool_t *p;
-    int access_status = HTTP_OK;    
-    
-    apr_pool_create(&p, conn->pool);
-    apr_pool_tag(p, "request");
-    r = apr_pcalloc(p, sizeof(request_rec));
-    AP_READ_REQUEST_ENTRY((intptr_t)r, (uintptr_t)conn);
-    r->pool            = p;
-    r->connection      = conn;
-    r->server          = conn->base_server;
-    
-    r->user            = NULL;
-    r->ap_auth_type    = NULL;
-    
-    r->allowed_methods = ap_make_method_list(p, 2);
-    
-    r->headers_in = apr_table_copy(r->pool, env->headers);
-    r->trailers_in     = apr_table_make(r->pool, 5);
-    r->subprocess_env  = apr_table_make(r->pool, 25);
-    r->headers_out     = apr_table_make(r->pool, 12);
-    r->err_headers_out = apr_table_make(r->pool, 5);
-    r->trailers_out    = apr_table_make(r->pool, 5);
-    r->notes           = apr_table_make(r->pool, 5);
-    
-    r->request_config  = ap_create_request_config(r->pool);
-    /* Must be set before we run create request hook */
-    
-    r->proto_output_filters = conn->output_filters;
-    r->output_filters  = r->proto_output_filters;
-    r->proto_input_filters = conn->input_filters;
-    r->input_filters   = r->proto_input_filters;
-    ap_run_create_request(r);
-    r->per_dir_config  = r->server->lookup_defaults;
-    
-    r->sent_bodyct     = 0;                      /* bytect isn't for body */
-    
-    r->read_length     = 0;
-    r->read_body       = REQUEST_NO_BODY;
-    
-    r->status          = HTTP_OK;  /* Until further notice */
-    r->header_only     = 0;
-    r->the_request     = NULL;
-    
-    /* Begin by presuming any module can make its own path_info assumptions,
-     * until some module interjects and changes the value.
-     */
-    r->used_path_info = AP_REQ_DEFAULT_PATH_INFO;
-    
-    r->useragent_addr = conn->client_addr;
-    r->useragent_ip = conn->client_ip;
-    
-    ap_run_pre_read_request(r, conn);
-    
-    /* Time to populate r with the data we have. */
-    r->request_time = apr_time_now();
-    r->the_request = apr_psprintf(r->pool, "%s %s HTTP/1.1", 
-                                  env->method, env->path);
-    r->method = env->method;
-    /* Provide quick information about the request method as soon as known */
-    r->method_number = ap_method_number_of(r->method);
-    if (r->method_number == M_GET && r->method[0] == 'H') {
-        r->header_only = 1;
-    }
-
-    ap_parse_uri(r, env->path);
-    r->protocol = (char*)"HTTP/2";
-    r->proto_num = HTTP_VERSION(2, 0);
-    
-    /* update what we think the virtual host is based on the headers we've
-     * now read. may update status.
-     * Leave r->hostname empty, vhost will parse if form our Host: header,
-     * otherwise we get complains about port numbers.
-     */
-    r->hostname = NULL;
-    ap_update_vhost_from_headers(r);
-    
-    /* we may have switched to another server */
-    r->per_dir_config = r->server->lookup_defaults;
-    
-    /*
-     * Add the HTTP_IN filter here to ensure that ap_discard_request_body
-     * called by ap_die and by ap_send_error_response works correctly on
-     * status codes that do not cause the connection to be dropped and
-     * in situations where the connection should be kept alive.
-     */
-    ap_add_input_filter_handle(ap_http_input_filter_handle,
-                               NULL, r, r->connection);
-    
-    if (access_status != HTTP_OK
-        || (access_status = ap_run_post_read_request(r))) {
-        /* Request check post hooks failed. An example of this would be a
-         * request for a vhost where h2 is disabled --> 421.
-         */
-        h2_task_die(env, access_status, r);
-        ap_update_child_status(conn->sbh, SERVER_BUSY_LOG, r);
-        ap_run_log_transaction(r);
-        r = NULL;
-        goto traceout;
-    }
-    
-    AP_READ_REQUEST_SUCCESS((uintptr_t)r, (char *)r->method, 
-                            (char *)r->uri, (char *)r->server->defn_name, 
-                            r->status);
-    return r;
-traceout:
-    AP_READ_REQUEST_FAILURE((uintptr_t)r);
-    return r;
-}
-
-
-apr_status_t h2_task_process_request(h2_task_env *env)
-{
-    conn_rec *c = &env->c;
     request_rec *r;
     conn_state_t *cs = c->cs;
 
-    r = h2_task_create_request(env);
+    r = h2_request_create_rec(req, c);
     if (r && (r->status == HTTP_OK)) {
         ap_update_child_status(c->sbh, SERVER_BUSY_READ, r);
         
         if (cs)
             cs->state = CONN_STATE_HANDLER;
         ap_process_request(r);
