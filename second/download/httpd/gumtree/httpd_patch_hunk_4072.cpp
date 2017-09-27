  */
 
 #include <assert.h>
 
 #include <apr_thread_cond.h>
 
+#include <mpm_common.h>
 #include <httpd.h>
 #include <http_core.h>
 #include <http_log.h>
 
+#include "h2.h"
 #include "h2_private.h"
 #include "h2_conn.h"
+#include "h2_ctx.h"
+#include "h2_h2.h"
 #include "h2_mplx.h"
-#include "h2_request.h"
 #include "h2_task.h"
 #include "h2_worker.h"
 
 static void* APR_THREAD_FUNC execute(apr_thread_t *thread, void *wctx)
 {
     h2_worker *worker = (h2_worker *)wctx;
-    apr_status_t status = APR_SUCCESS;
-    h2_mplx *m;
-    (void)thread;
+    int sticky;
     
-    /* Furthermore, other code might want to see the socket for
-     * this connection. Allocate one without further function...
-     */
-    status = apr_socket_create(&worker->socket,
-                               APR_INET, SOCK_STREAM,
-                               APR_PROTO_TCP, worker->pool);
-    if (status != APR_SUCCESS) {
-        ap_log_perror(APLOG_MARK, APLOG_ERR, status, worker->pool,
-                      APLOGNO(02948) "h2_worker(%d): alloc socket", 
-                      worker->id);
-        worker->worker_done(worker, worker->ctx);
-        return NULL;
-    }
-    
-    worker->task = NULL;
-    m = NULL;
     while (!worker->aborted) {
-        status = worker->get_next(worker, &m, &worker->task, worker->ctx);
+        h2_task *task;
         
-        if (worker->task) {            
-            h2_task_do(worker->task, worker);
-            worker->task = NULL;
+        /* Get a h2_task from the main workers queue. */
+        worker->get_next(worker, worker->ctx, &task, &sticky);
+        while (task) {
+            h2_task_do(task, worker->io);
+            
+            /* if someone was waiting on this task, time to wake up */
             apr_thread_cond_signal(worker->io);
+            /* report the task done and maybe get another one from the same
+             * mplx (= master connection), if we can be sticky. 
+             */
+            if (sticky && !worker->aborted) {
+                h2_mplx_task_done(task->mplx, task, &task);
+            }
+            else {
+                h2_mplx_task_done(task->mplx, task, NULL);
+                task = NULL;
+            }
         }
     }
 
-    status = worker->get_next(worker, &m, NULL, worker->ctx);
-    m = NULL;
-    
-    if (worker->socket) {
-        apr_socket_close(worker->socket);
-        worker->socket = NULL;
-    }
-    
     worker->worker_done(worker, worker->ctx);
     return NULL;
 }
 
-static apr_status_t cleanup_join_thread(void *ctx)
-{
-    h2_worker *w = ctx;
-    /* do the join only when the worker is aborted. Otherwise,
-     * we are probably in a process shutdown.
-     */
-    if (w->thread && w->aborted) {
-        apr_status_t rv;
-        apr_thread_join(&rv, w->thread);
-    }
-    return APR_SUCCESS;
-}
-
 h2_worker *h2_worker_create(int id,
                             apr_pool_t *parent_pool,
                             apr_threadattr_t *attr,
                             h2_worker_mplx_next_fn *get_next,
                             h2_worker_done_fn *worker_done,
                             void *ctx)
 {
     apr_allocator_t *allocator = NULL;
     apr_pool_t *pool = NULL;
     h2_worker *w;
     apr_status_t status;
     
-    status = apr_allocator_create(&allocator);
-    if (status != APR_SUCCESS) {
-        return NULL;
-    }
-    
-    status = apr_pool_create_ex(&pool, parent_pool, NULL, allocator);
-    if (status != APR_SUCCESS) {
-        return NULL;
-    }
+    apr_allocator_create(&allocator);
+    apr_allocator_max_free_set(allocator, ap_max_mem_free);
+    apr_pool_create_ex(&pool, parent_pool, NULL, allocator);
+    apr_pool_tag(pool, "h2_worker");
     apr_allocator_owner_set(allocator, pool);
 
     w = apr_pcalloc(pool, sizeof(h2_worker));
     if (w) {
         APR_RING_ELEM_INIT(w, link);
         
