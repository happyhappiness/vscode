     }
 
     m = apr_pcalloc(parent, sizeof(h2_mplx));
     if (m) {
         m->id = c->id;
         APR_RING_ELEM_INIT(m, link);
-        m->refs = 1;
         m->c = c;
         apr_pool_create_ex(&m->pool, parent, NULL, allocator);
         if (!m->pool) {
             return NULL;
         }
+        apr_pool_tag(m->pool, "h2_mplx");
         apr_allocator_owner_set(allocator, m->pool);
         
         status = apr_thread_mutex_create(&m->lock, APR_THREAD_MUTEX_DEFAULT,
                                          m->pool);
         if (status != APR_SUCCESS) {
             h2_mplx_destroy(m);
             return NULL;
         }
         
+        status = apr_thread_cond_create(&m->task_thawed, m->pool);
+        if (status != APR_SUCCESS) {
+            h2_mplx_destroy(m);
+            return NULL;
+        }
+    
         m->bucket_alloc = apr_bucket_alloc_create(m->pool);
-        
-        m->q = h2_tq_create(m->pool, h2_config_geti(conf, H2_CONF_MAX_STREAMS));
+        m->max_streams = h2_config_geti(conf, H2_CONF_MAX_STREAMS);
+        m->stream_max_mem = h2_config_geti(conf, H2_CONF_STREAM_MAX_MEM);
+        m->q = h2_iq_create(m->pool, m->max_streams);
         m->stream_ios = h2_io_set_create(m->pool);
         m->ready_ios = h2_io_set_create(m->pool);
-        m->stream_max_mem = h2_config_geti(conf, H2_CONF_STREAM_MAX_MEM);
+        m->stream_timeout = stream_timeout;
         m->workers = workers;
+        m->workers_max = workers->max_workers;
+        m->workers_def_limit = 4;
+        m->workers_limit = m->workers_def_limit;
+        m->last_limit_change = m->last_idle_block = apr_time_now();
+        m->limit_change_interval = apr_time_from_msec(200);
         
-        m->file_handles_allowed = h2_config_geti(conf, H2_CONF_SESSION_FILES);
+        m->tx_handles_reserved = 0;
+        m->tx_chunk_size = 4;
+        
+        m->spare_slaves = apr_array_make(m->pool, 10, sizeof(conn_rec*));
+        
+        m->ngn_shed = h2_ngn_shed_create(m->pool, m->c, m->max_streams, 
+                                         m->stream_max_mem);
+        h2_ngn_shed_set_ctx(m->ngn_shed , m);
     }
     return m;
 }
 
