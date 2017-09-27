 #include "h2_ctx.h"
 #include "h2_h2.h"
 #include "h2_mplx.h"
 #include "h2_ngn_shed.h"
 #include "h2_request.h"
 #include "h2_stream.h"
+#include "h2_session.h"
 #include "h2_task.h"
-#include "h2_worker.h"
 #include "h2_workers.h"
 #include "h2_util.h"
 
 
-static void h2_beam_log(h2_bucket_beam *beam, int id, const char *msg, 
-                        conn_rec *c, int level)
-{
-    if (beam && APLOG_C_IS_LEVEL(c,level)) {
-        char buffer[2048];
-        apr_size_t off = 0;
-        
-        off += apr_snprintf(buffer+off, H2_ALEN(buffer)-off, "cl=%d, ", beam->closed);
-        off += h2_util_bl_print(buffer+off, H2_ALEN(buffer)-off, "red", ", ", &beam->send_list);
-        off += h2_util_bb_print(buffer+off, H2_ALEN(buffer)-off, "green", ", ", beam->recv_buffer);
-        off += h2_util_bl_print(buffer+off, H2_ALEN(buffer)-off, "hold", ", ", &beam->hold_list);
-        off += h2_util_bl_print(buffer+off, H2_ALEN(buffer)-off, "purge", "", &beam->purge_list);
-
-        ap_log_cerror(APLOG_MARK, level, 0, c, "beam(%ld-%d): %s %s", 
-                      c->id, id, msg, buffer);
-    }
-}
-
-/* utility for iterating over ihash task sets */
+/* utility for iterating over ihash stream sets */
 typedef struct {
     h2_mplx *m;
-    h2_task *task;
+    h2_stream *stream;
     apr_time_t now;
-} task_iter_ctx;
-
-/* NULL or the mutex hold by this thread, used for recursive calls
- */
-static apr_threadkey_t *thread_lock;
+} stream_iter_ctx;
 
 apr_status_t h2_mplx_child_init(apr_pool_t *pool, server_rec *s)
 {
-    return apr_threadkey_private_create(&thread_lock, NULL, pool);
+    return APR_SUCCESS;
 }
 
-static apr_status_t enter_mutex(h2_mplx *m, int *pacquired)
-{
-    apr_status_t status;
-    void *mutex = NULL;
-    
-    /* Enter the mutex if this thread already holds the lock or
-     * if we can acquire it. Only on the later case do we unlock
-     * onleaving the mutex.
-     * This allow recursive entering of the mutex from the saem thread,
-     * which is what we need in certain situations involving callbacks
-     */
-    ap_assert(m);
-    apr_threadkey_private_get(&mutex, thread_lock);
-    if (mutex == m->lock) {
-        *pacquired = 0;
-        return APR_SUCCESS;
-    }
+#define H2_MPLX_ENTER(m)    \
+    do { apr_status_t rv; if ((rv = apr_thread_mutex_lock(m->lock)) != APR_SUCCESS) {\
+        return rv;\
+    } } while(0)
 
-    ap_assert(m->lock);
-    status = apr_thread_mutex_lock(m->lock);
-    *pacquired = (status == APR_SUCCESS);
-    if (*pacquired) {
-        apr_threadkey_private_set(m->lock, thread_lock);
-    }
-    return status;
-}
+#define H2_MPLX_LEAVE(m)    \
+    apr_thread_mutex_unlock(m->lock)
+ 
+#define H2_MPLX_ENTER_ALWAYS(m)    \
+    apr_thread_mutex_lock(m->lock)
 
-static void leave_mutex(h2_mplx *m, int acquired)
-{
-    if (acquired) {
-        apr_threadkey_private_set(NULL, thread_lock);
-        apr_thread_mutex_unlock(m->lock);
-    }
-}
+#define H2_MPLX_ENTER_MAYBE(m, lock)    \
+    if (lock) apr_thread_mutex_lock(m->lock)
 
-static void beam_leave(void *ctx, apr_thread_mutex_t *lock)
-{
-    leave_mutex(ctx, 1);
-}
+#define H2_MPLX_LEAVE_MAYBE(m, lock)    \
+    if (lock) apr_thread_mutex_unlock(m->lock)
 
-static apr_status_t beam_enter(void *ctx, h2_beam_lock *pbl)
-{
-    h2_mplx *m = ctx;
-    int acquired;
-    apr_status_t status;
-    
-    status = enter_mutex(m, &acquired);
-    if (status == APR_SUCCESS) {
-        pbl->mutex = m->lock;
-        pbl->leave = acquired? beam_leave : NULL;
-        pbl->leave_ctx = m;
-    }
-    return status;
-}
+static void check_data_for(h2_mplx *m, h2_stream *stream, int lock);
 
 static void stream_output_consumed(void *ctx, 
                                    h2_bucket_beam *beam, apr_off_t length)
 {
-    h2_task *task = ctx;
+    h2_stream *stream = ctx;
+    h2_task *task = stream->task;
+    
     if (length > 0 && task && task->assigned) {
         h2_req_engine_out_consumed(task->assigned, task->c, length); 
     }
 }
 
