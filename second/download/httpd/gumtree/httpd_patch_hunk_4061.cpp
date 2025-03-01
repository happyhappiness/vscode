     ap_register_output_filter("H1_TO_H2_RESP", h2_filter_read_response,
                               NULL, AP_FTYPE_PROTOCOL);
     ap_register_output_filter("H2_TRAILERS", h2_response_trailers_filter,
                               NULL, AP_FTYPE_PROTOCOL);
 }
 
+/* post config init */
+apr_status_t h2_task_init(apr_pool_t *pool, server_rec *s)
+{
+    h2_task_logio_add_bytes_in = APR_RETRIEVE_OPTIONAL_FN(ap_logio_add_bytes_in);
+    h2_task_logio_add_bytes_out = APR_RETRIEVE_OPTIONAL_FN(ap_logio_add_bytes_out);
+
+    return APR_SUCCESS;
+}
+
 static int h2_task_pre_conn(conn_rec* c, void *arg)
 {
+    h2_ctx *ctx;
     
-    h2_ctx *ctx = h2_ctx_get(c);
+    if (!c->master) {
+        return OK;
+    }
     
+    ctx = h2_ctx_get(c, 0);
     (void)arg;
     if (h2_ctx_is_task(ctx)) {
-        h2_task *task = h2_ctx_get_task(ctx);
-        
         ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c,
                       "h2_h2, pre_connection, found stream task");
         
         /* Add our own, network level in- and output filters.
          */
-        ap_add_input_filter("H2_TO_H1", task, NULL, c);
-        ap_add_output_filter("H1_TO_H2", task, NULL, c);
+        ap_add_input_filter("H2_TO_H1", NULL, NULL, c);
+        ap_add_output_filter("H1_TO_H2", NULL, NULL, c);
     }
     return OK;
 }
 
 h2_task *h2_task_create(long session_id, const h2_request *req, 
-                        apr_pool_t *pool, h2_mplx *mplx, int eos)
+                        conn_rec *c, h2_mplx *mplx)
 {
-    h2_task *task = apr_pcalloc(pool, sizeof(h2_task));
+    apr_pool_t *pool;
+    h2_task *task;
+    
+    apr_pool_create(&pool, c->pool);
+    task = apr_pcalloc(pool, sizeof(h2_task));
     if (task == NULL) {
-        ap_log_perror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, pool,
+        ap_log_cerror(APLOG_MARK, APLOG_ERR, APR_ENOMEM, c,
                       APLOGNO(02941) "h2_task(%ld-%d): create stream task", 
                       session_id, req->id);
-        h2_mplx_out_close(mplx, req->id, NULL);
+        h2_mplx_out_close(mplx, req->id);
         return NULL;
     }
     
-    task->id        = apr_psprintf(pool, "%ld-%d", session_id, req->id);
-    task->stream_id = req->id;
-    task->pool      = pool;
-    task->mplx      = mplx;
-    task->c         = h2_conn_create(mplx->c, task->pool);
+    task->id          = apr_psprintf(pool, "%ld-%d", session_id, req->id);
+    task->stream_id   = req->id;
+    task->c           = c;
+    task->mplx        = mplx;
+    task->c->keepalives = mplx->c->keepalives;
+    task->pool        = pool;
+    task->request     = req;
+    task->input_eos   = !req->body;
+    task->ser_headers = req->serialize;
+    task->blocking    = 1;
 
-    task->request   = req;
-    task->input_eos = eos;    
-    
+    h2_ctx_create_for(c, task);
     return task;
 }
 
-apr_status_t h2_task_destroy(h2_task *task)
+void h2_task_destroy(h2_task *task)
 {
-    (void)task;
-    return APR_SUCCESS;
+    if (task->pool) {
+        apr_pool_destroy(task->pool);
+    }
+}
+
+void h2_task_set_io_blocking(h2_task *task, int blocking)
+{
+    task->blocking = blocking;
 }
 
-apr_status_t h2_task_do(h2_task *task, h2_worker *worker)
+apr_status_t h2_task_do(h2_task *task, apr_thread_cond_t *cond)
 {
-    apr_status_t status = APR_SUCCESS;
+    apr_status_t status;
     
     AP_DEBUG_ASSERT(task);
+    task->io = cond;
+    task->input = h2_task_input_create(task, task->c);
+    task->output = h2_task_output_create(task, task->c);
+    
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
+                  "h2_task(%s): process connection", task->id);
+    ap_run_process_connection(task->c);
     