-static void release(h2_mplx *m, int lock)
+apr_uint32_t h2_mplx_shutdown(h2_mplx *m)
 {
-    if (lock) {
-        apr_thread_mutex_lock(m->lock);
-        --m->refs;
-        if (m->join_wait) {
-            apr_thread_cond_signal(m->join_wait);
-        }
-        apr_thread_mutex_unlock(m->lock);
-    }
-    else {
-        --m->refs;
+    int acquired, max_stream_started = 0;
+    
+    if (enter_mutex(m, &acquired) == APR_SUCCESS) {
+        max_stream_started = m->max_stream_started;
+        /* Clear schedule queue, disabling existing streams from starting */ 
+        h2_iq_clear(m->q);
+        leave_mutex(m, acquired);
     }
+    return max_stream_started;
 }
 
-void h2_mplx_reference(h2_mplx *m)
+static void workers_register(h2_mplx *m)
 {
-    apr_thread_mutex_lock(m->lock);
-    ++m->refs;
-    apr_thread_mutex_unlock(m->lock);
-}
-
-void h2_mplx_release(h2_mplx *m)
-{
-    release(m, 1);
-}
-
-static void workers_register(h2_mplx *m) {
-    /* Initially, there was ref count increase for this as well, but
-     * this is not needed, even harmful.
-     * h2_workers is only a hub for all the h2_worker instances.
+    /* h2_workers is only a hub for all the h2_worker instances.
      * At the end-of-life of this h2_mplx, we always unregister at
      * the workers. The thing to manage are all the h2_worker instances
      * out there. Those may hold a reference to this h2_mplx and we cannot
      * call them to unregister.
      * 
      * Therefore: ref counting for h2_workers in not needed, ref counting
      * for h2_worker using this is critical.
      */
+    m->need_registration = 0;
     h2_workers_register(m->workers, m);
 }
 
-static void workers_unregister(h2_mplx *m) {
-    h2_workers_unregister(m->workers, m);
-}
-
-static int io_process_events(h2_mplx *m, h2_io *io) {
+static int io_in_consumed_signal(h2_mplx *m, h2_io *io)
+{
     if (io->input_consumed && m->input_consumed) {
         m->input_consumed(m->input_consumed_ctx, 
                           io->id, io->input_consumed);
         io->input_consumed = 0;
         return 1;
     }
     return 0;
 }
 
+static int io_out_consumed_signal(h2_mplx *m, h2_io *io)
+{
+    if (io->output_consumed && io->task && io->task->assigned) {
+        h2_req_engine_out_consumed(io->task->assigned, io->task->c, 
+                                   io->output_consumed);
+        io->output_consumed = 0;
+        return 1;
+    }
+    return 0;
+}
 
 static void io_destroy(h2_mplx *m, h2_io *io, int events)
 {
-    apr_pool_t *pool = io->pool;
+    int reuse_slave;
     
     /* cleanup any buffered input */
     h2_io_in_shutdown(io);
     if (events) {
         /* Process outstanding events before destruction */
-        io_process_events(m, io);
+        io_in_consumed_signal(m, io);
     }
     
-    io->pool = NULL;    
     /* The pool is cleared/destroyed which also closes all
      * allocated file handles. Give this count back to our
      * file handle pool. */
-    m->file_handles_allowed += io->files_handles_owned;
+    m->tx_handles_reserved += io->files_handles_owned;
+
     h2_io_set_remove(m->stream_ios, io);
     h2_io_set_remove(m->ready_ios, io);
-    h2_io_destroy(io);
-    
-    if (pool) {
-        apr_pool_clear(pool);
-        if (m->spare_pool) {
-            apr_pool_destroy(m->spare_pool);
+    if (m->redo_ios) {
+        h2_io_set_remove(m->redo_ios, io);
+    }
+
+    reuse_slave = ((m->spare_slaves->nelts < m->spare_slaves->nalloc)
+                    && !io->rst_error && io->eor);
+    if (io->task) {
+        conn_rec *slave = io->task->c;
+        h2_task_destroy(io->task);
+        io->task = NULL;
+        
+        if (reuse_slave && slave->keepalive == AP_CONN_KEEPALIVE) {
+            apr_bucket_delete(io->eor);
+            io->eor = NULL;
+            APR_ARRAY_PUSH(m->spare_slaves, conn_rec*) = slave;
         }
-        m->spare_pool = pool;
+        else {
+            slave->sbh = NULL;
+            h2_slave_destroy(slave, NULL);
+        }
+    }
+
+    if (io->pool) {
+        apr_pool_destroy(io->pool);
     }
+
+    check_tx_free(m);
 }
 
 static int io_stream_done(h2_mplx *m, h2_io *io, int rst_error) 
 {
     /* Remove io from ready set, we will never submit it */
     h2_io_set_remove(m->ready_ios, io);
-    if (io->task_done || h2_tq_remove(m->q, io->id)) {
+    if (!io->worker_started || io->worker_done) {
         /* already finished or not even started yet */
+        h2_iq_remove(m->q, io->id);
         io_destroy(m, io, 1);
         return 0;
     }
     else {
         /* cleanup once task is done */
-        io->orphaned = 1;
-        if (rst_error) {
-            h2_io_rst(io, rst_error);
-        }
+        h2_io_make_orphaned(io, rst_error);
         return 1;
     }
 }
 
-static int stream_done_iter(void *ctx, h2_io *io) {
+static int stream_done_iter(void *ctx, h2_io *io)
+{
     return io_stream_done((h2_mplx*)ctx, io, 0);
 }
 
+static int stream_print(void *ctx, h2_io *io)
+{
+    h2_mplx *m = ctx;
+    if (io && io->request) {
+        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, /* NO APLOGNO */
+                      "->03198: h2_stream(%ld-%d): %s %s %s -> %s %d"
+                      "[orph=%d/started=%d/done=%d/eos_in=%d/eos_out=%d]", 
+                      m->id, io->id, 
+                      io->request->method, io->request->authority, io->request->path,
+                      io->response? "http" : (io->rst_error? "reset" : "?"),
+                      io->response? io->response->http_status : io->rst_error,
+                      io->orphaned, io->worker_started, io->worker_done,
+                      io->eos_in, io->eos_out);
+    }
+    else if (io) {
+        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, /* NO APLOGNO */
+                      "->03198: h2_stream(%ld-%d): NULL -> %s %d"
+                      "[orph=%d/started=%d/done=%d/eos_in=%d/eos_out=%d]", 
+                      m->id, io->id, 
+                      io->response? "http" : (io->rst_error? "reset" : "?"),
+                      io->response? io->response->http_status : io->rst_error,
+                      io->orphaned, io->worker_started, io->worker_done,
+                      io->eos_in, io->eos_out);
+    }
+    else {
+        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, /* NO APLOGNO */
+                      "->03198: h2_stream(%ld-NULL): NULL", m->id);
+    }
+    return 1;
+}
+
 apr_status_t h2_mplx_release_and_join(h2_mplx *m, apr_thread_cond_t *wait)
 {
     apr_status_t status;
+    int acquired;
+
+    h2_workers_unregister(m->workers, m);
     
-    workers_unregister(m);
-    status = apr_thread_mutex_lock(m->lock);
-    if (APR_SUCCESS == status) {
+    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
+        int i, wait_secs = 5;
+        
+        /* disable WINDOW_UPDATE callbacks */
+        h2_mplx_set_consumed_cb(m, NULL, NULL);
+        
+        h2_iq_clear(m->q);
+        apr_thread_cond_broadcast(m->task_thawed);
         while (!h2_io_set_iter(m->stream_ios, stream_done_iter, m)) {
-            /* iterator until all h2_io have been orphaned or destroyed */
+            /* iterate until all ios have been orphaned or destroyed */
         }
     
-        release(m, 0);
-        while (m->refs > 0) {
+        /* If we still have busy workers, we cannot release our memory
+         * pool yet, as slave connections have child pools of their respective
+         * h2_io's.
+         * Any remaining ios are processed in these workers. Any operation 
+         * they do on their input/outputs will be errored ECONNRESET/ABORTED, 
+         * so processing them should fail and workers *should* return.
+         */
+        for (i = 0; m->workers_busy > 0; ++i) {
             m->join_wait = wait;
-            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c,
-                          "h2_mplx(%ld): release_join, refs=%d, waiting...", 
-                          m->id, m->refs);
-            apr_thread_cond_wait(wait, m->lock);
-        }
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c,
-                      "h2_mplx(%ld): release_join -> destroy, (#ios=%ld)", 
-                      m->id, (long)h2_io_set_size(m->stream_ios));
+            ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
+                          "h2_mplx(%ld): release_join, waiting on %d worker to report back", 
+                          m->id, (int)h2_io_set_size(m->stream_ios));
+                          
+            status = apr_thread_cond_timedwait(wait, m->lock, apr_time_from_sec(wait_secs));
+            if (APR_STATUS_IS_TIMEUP(status)) {
+                if (i > 0) {
+                    /* Oh, oh. Still we wait for assigned  workers to report that 
+                     * they are done. Unless we have a bug, a worker seems to be hanging. 
+                     * If we exit now, all will be deallocated and the worker, once 
+                     * it does return, will walk all over freed memory...
+                     */
+                    ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, APLOGNO(03198)
+                                  "h2_mplx(%ld): release, waiting for %d seconds now for "
+                                  "%d h2_workers to return, have still %d requests outstanding", 
+                                  m->id, i*wait_secs, m->workers_busy,
+                                  (int)h2_io_set_size(m->stream_ios));
+                    if (i == 1) {
+                        h2_io_set_iter(m->stream_ios, stream_print, m);
+                    }
+                }
+                h2_mplx_abort(m);
+                apr_thread_cond_broadcast(m->task_thawed);
+            }
+        }
+        
+        if (!h2_io_set_is_empty(m->stream_ios)) {
+            ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, m->c, 
+                          "h2_mplx(%ld): release_join, %d streams still open", 
+                          m->id, (int)h2_io_set_size(m->stream_ios));
+        }
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, m->c, APLOGNO(03056)
+                      "h2_mplx(%ld): release_join -> destroy", m->id);
+        leave_mutex(m, acquired);
         h2_mplx_destroy(m);
         /* all gone */