-static void stream_input_consumed(void *ctx, 
-                                  h2_bucket_beam *beam, apr_off_t length)
-{
-    h2_mplx *m = ctx;
-    if (m->input_consumed && length) {
-        m->input_consumed(m->input_consumed_ctx, beam->id, length);
-    }
-}
-
-static int can_beam_file(void *ctx, h2_bucket_beam *beam,  apr_file_t *file)
+static void stream_input_ev(void *ctx, h2_bucket_beam *beam)
 {
-    h2_mplx *m = ctx;
-    if (m->tx_handles_reserved > 0) {
-        --m->tx_handles_reserved;
-        ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c,
-                      "h2_mplx(%ld-%d): beaming file %s, tx_avail %d", 
-                      m->id, beam->id, beam->tag, m->tx_handles_reserved);
-        return 1;
-    }
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE3, 0, m->c,
-                  "h2_mplx(%ld-%d): can_beam_file denied on %s", 
-                  m->id, beam->id, beam->tag);
-    return 0;
+    h2_stream *stream = ctx;
+    h2_mplx *m = stream->session->mplx;
+    apr_atomic_set32(&m->event_pending, 1); 
 }
 
-static void have_out_data_for(h2_mplx *m, h2_stream *stream, int response);
-static void task_destroy(h2_mplx *m, h2_task *task, int called_from_master);
-
-static void check_tx_reservation(h2_mplx *m) 
+static void stream_input_consumed(void *ctx, h2_bucket_beam *beam, apr_off_t length)
 {
-    if (m->tx_handles_reserved <= 0) {
-        m->tx_handles_reserved += h2_workers_tx_reserve(m->workers, 
-            H2MIN(m->tx_chunk_size, h2_ihash_count(m->tasks)));
-    }
+    h2_stream_in_consumed(ctx, length);
 }
 
-static void check_tx_free(h2_mplx *m) 
+static void stream_joined(h2_mplx *m, h2_stream *stream)
 {
-    if (m->tx_handles_reserved > m->tx_chunk_size) {
-        apr_size_t count = m->tx_handles_reserved - m->tx_chunk_size;
-        m->tx_handles_reserved = m->tx_chunk_size;
-        h2_workers_tx_free(m->workers, count);
-    }
-    else if (m->tx_handles_reserved && h2_ihash_empty(m->tasks)) {
-        h2_workers_tx_free(m->workers, m->tx_handles_reserved);
-        m->tx_handles_reserved = 0;
-    }
+    ap_assert(!stream->task || stream->task->worker_done);
+    
+    h2_ihash_remove(m->shold, stream->id);
+    h2_ihash_add(m->spurge, stream);
 }
 
-static int purge_stream(void *ctx, void *val) 
+static void stream_cleanup(h2_mplx *m, h2_stream *stream)
 {
-    h2_mplx *m = ctx;
-    h2_stream *stream = val;
-    int stream_id = stream->id;
-    h2_task *task;
+    ap_assert(stream->state == H2_SS_CLEANUP);
 
-    /* stream_cleanup clears all buffers and destroys any buckets
-     * that might hold references into task space. Needs to be done
-     * before task destruction, otherwise it will complain. */
-    h2_stream_cleanup(stream);
-    
-    task = h2_ihash_get(m->tasks, stream_id);    
-    if (task) {
-        task_destroy(m, task, 1);
+    if (stream->input) {
+        h2_beam_on_consumed(stream->input, NULL, NULL, NULL);
+        h2_beam_abort(stream->input);
     }
-    
-    h2_stream_destroy(stream);
-    h2_ihash_remove(m->spurge, stream_id);
-    return 0;
-}
-
-static void purge_streams(h2_mplx *m)
-{
-    if (!h2_ihash_empty(m->spurge)) {
-        while(!h2_ihash_iter(m->spurge, purge_stream, m)) {
-            /* repeat until empty */
-        }
-        h2_ihash_clear(m->spurge);
+    if (stream->output) {
+        h2_beam_on_produced(stream->output, NULL, NULL);
+        h2_beam_leave(stream->output);
     }
-}
+    
+    h2_stream_cleanup(stream);
 
-static void h2_mplx_destroy(h2_mplx *m)
-{
-    conn_rec **pslave;
-    ap_assert(m);
-    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, m->c,
-                  "h2_mplx(%ld): destroy, tasks=%d", 
-                  m->id, (int)h2_ihash_count(m->tasks));
-    check_tx_free(m);
-    
-    while (m->spare_slaves->nelts > 0) {
-        pslave = (conn_rec **)apr_array_pop(m->spare_slaves);
-        h2_slave_destroy(*pslave);
+    h2_iq_remove(m->q, stream->id);
+    h2_fifo_remove(m->readyq, stream);
+    h2_ihash_remove(m->streams, stream->id);
+    h2_ihash_add(m->shold, stream);
+    
+    if (!stream->task || stream->task->worker_done) {
+        stream_joined(m, stream);
     }
-    if (m->pool) {
-        apr_pool_destroy(m->pool);
+    else if (stream->task) {
+        stream->task->c->aborted = 1;
+        apr_thread_cond_broadcast(m->task_thawed);
     }
 }
 
 /**
  * A h2_mplx needs to be thread-safe *and* if will be called by
  * the h2_session thread *and* the h2_worker threads. Therefore:
