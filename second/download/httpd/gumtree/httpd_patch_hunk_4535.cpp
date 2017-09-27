     int streams_updated;
 } ngn_update_ctx;
 
 static int ngn_update_window(void *ctx, void *val)
 {
     ngn_update_ctx *uctx = ctx;
-    h2_task *task = val;
-    if (task && task->assigned == uctx->ngn
-        && output_consumed_signal(uctx->m, task)) {
+    h2_stream *stream = val;
+    if (stream->task && stream->task->assigned == uctx->ngn
+        && output_consumed_signal(uctx->m, stream->task)) {
         ++uctx->streams_updated;
     }
     return 1;
 }
 
 static apr_status_t ngn_out_update_windows(h2_mplx *m, h2_req_engine *ngn)
 {
     ngn_update_ctx ctx;
         
     ctx.m = m;
     ctx.ngn = ngn;
     ctx.streams_updated = 0;
-    h2_ihash_iter(m->tasks, ngn_update_window, &ctx);
+    h2_ihash_iter(m->streams, ngn_update_window, &ctx);
     
     return ctx.streams_updated? APR_SUCCESS : APR_EAGAIN;
 }
 
 apr_status_t h2_mplx_req_engine_push(const char *ngn_type, 
                                      request_rec *r,
                                      http2_req_engine_init *einit)
 {
     apr_status_t status;
     h2_mplx *m;
     h2_task *task;
-    int acquired;
+    h2_stream *stream;
     
     task = h2_ctx_rget_task(r);
     if (!task) {
         return APR_ECONNABORTED;
     }
     m = task->mplx;
     
-    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
-        h2_stream *stream = h2_ihash_get(m->streams, task->stream_id);
-        
-        if (stream) {
-            status = h2_ngn_shed_push_request(m->ngn_shed, ngn_type, r, einit);
-        }
-        else {
-            status = APR_ECONNABORTED;
-        }
-        leave_mutex(m, acquired);
+    H2_MPLX_ENTER(m);
+
+    stream = h2_ihash_get(m->streams, task->stream_id);
+    if (stream) {
+        status = h2_ngn_shed_push_request(m->ngn_shed, ngn_type, r, einit);
+    }
+    else {
+        status = APR_ECONNABORTED;
     }
+
+    H2_MPLX_LEAVE(m);
     return status;
 }
 
 apr_status_t h2_mplx_req_engine_pull(h2_req_engine *ngn, 
                                      apr_read_type_e block, 
                                      int capacity, 
                                      request_rec **pr)
 {   
     h2_ngn_shed *shed = h2_ngn_shed_get_shed(ngn);
     h2_mplx *m = h2_ngn_shed_get_ctx(shed);
     apr_status_t status;
-    int acquired;
+    int want_shutdown;
     
-    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
-        int want_shutdown = (block == APR_BLOCK_READ);
+    H2_MPLX_ENTER(m);
 
-        /* Take this opportunity to update output consummation 
-         * for this engine */
-        ngn_out_update_windows(m, ngn);
-        
-        if (want_shutdown && !h2_iq_empty(m->q)) {
-            /* For a blocking read, check first if requests are to be
-             * had and, if not, wait a short while before doing the
-             * blocking, and if unsuccessful, terminating read.
-             */
+    want_shutdown = (block == APR_BLOCK_READ);
+
+    /* Take this opportunity to update output consummation 
+     * for this engine */
+    ngn_out_update_windows(m, ngn);
+    
+    if (want_shutdown && !h2_iq_empty(m->q)) {
+        /* For a blocking read, check first if requests are to be
+         * had and, if not, wait a short while before doing the
+         * blocking, and if unsuccessful, terminating read.
+         */
+        status = h2_ngn_shed_pull_request(shed, ngn, capacity, 1, pr);
+        if (APR_STATUS_IS_EAGAIN(status)) {
+            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
+                          "h2_mplx(%ld): start block engine pull", m->id);
+            apr_thread_cond_timedwait(m->task_thawed, m->lock, 
+                                      apr_time_from_msec(20));
             status = h2_ngn_shed_pull_request(shed, ngn, capacity, 1, pr);
-            if (APR_STATUS_IS_EAGAIN(status)) {
-                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
-                              "h2_mplx(%ld): start block engine pull", m->id);
-                apr_thread_cond_timedwait(m->task_thawed, m->lock, 
-                                          apr_time_from_msec(20));
-                status = h2_ngn_shed_pull_request(shed, ngn, capacity, 1, pr);
-            }
-        }
-        else {
-            status = h2_ngn_shed_pull_request(shed, ngn, capacity,
-                                              want_shutdown, pr);
         }
-        leave_mutex(m, acquired);
     }
+    else {
+        status = h2_ngn_shed_pull_request(shed, ngn, capacity,
+                                          want_shutdown, pr);
+    }
+
+    H2_MPLX_LEAVE(m);
     return status;
 }
  
 void h2_mplx_req_engine_done(h2_req_engine *ngn, conn_rec *r_conn,
                              apr_status_t status)
 {
     h2_task *task = h2_ctx_cget_task(r_conn);
     
     if (task) {
         h2_mplx *m = task->mplx;
-        int acquired;
+        h2_stream *stream;
 
-        if (enter_mutex(m, &acquired) == APR_SUCCESS) {
-            ngn_out_update_windows(m, ngn);
-            h2_ngn_shed_done_task(m->ngn_shed, ngn, task);
-            if (status != APR_SUCCESS && h2_task_can_redo(task) 
-                && !h2_ihash_get(m->redo_tasks, task->stream_id)) {
-                h2_ihash_add(m->redo_tasks, task);
-            }
-            if (task->engine) { 
-                /* cannot report that as done until engine returns */
-            }
-            else {
-                task_done(m, task, ngn);
-            }
-            /* Take this opportunity to update output consummation 
-             * for this engine */
-            leave_mutex(m, acquired);
+        H2_MPLX_ENTER_ALWAYS(m);
+
+        stream = h2_ihash_get(m->streams, task->stream_id);
+        
+        ngn_out_update_windows(m, ngn);
+        h2_ngn_shed_done_task(m->ngn_shed, ngn, task);
+        
+        if (status != APR_SUCCESS && stream 
+            && h2_task_can_redo(task) 
+            && !h2_ihash_get(m->sredo, stream->id)) {
+            h2_ihash_add(m->sredo, stream);
+        }
+
+        if (task->engine) { 
+            /* cannot report that as done until engine returns */
+        }
+        else {
+            task_done(m, task, ngn);
         }
+
+        H2_MPLX_LEAVE(m);
     }
 }
 
 /*******************************************************************************
  * mplx master events dispatching
  ******************************************************************************/
 
-static int update_window(void *ctx, void *val)
+int h2_mplx_has_master_events(h2_mplx *m)
 {
-    input_consumed_signal(ctx, val);
-    return 1;
+    return apr_atomic_read32(&m->event_pending) > 0;
 }
 
 apr_status_t h2_mplx_dispatch_master_events(h2_mplx *m, 
                                             stream_ev_callback *on_resume, 
                                             void *on_ctx)
 {
-    apr_status_t status;
-    int acquired;
-    int ids[100];
     h2_stream *stream;
-    size_t i, n;
+    int n;
     
-    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c, 
-                      "h2_mplx(%ld): dispatch events", m->id);
-                      
-        /* update input windows for streams */
-        h2_ihash_iter(m->streams, update_window, m);
-        if (on_resume && !h2_iq_empty(m->readyq)) {
-            n = h2_iq_mshift(m->readyq, ids, H2_ALEN(ids));
-            for (i = 0; i < n; ++i) {
-                stream = h2_ihash_get(m->streams, ids[i]);
-                if (stream) {
-                    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c, 
-                                  "h2_mplx(%ld-%d): on_resume", 
-                                  m->id, stream->id);
-                    on_resume(on_ctx, stream);
-                }
-            }
-        }
-        
-        leave_mutex(m, acquired);
+    ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c, 
+                  "h2_mplx(%ld): dispatch events", m->id);        
+    apr_atomic_set32(&m->event_pending, 0);
+
+    /* update input windows for streams */
+    h2_ihash_iter(m->streams, report_consumption_iter, m);    
+    purge_streams(m, 1);
+    
+    n = h2_fifo_count(m->readyq);
+    while (n > 0 
+           && (h2_fifo_try_pull(m->readyq, (void**)&stream) == APR_SUCCESS)) {
+        --n;
+        on_resume(on_ctx, stream);
     }