-        /*apr_thread_mutex_unlock(m->lock);*/
     }
     return status;
 }
 
 void h2_mplx_abort(h2_mplx *m)
 {
-    apr_status_t status;
+    int acquired;
+    
     AP_DEBUG_ASSERT(m);
-    status = apr_thread_mutex_lock(m->lock);
-    if (APR_SUCCESS == status) {
+    if (!m->aborted && enter_mutex(m, &acquired) == APR_SUCCESS) {
         m->aborted = 1;
-        apr_thread_mutex_unlock(m->lock);
+        h2_ngn_shed_abort(m->ngn_shed);
+        leave_mutex(m, acquired);
     }
 }
 
 apr_status_t h2_mplx_stream_done(h2_mplx *m, int stream_id, int rst_error)
 {
-    apr_status_t status;
+    apr_status_t status = APR_SUCCESS;
+    int acquired;
     
+    /* This maybe called from inside callbacks that already hold the lock.
+     * E.g. when we are streaming out DATA and the EOF triggers the stream
+     * release.
+     */
     AP_DEBUG_ASSERT(m);
-    status = apr_thread_mutex_lock(m->lock);
-    if (APR_SUCCESS == status) {
+    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
         h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
 
         /* there should be an h2_io, once the stream has been scheduled
          * for processing, e.g. when we received all HEADERs. But when
          * a stream is cancelled very early, it will not exist. */
         if (io) {
+            ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c, 
+                          "h2_mplx(%ld-%d): marking stream as done.", 
+                          m->id, stream_id);
             io_stream_done(m, io, rst_error);
         }
-        
-        apr_thread_mutex_unlock(m->lock);
+        leave_mutex(m, acquired);
     }
     return status;
 }
 
