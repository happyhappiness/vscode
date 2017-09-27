     AP_DEBUG_ASSERT(m);
     if (m->added_output) {
         apr_thread_cond_signal(m->added_output);
     }
 }
 
-apr_status_t h2_mplx_do_task(h2_mplx *m, struct h2_task *task)
+apr_status_t h2_mplx_reprioritize(h2_mplx *m, h2_stream_pri_cmp *cmp, void *ctx)
 {
     apr_status_t status;
+    
     AP_DEBUG_ASSERT(m);
     if (m->aborted) {
         return APR_ECONNABORTED;
     }
     status = apr_thread_mutex_lock(m->lock);
     if (APR_SUCCESS == status) {
-        /* TODO: needs to sort queue by priority */
+        h2_tq_sort(m->q, cmp, ctx);
+        
         ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
-                      "h2_mplx: do task(%s)", task->id);
-        h2_tq_append(m->q, task);
+                      "h2_mplx(%ld): reprioritize tasks", m->id);
         apr_thread_mutex_unlock(m->lock);
     }
     workers_register(m);
     return status;
 }
 
-h2_task *h2_mplx_pop_task(h2_mplx *m, int *has_more)
+static h2_io *open_io(h2_mplx *m, int stream_id)
+{
+    apr_pool_t *io_pool = m->spare_pool;
+    h2_io *io;
+    
+    if (!io_pool) {
+        apr_pool_create(&io_pool, m->pool);
+    }
+    else {
+        m->spare_pool = NULL;
+    }
+    
+    io = h2_io_create(stream_id, io_pool, m->bucket_alloc);
+    h2_io_set_add(m->stream_ios, io);
+    
+    return io;
+}
+
+
+apr_status_t h2_mplx_process(h2_mplx *m, int stream_id,
+                             const h2_request *req, int eos, 
+                             h2_stream_pri_cmp *cmp, void *ctx)
 {
-    h2_task *task = NULL;
     apr_status_t status;
+    
     AP_DEBUG_ASSERT(m);
     if (m->aborted) {
-        *has_more = 0;
-        return NULL;
+        return APR_ECONNABORTED;
     }
     status = apr_thread_mutex_lock(m->lock);
     if (APR_SUCCESS == status) {
-        task = h2_tq_pop_first(m->q);
-        if (task) {
-            h2_task_set_started(task);
+        h2_io *io = open_io(m, stream_id);
+        io->request = req;
+        io->request_body = !eos;
+
+        if (eos) {
+            status = h2_io_in_close(io);
         }
-        *has_more = !h2_tq_empty(m->q);
+        
+        h2_tq_add(m->q, io->id, cmp, ctx);
+
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, m->c,
+                      "h2_mplx(%ld-%d): process", m->c->id, stream_id);
+        H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_process");
         apr_thread_mutex_unlock(m->lock);
     }
-    return task;
+    
+    if (status == APR_SUCCESS) {
+        workers_register(m);
+    }
+    return status;
 }
 
-apr_status_t h2_mplx_create_task(h2_mplx *m, struct h2_stream *stream)
+h2_task *h2_mplx_pop_task(h2_mplx *m, h2_worker *w, int *has_more)
 {
+    h2_task *task = NULL;
     apr_status_t status;
+    
     AP_DEBUG_ASSERT(m);
     if (m->aborted) {
-        return APR_ECONNABORTED;
+        *has_more = 0;
+        return NULL;
     }
     status = apr_thread_mutex_lock(m->lock);
     if (APR_SUCCESS == status) {
-        conn_rec *c = h2_conn_create(m->c, stream->pool);
-        stream->task = h2_task_create(m->id, stream->id, 
-                                      stream->pool, m, c);
-        
+        int sid;
+        while (!task && (sid = h2_tq_shift(m->q)) > 0) {
+            /* Anything not already setup correctly in the task
+             * needs to be so now, as task will be executed right about 
+             * when this method returns. */
+            h2_io *io = h2_io_set_get(m->stream_ios, sid);
+            if (io) {
+                task = h2_worker_create_task(w, m, io->request, !io->request_body);
+            }
+        }
+        *has_more = !h2_tq_empty(m->q);
         apr_thread_mutex_unlock(m->lock);
     }
-    return status;
+    return task;
 }
 