-    task->serialize_headers = h2_config_geti(task->request->config, H2_CONF_SER_HEADERS);
-
-    status = h2_worker_setup_task(worker, task);
-    
-    /* save in connection that this one is a pseudo connection */
-    h2_ctx_create_for(task->c, task);
-
-    if (status == APR_SUCCESS) {
-        task->input = h2_task_input_create(task, task->pool, 
-                                           task->c->bucket_alloc);
-        task->output = h2_task_output_create(task, task->pool);
-        
-        ap_process_connection(task->c, h2_worker_get_socket(worker));
-        
+    if (task->frozen) {
         ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
-                      "h2_task(%s): processing done", task->id);
-    }
-    else {
-        ap_log_cerror(APLOG_MARK, APLOG_WARNING, status, task->c,
-                      APLOGNO(02957) "h2_task(%s): error setting up h2_task", 
+                      "h2_task(%s): process_conn returned frozen task", 
                       task->id);
+        /* cleanup delayed */
+        status = APR_EAGAIN;
     }
-    
-    if (task->input) {
-        h2_task_input_destroy(task->input);
-        task->input = NULL;
-    }
-    
-    if (task->output) {
-        h2_task_output_close(task->output);
-        h2_task_output_destroy(task->output);
-        task->output = NULL;
-    }
-
-    if (task->io) {
-        apr_thread_cond_signal(task->io);
+    else {
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, task->c,
+                      "h2_task(%s): processing done", task->id);
+        status = APR_SUCCESS;
     }
     
-    h2_worker_release_task(worker, task);
-    h2_mplx_task_done(task->mplx, task->stream_id);
-    
     return status;
 }
 
-static apr_status_t h2_task_process_request(const h2_request *req, conn_rec *c)
+static apr_status_t h2_task_process_request(h2_task *task, conn_rec *c)
 {
-    request_rec *r;
+    const h2_request *req = task->request;
     conn_state_t *cs = c->cs;
+    request_rec *r;
 
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
+                  "h2_task(%s): create request_rec", task->id);
     r = h2_request_create_rec(req, c);
     if (r && (r->status == HTTP_OK)) {
         ap_update_child_status(c->sbh, SERVER_BUSY_READ, r);
         
-        if (cs)
+        if (cs) {
             cs->state = CONN_STATE_HANDLER;
+        }
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
+                      "h2_task(%s): start process_request", task->id);
         ap_process_request(r);
+        if (task->frozen) {
+            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
+                          "h2_task(%s): process_request frozen", task->id);
+        }
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
+                      "h2_task(%s): process_request done", task->id);
+        
         /* After the call to ap_process_request, the
          * request pool will have been deleted.  We set
          * r=NULL here to ensure that any dereference
          * of r that might be added later in this function
          * will result in a segfault immediately instead
          * of nondeterministic failures later.
          */
-        if (cs)
+        if (cs) 
             cs->state = CONN_STATE_WRITE_COMPLETION;
         r = NULL;
     }
-    ap_update_child_status(c->sbh, SERVER_BUSY_WRITE, NULL);
-    c->sbh = NULL;
+    else if (!r) {
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
+                      "h2_task(%s): create request_rec failed, r=NULL", task->id);
+    }
+    else {
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c,
+                      "h2_task(%s): create request_rec failed, r->status=%d", 
+                      task->id, r->status);
+    }
 
     return APR_SUCCESS;
 }
 
 static int h2_task_process_conn(conn_rec* c)
 {
-    h2_ctx *ctx = h2_ctx_get(c);
+    h2_ctx *ctx;
     
+    if (!c->master) {
+        return DECLINED;
+    }
+    
+    ctx = h2_ctx_get(c, 0);
     if (h2_ctx_is_task(ctx)) {
-        if (!ctx->task->serialize_headers) {
-            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c, 
+        if (!ctx->task->ser_headers) {
+            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, 
                           "h2_h2, processing request directly");
-            h2_task_process_request(ctx->task->request, c);
+            h2_task_process_request(ctx->task, c);
             return DONE;
         }
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, c, 
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, 
                       "h2_task(%s), serialized handling", ctx->task->id);
     }
+    else {
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, c, 
+                      "slave_conn(%ld): has no task", c->id);
+    }
     return DECLINED;
 }
 
+apr_status_t h2_task_freeze(h2_task *task)
+{   
+    if (!task->frozen) {
+        task->frozen = 1;
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, task->c, 
+                      "h2_task(%s), frozen", task->id);
+    }
+    return APR_SUCCESS;
+}
 
+apr_status_t h2_task_thaw(h2_task *task)
+{
+    if (task->frozen) {
+        task->frozen = 0;
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, task->c, 
+                      "h2_task(%s), thawed", task->id);
+    }
+    task->detached = 1;
+    return APR_SUCCESS;
+}
 
-
-
+int h2_task_is_detached(h2_task *task)
+{
+    return task->detached;
+}