-void h2_mplx_task_done(h2_mplx *m, int stream_id)
-{
-    apr_status_t status = apr_thread_mutex_lock(m->lock);
-    if (APR_SUCCESS == status) {
-        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE2, 0, m->c,
-                      "h2_mplx(%ld): task(%d) done", m->id, stream_id);
-        if (io) {
-            io->task_done = 1;
-            if (io->orphaned) {
-                io_destroy(m, io, 0);
-            }
-            else {
-                /* hang around until the stream deregisteres */
-            }
-        }
-        apr_thread_mutex_unlock(m->lock);
-    }
-}
-
 apr_status_t h2_mplx_in_read(h2_mplx *m, apr_read_type_e block,
-                             int stream_id, apr_bucket_brigade *bb,
+                             int stream_id, apr_bucket_brigade *bb, 
+                             apr_table_t *trailers,
                              struct apr_thread_cond_t *iowait)
 {
     apr_status_t status; 
+    int acquired;
+    
     AP_DEBUG_ASSERT(m);
-    if (m->aborted) {
-        return APR_ECONNABORTED;
-    }
-    status = apr_thread_mutex_lock(m->lock);
-    if (APR_SUCCESS == status) {
+    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
         h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
         if (io && !io->orphaned) {
-            io->input_arrived = iowait;
             H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_in_read_pre");
-            status = h2_io_in_read(io, bb, -1);
+            
+            h2_io_signal_init(io, H2_IO_READ, m->stream_timeout, iowait);
+            status = h2_io_in_read(io, bb, -1, trailers);
             while (APR_STATUS_IS_EAGAIN(status) 
                    && !is_aborted(m, &status)
                    && block == APR_BLOCK_READ) {
-                apr_thread_cond_wait(io->input_arrived, m->lock);
-                status = h2_io_in_read(io, bb, -1);
+                ap_log_cerror(APLOG_MARK, APLOG_TRACE2, status, m->c,
+                              "h2_mplx(%ld-%d): wait on in data (BLOCK_READ)", 
+                              m->id, stream_id);
+                status = h2_io_signal_wait(m, io);
+                if (status == APR_SUCCESS) {
+                    status = h2_io_in_read(io, bb, -1, trailers);
+                }
             }
             H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_in_read_post");
-            io->input_arrived = NULL;
+            h2_io_signal_exit(io);
         }
         else {
             status = APR_EOF;
         }
-        apr_thread_mutex_unlock(m->lock);
+        leave_mutex(m, acquired);
     }
     return status;
 }
 
 apr_status_t h2_mplx_in_write(h2_mplx *m, int stream_id, 
-                              apr_bucket_brigade *bb)
+                              const char *data, apr_size_t len, int eos)
 {
     apr_status_t status;
+    int acquired;
+    
     AP_DEBUG_ASSERT(m);
-    if (m->aborted) {
-        return APR_ECONNABORTED;
-    }
-    status = apr_thread_mutex_lock(m->lock);
-    if (APR_SUCCESS == status) {
+    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
         h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
         if (io && !io->orphaned) {
             H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_in_write_pre");
-            status = h2_io_in_write(io, bb);
+            status = h2_io_in_write(io, data, len, eos);
             H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_in_write_post");
-            if (io->input_arrived) {
-                apr_thread_cond_signal(io->input_arrived);
-            }
-            io_process_events(m, io);
+            h2_io_signal(io, H2_IO_READ);
+            io_in_consumed_signal(m, io);
         }
         else {
-            status = APR_EOF;
+            status = APR_ECONNABORTED;
         }
-        apr_thread_mutex_unlock(m->lock);
+        leave_mutex(m, acquired);
     }
     return status;
 }
 
 apr_status_t h2_mplx_in_close(h2_mplx *m, int stream_id)
 {
     apr_status_t status;
+    int acquired;
+    
     AP_DEBUG_ASSERT(m);
-    if (m->aborted) {
-        return APR_ECONNABORTED;
-    }
-    status = apr_thread_mutex_lock(m->lock);
-    if (APR_SUCCESS == status) {
+    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
         h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
         if (io && !io->orphaned) {
             status = h2_io_in_close(io);
             H2_MPLX_IO_IN(APLOG_TRACE2, m, io, "h2_mplx_in_close");
-            if (io->input_arrived) {
-                apr_thread_cond_signal(io->input_arrived);
-            }
-            io_process_events(m, io);
+            h2_io_signal(io, H2_IO_READ);
+            io_in_consumed_signal(m, io);
         }
         else {
             status = APR_ECONNABORTED;
         }
-        apr_thread_mutex_unlock(m->lock);
+        leave_mutex(m, acquired);
     }
     return status;
 }
 