-    return status;
+    
+    return APR_SUCCESS;
 }
 
-apr_status_t h2_mplx_keep_active(h2_mplx *m, int stream_id)
+apr_status_t h2_mplx_keep_active(h2_mplx *m, h2_stream *stream)
 {
-    apr_status_t status;
-    int acquired;
-    
-    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
-        h2_stream *s = h2_ihash_get(m->streams, stream_id);
-        if (s) {
-            h2_iq_append(m->readyq, stream_id);
-        }
-        leave_mutex(m, acquired);
-    }
-    return status;
+    check_data_for(m, stream, 1);
+    return APR_SUCCESS;
 }
 
 int h2_mplx_awaits_data(h2_mplx *m)
 {
-    apr_status_t status;
-    int acquired, waiting = 1;
+    int waiting = 1;
      
-    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
-        if (h2_ihash_empty(m->streams)) {
-            waiting = 0;
-        }
-        if (h2_iq_empty(m->q) && h2_ihash_empty(m->tasks)) {
-            waiting = 0;
-        }
-        leave_mutex(m, acquired);
+    H2_MPLX_ENTER_ALWAYS(m);
+
+    if (h2_ihash_empty(m->streams)) {
+        waiting = 0;
+    }
+    else if (!m->tasks_active && !h2_fifo_count(m->readyq)
+             && h2_iq_empty(m->q)) {
+        waiting = 0;
     }
+
+    H2_MPLX_LEAVE(m);
     return waiting;
 }
