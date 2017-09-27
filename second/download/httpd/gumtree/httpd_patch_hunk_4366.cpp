     input_consumed_signal(ctx, val);
     return 1;
 }
 
 apr_status_t h2_mplx_dispatch_master_events(h2_mplx *m, 
                                             stream_ev_callback *on_resume, 
-                                            stream_ev_callback *on_response, 
                                             void *on_ctx)
 {
     apr_status_t status;
     int acquired;
-    int streams[32];
+    int ids[100];
     h2_stream *stream;
-    h2_task *task;
     size_t i, n;
     
-    AP_DEBUG_ASSERT(m);
     if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
         ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c, 
                       "h2_mplx(%ld): dispatch events", m->id);
                       
         /* update input windows for streams */
         h2_ihash_iter(m->streams, update_window, m);
-
-        if (on_response && !h2_ihash_empty(m->sready)) {
-            n = h2_ihash_ishift(m->sready, streams, H2_ALEN(streams));
-            for (i = 0; i < n; ++i) {
-                stream = h2_ihash_get(m->streams, streams[i]);
-                if (!stream) {
-                    continue;
-                }
-                ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c, 
-                              "h2_mplx(%ld-%d): on_response", 
-                              m->id, stream->id);
-                task = h2_ihash_get(m->tasks, stream->id);
-                if (task) {
-                    task->submitted = 1;
-                    if (task->rst_error) {
-                        h2_stream_rst(stream, task->rst_error);
-                    }
-                    else {
-                        AP_DEBUG_ASSERT(task->response);
-                        h2_stream_set_response(stream, task->response, task->output.beam);
-                    }
-                }
-                else {
-                    /* We have the stream ready without a task. This happens
-                     * when we fail streams early. A response should already
-                     * be present.  */
-                    AP_DEBUG_ASSERT(stream->response || stream->rst_error);
-                }
-                status = on_response(on_ctx, stream->id);
-            }
-        }
-
-        if (on_resume && !h2_ihash_empty(m->sresume)) {
-            n = h2_ihash_ishift(m->sresume, streams, H2_ALEN(streams));
+        if (on_resume && !h2_iq_empty(m->readyq)) {
+            n = h2_iq_mshift(m->readyq, ids, H2_ALEN(ids));
             for (i = 0; i < n; ++i) {
-                stream = h2_ihash_get(m->streams, streams[i]);
-                if (!stream) {
-                    continue;
+                stream = h2_ihash_get(m->streams, ids[i]);
+                if (stream) {
+                    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c, 
+                                  "h2_mplx(%ld-%d): on_resume", 
+                                  m->id, stream->id);
+                    on_resume(on_ctx, stream);
                 }
-                ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c, 
-                              "h2_mplx(%ld-%d): on_resume", 
-                              m->id, stream->id);
-                h2_stream_set_suspended(stream, 0);
-                status = on_resume(on_ctx, stream->id);
             }
         }
         
         leave_mutex(m, acquired);
     }
     return status;
 }
 
-static void output_produced(void *ctx, h2_bucket_beam *beam, apr_off_t bytes)
+apr_status_t h2_mplx_keep_active(h2_mplx *m, int stream_id)
 {
-    h2_mplx *m = ctx;
     apr_status_t status;
-    h2_stream *stream;
     int acquired;
     
-    AP_DEBUG_ASSERT(m);
     if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
-        stream = h2_ihash_get(m->streams, beam->id);
-        if (stream && h2_stream_is_suspended(stream)) {
-            h2_ihash_add(m->sresume, stream);
-            h2_beam_on_produced(beam, NULL, NULL);
-            have_out_data_for(m, beam->id);
+        h2_stream *s = h2_ihash_get(m->streams, stream_id);
+        if (s) {
+            h2_iq_append(m->readyq, stream_id);
         }
         leave_mutex(m, acquired);
     }
+    return status;
 }
 
-apr_status_t h2_mplx_suspend_stream(h2_mplx *m, int stream_id)
+int h2_mplx_awaits_data(h2_mplx *m)
 {
     apr_status_t status;
-    h2_stream *stream;
-    h2_task *task;
-    int acquired;
-    
-    AP_DEBUG_ASSERT(m);
+    int acquired, waiting = 1;
+     
     if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
-        stream = h2_ihash_get(m->streams, stream_id);
-        if (stream) {
-            h2_stream_set_suspended(stream, 1);
-            task = h2_ihash_get(m->tasks, stream->id);
-            if (stream->started && (!task || task->worker_done)) {
-                h2_ihash_add(m->sresume, stream);
-            }
-            else {
-                /* register callback so that we can resume on new output */
-                h2_beam_on_produced(task->output.beam, output_produced, m);
-            }
+        if (h2_ihash_empty(m->streams)) {
+            waiting = 0;
+        }
+        if (h2_iq_empty(m->q) && h2_ihash_empty(m->tasks)) {
+            waiting = 0;
         }
         leave_mutex(m, acquired);
     }
-    return status;
+    return waiting;
 }