+void h2_mplx_set_consumed_cb(h2_mplx *m, h2_mplx_consumed_cb *cb, void *ctx)
+{
+    m->input_consumed = cb;
+    m->input_consumed_ctx = ctx;
+}
+
 typedef struct {
     h2_mplx * m;
     int streams_updated;
 } update_ctx;
 
 static int update_window(void *ctx, h2_io *io)
 {
     update_ctx *uctx = (update_ctx*)ctx;
-    if (io_process_events(uctx->m, io)) {
+    if (io_in_consumed_signal(uctx->m, io)) {
         ++uctx->streams_updated;
     }
     return 1;
 }
 
-void h2_mplx_set_consumed_cb(h2_mplx *m, h2_mplx_consumed_cb *cb, void *ctx)
-{
-    m->input_consumed = cb;
-    m->input_consumed_ctx = ctx;
-}
-
 apr_status_t h2_mplx_in_update_windows(h2_mplx *m)
 {
     apr_status_t status;
+    int acquired;
+    
     AP_DEBUG_ASSERT(m);
     if (m->aborted) {
         return APR_ECONNABORTED;
     }
-    status = apr_thread_mutex_lock(m->lock);
-    if (APR_SUCCESS == status) {
+    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
         update_ctx ctx;
         
         ctx.m               = m;
         ctx.streams_updated = 0;
 
         status = APR_EAGAIN;
         h2_io_set_iter(m->stream_ios, update_window, &ctx);
         
         if (ctx.streams_updated) {
             status = APR_SUCCESS;
         }
-        apr_thread_mutex_unlock(m->lock);
+        leave_mutex(m, acquired);
     }
     return status;
 }
 
-apr_status_t h2_mplx_out_readx(h2_mplx *m, int stream_id, 
-                               h2_io_data_cb *cb, void *ctx, 
-                               apr_off_t *plen, int *peos,
-                               apr_table_t **ptrailers)
+apr_status_t h2_mplx_out_get_brigade(h2_mplx *m, int stream_id, 
+                                     apr_bucket_brigade *bb, 
+                                     apr_off_t len, apr_table_t **ptrailers)
 {
     apr_status_t status;
-    AP_DEBUG_ASSERT(m);
-    if (m->aborted) {
-        return APR_ECONNABORTED;
-    }
-    status = apr_thread_mutex_lock(m->lock);
-    if (APR_SUCCESS == status) {
-        h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
-        if (io && !io->orphaned) {
-            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_readx_pre");
-            
-            status = h2_io_out_readx(io, cb, ctx, plen, peos);
-            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_readx_post");
-            if (status == APR_SUCCESS && cb && io->output_drained) {
-                apr_thread_cond_signal(io->output_drained);
-            }
-        }
-        else {
-            status = APR_ECONNABORTED;
-        }
-        
-        *ptrailers = (*peos && io->response)? io->response->trailers : NULL;
-        apr_thread_mutex_unlock(m->lock);
-    }
-    return status;
-}
+    int acquired;
 
-apr_status_t h2_mplx_out_read_to(h2_mplx *m, int stream_id, 
-                                 apr_bucket_brigade *bb, 
-                                 apr_off_t *plen, int *peos,
-                                 apr_table_t **ptrailers)
-{
-    apr_status_t status;
     AP_DEBUG_ASSERT(m);
-    if (m->aborted) {
-        return APR_ECONNABORTED;
-    }
-    status = apr_thread_mutex_lock(m->lock);
-    if (APR_SUCCESS == status) {
+    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
         h2_io *io = h2_io_set_get(m->stream_ios, stream_id);
         if (io && !io->orphaned) {
-            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_read_to_pre");
+            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_get_brigade_pre");
             
-            status = h2_io_out_read_to(io, bb, plen, peos);
+            status = h2_io_out_get_brigade(io, bb, len);
             
-            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_read_to_post");
-            if (status == APR_SUCCESS && io->output_drained) {
-                apr_thread_cond_signal(io->output_drained);
+            H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_out_get_brigade_post");
+            if (status == APR_SUCCESS) {
+                h2_io_signal(io, H2_IO_WRITE);
             }
         }
         else {
             status = APR_ECONNABORTED;
         }
-        *ptrailers = (*peos && io->response)? io->response->trailers : NULL;
-        apr_thread_mutex_unlock(m->lock);
+        *ptrailers = io->response? io->response->trailers : NULL;
+        leave_mutex(m, acquired);
     }
     return status;
 }
 
-h2_stream *h2_mplx_next_submit(h2_mplx *m, h2_stream_set *streams)
+h2_stream *h2_mplx_next_submit(h2_mplx *m, h2_ihash_t *streams)
 {
     apr_status_t status;
     h2_stream *stream = NULL;
+    int acquired;
+
     AP_DEBUG_ASSERT(m);
-    if (m->aborted) {
-        return NULL;
-    }
-    status = apr_thread_mutex_lock(m->lock);
-    if (APR_SUCCESS == status) {
-        h2_io *io = h2_io_set_pop_highest_prio(m->ready_ios);
-        if (io) {
-            stream = h2_stream_set_get(streams, io->id);
+    if ((status = enter_mutex(m, &acquired)) == APR_SUCCESS) {
+        h2_io *io = h2_io_set_shift(m->ready_ios);
+        if (io && !m->aborted) {
+            stream = h2_ihash_get(streams, io->id);
             if (stream) {
+                io->submitted = 1;
                 if (io->rst_error) {
                     h2_stream_rst(stream, io->rst_error);
                 }
                 else {
                     AP_DEBUG_ASSERT(io->response);
                     H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_next_submit_pre");
                     h2_stream_set_response(stream, io->response, io->bbout);
                     H2_MPLX_IO_OUT(APLOG_TRACE2, m, io, "h2_mplx_next_submit_post");
                 }
-                
             }
             else {
                 /* We have the io ready, but the stream has gone away, maybe
                  * reset by the client. Should no longer happen since such
                  * streams should clear io's from the ready queue.
                  */
-                ap_log_cerror(APLOG_MARK, APLOG_INFO, 0, m->c, APLOGNO(02953) 
+                ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, m->c, APLOGNO(03347)
                               "h2_mplx(%ld): stream for response %d closed, "
                               "resetting io to close request processing",
                               m->id, io->id);
-                io->orphaned = 1;
-                if (io->task_done) {
+                h2_io_make_orphaned(io, H2_ERR_STREAM_CLOSED);
+                if (!io->worker_started || io->worker_done) {
                     io_destroy(m, io, 1);
                 }
                 else {
                     /* hang around until the h2_task is done, but
                      * shutdown input and send out any events (e.g. window
                      * updates) asap. */
                     h2_io_in_shutdown(io);
-                    h2_io_rst(io, H2_ERR_STREAM_CLOSED);
-                    io_process_events(m, io);
+                    io_in_consumed_signal(m, io);
                 }
             }
             
-            if (io->output_drained) {
-                apr_thread_cond_signal(io->output_drained);
-            }
+            h2_io_signal(io, H2_IO_WRITE);
         }
-        apr_thread_mutex_unlock(m->lock);
+        leave_mutex(m, acquired);
     }
     return stream;
 }
 
 static apr_status_t out_write(h2_mplx *m, h2_io *io, 
-                              ap_filter_t* f, apr_bucket_brigade *bb,
-                              apr_table_t *trailers,
+                              ap_filter_t* f, int blocking,
+                              apr_bucket_brigade *bb,
                               struct apr_thread_cond_t *iowait)
 {
     apr_status_t status = APR_SUCCESS;
     /* We check the memory footprint queued for this stream_id
      * and block if it exceeds our configured limit.
      * We will not split buckets to enforce the limit to the last
      * byte. After all, the bucket is already in memory.
      */
-    while (!APR_BRIGADE_EMPTY(bb) 
-           && (status == APR_SUCCESS)
+    while (status == APR_SUCCESS 
+           && !APR_BRIGADE_EMPTY(bb) 
            && !is_aborted(m, &status)) {
         
-        status = h2_io_out_write(io, bb, m->stream_max_mem, trailers,
-                                 &m->file_handles_allowed);
-        /* Wait for data to drain until there is room again */
-        while (!APR_BRIGADE_EMPTY(bb) 
+        status = h2_io_out_write(io, bb, blocking? m->stream_max_mem : INT_MAX, 
+                                 &m->tx_handles_reserved);
+        io_out_consumed_signal(m, io);
+        
+        /* Wait for data to drain until there is room again or
+         * stream timeout expires */
+        h2_io_signal_init(io, H2_IO_WRITE, m->stream_timeout, iowait);
+        while (status == APR_SUCCESS
+               && !APR_BRIGADE_EMPTY(bb) 
                && iowait
-               && status == APR_SUCCESS
                && (m->stream_max_mem <= h2_io_out_length(io))
                && !is_aborted(m, &status)) {
-            trailers = NULL;
-            io->output_drained = iowait;
+            if (!blocking) {
+                ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, f->c,
+                              "h2_mplx(%ld-%d): incomplete write", 
+                              m->id, io->id);
+                return APR_INCOMPLETE;
+            }
             if (f) {
                 ap_log_cerror(APLOG_MARK, APLOG_TRACE1, status, f->c,
                               "h2_mplx(%ld-%d): waiting for out drain", 
                               m->id, io->id);
             }
-            apr_thread_cond_wait(io->output_drained, m->lock);
-            io->output_drained = NULL;
+            status = h2_io_signal_wait(m, io);
         }
+        h2_io_signal_exit(io);
     }
     apr_brigade_cleanup(bb);
     
     return status;
 }
 
