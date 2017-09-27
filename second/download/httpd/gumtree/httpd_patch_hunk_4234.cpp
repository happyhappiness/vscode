     }
     return task;
 }
 
 static void task_done(h2_mplx *m, h2_task *task, h2_req_engine *ngn)
 {
-    if (task) {
-        h2_io *io = h2_io_set_get(m->stream_ios, task->stream_id);
+    if (task->frozen) {
+        /* this task was handed over to an engine for processing 
+         * and the original worker has finished. That means the 
+         * engine may start processing now. */
+        h2_task_thaw(task);
+        /* we do not want the task to block on writing response
+         * bodies into the mplx. */
+        h2_task_set_io_blocking(task, 0);
+        apr_thread_cond_broadcast(m->task_thawed);
+        return;
+    }
+    else {
+        h2_stream *stream;
         
-        if (task->frozen) {
-            /* this task was handed over to an engine for processing 
-             * and the original worker has finished. That means the 
-             * engine may start processing now. */
-            h2_task_thaw(task);
-            /* we do not want the task to block on writing response
-             * bodies into the mplx. */
-            /* FIXME: this implementation is incomplete. */
-            h2_task_set_io_blocking(task, 0);
-            apr_thread_cond_broadcast(m->task_thawed);
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
+                      "h2_mplx(%ld): task(%s) done", m->id, task->id);
+        out_close(m, task);
+        stream = h2_ihash_get(m->streams, task->stream_id);
+        
+        if (ngn) {
+            apr_off_t bytes = 0;
+            if (task->output.beam) {
+                h2_beam_send(task->output.beam, NULL, APR_NONBLOCK_READ);
+                bytes += h2_beam_get_buffered(task->output.beam);
+            }
+            if (bytes > 0) {
+                /* we need to report consumed and current buffered output
+                 * to the engine. The request will be streamed out or cancelled,
+                 * no more data is coming from it and the engine should update
+                 * its calculations before we destroy this information. */
+                h2_req_engine_out_consumed(ngn, task->c, bytes);
+            }
         }
-        else {
-            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
-                          "h2_mplx(%ld): task(%s) done", m->id, task->id);
-            /* clean our references and report request as done. Signal
-             * that we want another unless we have been aborted */
-            /* TODO: this will keep a worker attached to this h2_mplx as
-             * long as it has requests to handle. Might no be fair to
-             * other mplx's. Perhaps leave after n requests? */
-            h2_mplx_out_close(m, task->stream_id);
-            
-            if (ngn && io) {
-                apr_off_t bytes = io->output_consumed + h2_io_out_length(io);
-                if (bytes > 0) {
-                    /* we need to report consumed and current buffered output
-                     * to the engine. The request will be streamed out or cancelled,
-                     * no more data is coming from it and the engine should update
-                     * its calculations before we destroy this information. */
-                    h2_req_engine_out_consumed(ngn, task->c, bytes);
-                    io->output_consumed = 0;
-                }
+        
+        if (task->engine) {
+            if (!h2_req_engine_is_shutdown(task->engine)) {
+                ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c,
+                              "h2_mplx(%ld): task(%s) has not-shutdown "
+                              "engine(%s)", m->id, task->id, 
+                              h2_req_engine_get_id(task->engine));
             }
-            
-            if (task->engine) {
-                if (!h2_req_engine_is_shutdown(task->engine)) {
-                    ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c,
-                                  "h2_mplx(%ld): task(%s) has not-shutdown "
-                                  "engine(%s)", m->id, task->id, 
-                                  h2_req_engine_get_id(task->engine));
-                }
-                h2_ngn_shed_done_ngn(m->ngn_shed, task->engine);
+            h2_ngn_shed_done_ngn(m->ngn_shed, task->engine);
+        }
+        
+        if (!m->aborted && stream && m->redo_tasks
+            && h2_ihash_get(m->redo_tasks, task->stream_id)) {
+            /* reset and schedule again */
+            h2_task_redo(task);
+            h2_ihash_remove(m->redo_tasks, task->stream_id);
+            h2_iq_add(m->q, task->stream_id, NULL, NULL);
+            return;
+        }
+        
+        task->worker_done = 1;
+        task->done_at = apr_time_now();
+        if (task->output.beam) {
+            h2_beam_on_consumed(task->output.beam, NULL, NULL);
+            h2_beam_mutex_set(task->output.beam, NULL, NULL, NULL);
+        }
+        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
+                      "h2_mplx(%s): request done, %f ms elapsed", task->id, 
+                      (task->done_at - task->started_at) / 1000.0);
+        if (task->started_at > m->last_idle_block) {
+            /* this task finished without causing an 'idle block', e.g.
+             * a block by flow control.
+             */
+            if (task->done_at- m->last_limit_change >= m->limit_change_interval
+                && m->workers_limit < m->workers_max) {
+                /* Well behaving stream, allow it more workers */
+                m->workers_limit = H2MIN(m->workers_limit * 2, 
+                                         m->workers_max);
+                m->last_limit_change = task->done_at;
+                m->need_registration = 1;
+                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
+                              "h2_mplx(%ld): increase worker limit to %d",
+                              m->id, m->workers_limit);
             }
-            
-            if (io) {
-                apr_time_t now = apr_time_now();
-                if (!io->orphaned && m->redo_ios
-                    && h2_io_set_get(m->redo_ios, io->id)) {
-                    /* reset and schedule again */
-                    h2_io_redo(io);
-                    h2_io_set_remove(m->redo_ios, io);
-                    h2_iq_add(m->q, io->id, NULL, NULL);
-                }
-                else {
-                    io->worker_done = 1;
-                    io->done_at = now;
-                    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
-                                  "h2_mplx(%ld): request(%d) done, %f ms"
-                                  " elapsed", m->id, io->id, 
-                                  (io->done_at - io->started_at) / 1000.0);
-                    if (io->started_at > m->last_idle_block) {
-                        /* this task finished without causing an 'idle block', e.g.
-                         * a block by flow control.
-                         */
-                        if (now - m->last_limit_change >= m->limit_change_interval
-                            && m->workers_limit < m->workers_max) {
-                            /* Well behaving stream, allow it more workers */
-                            m->workers_limit = H2MIN(m->workers_limit * 2, 
-                                                     m->workers_max);
-                            m->last_limit_change = now;
-                            m->need_registration = 1;
-                            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
-                                          "h2_mplx(%ld): increase worker limit to %d",
-                                          m->id, m->workers_limit);
-                        }
-                    }
-                }
-                
-                if (io->orphaned) {
-                    io_destroy(m, io, 0);
-                    if (m->join_wait) {
-                        apr_thread_cond_signal(m->join_wait);
-                    }
-                }
-                else {
-                    /* hang around until the stream deregisters */
-                }
+        }
+        
+        if (stream) {
+            /* hang around until the stream deregisters */
+            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
+                          "h2_mplx(%s): task_done, stream still open", 
+                          task->id);
+            if (h2_stream_is_suspended(stream)) {
+                /* more data will not arrive, resume the stream */
+                h2_ihash_add(m->sresume, stream);
+                have_out_data_for(m, stream->id);
+            }
+        }
+        else {
+            /* stream no longer active, was it placed in hold? */
+            stream = h2_ihash_get(m->shold, task->stream_id);
+            if (stream) {
+                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
+                              "h2_mplx(%s): task_done, stream in hold", 
+                              task->id);
+                /* We cannot destroy the stream here since this is 
+                 * called from a worker thread and freeing memory pools
+                 * is only safe in the only thread using it (and its
+                 * parent pool / allocator) */
+                h2_ihash_remove(m->shold, stream->id);
+                h2_ihash_add(m->spurge, stream);
             }
             else {
-                ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c,
-                              "h2_mplx(%ld): task %s without corresp. h2_io",
-                              m->id, task->id);
+                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
+                              "h2_mplx(%s): task_done, stream not found", 
+                              task->id);
+                task_destroy(m, task, 0);
+            }
+            
+            if (m->join_wait) {
+                apr_thread_cond_signal(m->join_wait);
             }
         }
     }
 }
 
 void h2_mplx_task_done(h2_mplx *m, h2_task *task, h2_task **ptask)
