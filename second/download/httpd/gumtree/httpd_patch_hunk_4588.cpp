 #include <http_log.h>
 
 #include "h2.h"
 #include "h2_private.h"
 #include "h2_mplx.h"
 #include "h2_task.h"
-#include "h2_worker.h"
 #include "h2_workers.h"
+#include "h2_util.h"
 
+typedef struct h2_slot h2_slot;
+struct h2_slot {
+    int id;
+    h2_slot *next;
+    h2_workers *workers;
+    int aborted;
+    int sticks;
+    h2_task *task;
+    apr_thread_t *thread;
+    apr_thread_mutex_t *lock;
+    apr_thread_cond_t *not_idle;
+};
 
-static int in_list(h2_workers *workers, h2_mplx *m)
+static h2_slot *pop_slot(h2_slot **phead) 
 {
-    h2_mplx *e;
-    for (e = H2_MPLX_LIST_FIRST(&workers->mplxs); 
-         e != H2_MPLX_LIST_SENTINEL(&workers->mplxs);
-         e = H2_MPLX_NEXT(e)) {
-        if (e == m) {
-            return 1;
+    /* Atomically pop a slot from the list */
+    for (;;) {
+        h2_slot *first = *phead;
+        if (first == NULL) {
+            return NULL;
+        }
+        if (apr_atomic_casptr((void*)phead, first->next, first) == first) {
+            first->next = NULL;
+            return first;
         }
     }
-    return 0;
 }
 
-static void cleanup_zombies(h2_workers *workers, int lock)
+static void push_slot(h2_slot **phead, h2_slot *slot)
 {
-    if (lock) {
-        apr_thread_mutex_lock(workers->lock);
-    }
-    while (!H2_WORKER_LIST_EMPTY(&workers->zombies)) {
-        h2_worker *zombie = H2_WORKER_LIST_FIRST(&workers->zombies);
-        H2_WORKER_REMOVE(zombie);
-        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
-                      "h2_workers: cleanup zombie %d", zombie->id);
-        h2_worker_destroy(zombie);
-    }
-    if (lock) {
-        apr_thread_mutex_unlock(workers->lock);
+    /* Atomically push a slot to the list */
+    ap_assert(!slot->next);
+    for (;;) {
+        h2_slot *next = slot->next = *phead;
+        if (apr_atomic_casptr((void*)phead, slot, next) == next) {
+            return;
+        }
     }
 }
 
-static h2_task *next_task(h2_workers *workers)
+static void* APR_THREAD_FUNC slot_run(apr_thread_t *thread, void *wctx);
+
+static apr_status_t activate_slot(h2_workers *workers, h2_slot *slot) 
 {
-    h2_task *task = NULL;
-    h2_mplx *last = NULL;
-    int has_more;
+    apr_status_t status;
     
-    /* Get the next h2_mplx to process that has a task to hand out.
-     * If it does, place it at the end of the queu and return the
-     * task to the worker.
-     * If it (currently) has no tasks, remove it so that it needs
-     * to register again for scheduling.
-     * If we run out of h2_mplx in the queue, we need to wait for
-     * new mplx to arrive. Depending on how many workers do exist,
-     * we do a timed wait or block indefinitely.
-     */
-    while (!task && !H2_MPLX_LIST_EMPTY(&workers->mplxs)) {
-        h2_mplx *m = H2_MPLX_LIST_FIRST(&workers->mplxs);
-        
-        if (last == m) {
-            break;
+    slot->workers = workers;
+    slot->aborted = 0;
+    slot->task = NULL;
+
+    if (!slot->lock) {
+        status = apr_thread_mutex_create(&slot->lock,
+                                         APR_THREAD_MUTEX_DEFAULT,
+                                         workers->pool);
+        if (status != APR_SUCCESS) {
+            push_slot(&workers->free, slot);
+            return status;
         }
-        H2_MPLX_REMOVE(m);
-        --workers->mplx_count;
-        
-        task = h2_mplx_pop_task(m, &has_more);
-        if (has_more) {
-            H2_MPLX_LIST_INSERT_TAIL(&workers->mplxs, m);
-            ++workers->mplx_count;
-            if (!last) {
-                last = m;
-            }
+    }
+
+    if (!slot->not_idle) {
+        status = apr_thread_cond_create(&slot->not_idle, workers->pool);
+        if (status != APR_SUCCESS) {
+            push_slot(&workers->free, slot);
+            return status;
         }
     }
-    return task;
+    
+    /* thread will either immediately start work or add itself
+     * to the idle queue */
+    apr_thread_create(&slot->thread, workers->thread_attr, slot_run, slot, 
+                      workers->pool);
+    if (!slot->thread) {
+        push_slot(&workers->free, slot);
+        return APR_ENOMEM;
+    }
+    
+    apr_atomic_inc32(&workers->worker_count);
+    return APR_SUCCESS;
+}
+
+static apr_status_t add_worker(h2_workers *workers)
+{
+    h2_slot *slot = pop_slot(&workers->free);
+    if (slot) {
+        return activate_slot(workers, slot);
+    }
+    return APR_EAGAIN;
+}
+
+static void wake_idle_worker(h2_workers *workers) 
+{
+    h2_slot *slot = pop_slot(&workers->idle);
+    if (slot) {
+        apr_thread_mutex_lock(slot->lock);
+        apr_thread_cond_signal(slot->not_idle);
+        apr_thread_mutex_unlock(slot->lock);
+    }
+    else if (workers->dynamic) {
+        add_worker(workers);
+    }
+}
+
+static void cleanup_zombies(h2_workers *workers)
+{
+    h2_slot *slot;
+    while ((slot = pop_slot(&workers->zombies))) {
+        if (slot->thread) {
+            apr_status_t status;
+            apr_thread_join(&status, slot->thread);
+            slot->thread = NULL;
+        }
+        apr_atomic_dec32(&workers->worker_count);
+        slot->next = NULL;
+        push_slot(&workers->free, slot);
+    }
+}
+
+static apr_status_t slot_pull_task(h2_slot *slot, h2_mplx *m)
+{
+    int has_more;
+    slot->task = h2_mplx_pop_task(m, &has_more);
+    if (slot->task) {
+        /* Ok, we got something to give back to the worker for execution. 
+         * If we still have idle workers, we let the worker be sticky, 
+         * e.g. making it poll the task's h2_mplx instance for more work 
+         * before asking back here. */
+        slot->sticks = slot->workers->max_workers;
+        return has_more? APR_EAGAIN : APR_SUCCESS;            
+    }
+    slot->sticks = 0;
+    return APR_EOF;
+}
+
+static h2_fifo_op_t mplx_peek(void *head, void *ctx)
+{
+    h2_mplx *m = head;
+    h2_slot *slot = ctx;
+    
+    if (slot_pull_task(slot, m) == APR_EAGAIN) {
+        wake_idle_worker(slot->workers);
+        return H2_FIFO_OP_REPUSH;
+    } 
+    return H2_FIFO_OP_PULL;
 }
 
 /**
  * Get the next task for the given worker. Will block until a task arrives
  * or the max_wait timer expires and more than min workers exist.
  */
-static apr_status_t get_mplx_next(h2_worker *worker, void *ctx, 
-                                  h2_task **ptask, int *psticky)
+static apr_status_t get_next(h2_slot *slot)
 {
+    h2_workers *workers = slot->workers;
     apr_status_t status;
-    apr_time_t wait_until = 0, now;
-    h2_workers *workers = ctx;
-    h2_task *task = NULL;
-    
-    *ptask = NULL;
-    *psticky = 0;
     
-    status = apr_thread_mutex_lock(workers->lock);
-    if (status == APR_SUCCESS) {
-        ++workers->idle_workers;
-        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
-                     "h2_worker(%d): looking for work", worker->id);
-        
-        while (!h2_worker_is_aborted(worker) && !workers->aborted
-               && !(task = next_task(workers))) {
-        
-            /* Need to wait for a new tasks to arrive. If we are above
-             * minimum workers, we do a timed wait. When timeout occurs
-             * and we have still more workers, we shut down one after
-             * the other. */
-            cleanup_zombies(workers, 0);
-            if (workers->worker_count > workers->min_workers) {
-                now = apr_time_now();
-                if (now >= wait_until) {
-                    wait_until = now + apr_time_from_sec(workers->max_idle_secs);
-                }
-                
-                ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
-                             "h2_worker(%d): waiting signal, "
-                             "workers=%d, idle=%d", worker->id, 
-                             (int)workers->worker_count, 
-                             workers->idle_workers);
-                status = apr_thread_cond_timedwait(workers->mplx_added,
-                                                   workers->lock, 
-                                                   wait_until - now);
-                if (status == APR_TIMEUP
-                    && workers->worker_count > workers->min_workers) {
-                    /* waited long enough without getting a task and
-                     * we are above min workers, abort this one. */
-                    ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, 
-                                 workers->s,
-                                 "h2_workers: aborting idle worker");
-                    h2_worker_abort(worker);
-                    break;
-                }
-            }
-            else {
-                ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
-                             "h2_worker(%d): waiting signal (eternal), "
-                             "worker_count=%d, idle=%d", worker->id, 
-                             (int)workers->worker_count,
-                             workers->idle_workers);
-                apr_thread_cond_wait(workers->mplx_added, workers->lock);
+    slot->task = NULL;
+    while (!slot->aborted) {
+        if (!slot->task) {
+            status = h2_fifo_try_peek(workers->mplxs, mplx_peek, slot);
+            if (status == APR_EOF) {
+                return status;
             }
         }
         
-        /* Here, we either have gotten task or decided to shut down
-         * the calling worker.
-         */
-        if (task) {
-            /* Ok, we got something to give back to the worker for execution. 
-             * If we have more idle workers than h2_mplx in our queue, then
-             * we let the worker be sticky, e.g. making it poll the task's
-             * h2_mplx instance for more work before asking back here.
-             * This avoids entering our global lock as long as enough idle
-             * workers remain. Stickiness of a worker ends when the connection
-             * has no new tasks to process, so the worker will get back here
-             * eventually.
-             */
-            *ptask = task;
-            *psticky = (workers->max_workers >= workers->mplx_count);
-            
-            if (workers->mplx_count && workers->idle_workers > 1) {
-                apr_thread_cond_signal(workers->mplx_added);
-            }
+        if (slot->task) {
+            return APR_SUCCESS;
         }
         
-        --workers->idle_workers;
-        apr_thread_mutex_unlock(workers->lock);
+        cleanup_zombies(workers);
+
+        apr_thread_mutex_lock(slot->lock);
+        push_slot(&workers->idle, slot);
+        apr_thread_cond_wait(slot->not_idle, slot->lock);
+        apr_thread_mutex_unlock(slot->lock);
     }
-    
-    return *ptask? APR_SUCCESS : APR_EOF;
+    return APR_EOF;
 }
 
-static void worker_done(h2_worker *worker, void *ctx)
+static void slot_done(h2_slot *slot)
 {
-    h2_workers *workers = ctx;
-    apr_status_t status = apr_thread_mutex_lock(workers->lock);
-    if (status == APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
-                     "h2_worker(%d): done", worker->id);
-        H2_WORKER_REMOVE(worker);
-        --workers->worker_count;
-        H2_WORKER_LIST_INSERT_TAIL(&workers->zombies, worker);
-        
-        apr_thread_mutex_unlock(workers->lock);
-    }
+    push_slot(&(slot->workers->zombies), slot);
 }
 
-static apr_status_t add_worker(h2_workers *workers)
+
+static void* APR_THREAD_FUNC slot_run(apr_thread_t *thread, void *wctx)
 {
-    h2_worker *w = h2_worker_create(workers->next_worker_id++,
-                                    workers->pool, workers->thread_attr,
-                                    get_mplx_next, worker_done, workers);
-    if (!w) {
-        return APR_ENOMEM;
+    h2_slot *slot = wctx;
+    
+    while (!slot->aborted) {
+
+        /* Get a h2_task from the mplxs queue. */
+        get_next(slot);
+        while (slot->task) {
+        
+            h2_task_do(slot->task, thread, slot->id);
+            
+            /* Report the task as done. If stickyness is left, offer the
+             * mplx the opportunity to give us back a new task right away.
+             */
+            if (!slot->aborted && (--slot->sticks > 0)) {
+                h2_mplx_task_done(slot->task->mplx, slot->task, &slot->task);
+            }
+            else {
+                h2_mplx_task_done(slot->task->mplx, slot->task, NULL);
+                slot->task = NULL;
+            }
+        }
     }
-    ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
-                 "h2_workers: adding worker(%d)", w->id);
-    ++workers->worker_count;
-    H2_WORKER_LIST_INSERT_TAIL(&workers->workers, w);
-    return APR_SUCCESS;
+
+    slot_done(slot);
+    return NULL;
 }
 
-static apr_status_t h2_workers_start(h2_workers *workers)
+static apr_status_t workers_pool_cleanup(void *data)
 {
-    apr_status_t status = apr_thread_mutex_lock(workers->lock);
-    if (status == APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
-                      "h2_workers: starting");
-
-        while (workers->worker_count < workers->min_workers
-               && status == APR_SUCCESS) {
-            status = add_worker(workers);
+    h2_workers *workers = data;
+    h2_slot *slot;
+    
+    if (!workers->aborted) {
+        workers->aborted = 1;
+        /* abort all idle slots */
+        for (;;) {
+            slot = pop_slot(&workers->idle);
+            if (slot) {
+                apr_thread_mutex_lock(slot->lock);
+                slot->aborted = 1;
+                apr_thread_cond_signal(slot->not_idle);
+                apr_thread_mutex_unlock(slot->lock);
+            }
+            else {
+                break;
+            }
         }
-        apr_thread_mutex_unlock(workers->lock);
+
+        h2_fifo_term(workers->mplxs);
+        h2_fifo_interrupt(workers->mplxs);
+
+        cleanup_zombies(workers);
     }
-    return status;
+    return APR_SUCCESS;
 }
 
 h2_workers *h2_workers_create(server_rec *s, apr_pool_t *server_pool,
                               int min_workers, int max_workers,
-                              apr_size_t max_tx_handles)
+                              int idle_secs)
 {
     apr_status_t status;
     h2_workers *workers;
     apr_pool_t *pool;
+    int i, n;
 
     ap_assert(s);
     ap_assert(server_pool);
 
     /* let's have our own pool that will be parent to all h2_worker
      * instances we create. This happens in various threads, but always
      * guarded by our lock. Without this pool, all subpool creations would
      * happen on the pool handed to us, which we do not guard.
      */
     apr_pool_create(&pool, server_pool);
     apr_pool_tag(pool, "h2_workers");
     workers = apr_pcalloc(pool, sizeof(h2_workers));
-    if (workers) {
-        workers->s = s;
-        workers->pool = pool;
-        workers->min_workers = min_workers;
-        workers->max_workers = max_workers;
-        workers->max_idle_secs = 10;
-        
-        workers->max_tx_handles = max_tx_handles;
-        workers->spare_tx_handles = workers->max_tx_handles;
-        
-        apr_threadattr_create(&workers->thread_attr, workers->pool);
-        if (ap_thread_stacksize != 0) {
-            apr_threadattr_stacksize_set(workers->thread_attr,
-                                         ap_thread_stacksize);
-            ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, s,
-                         "h2_workers: using stacksize=%ld", 
-                         (long)ap_thread_stacksize);
-        }
-        
-        APR_RING_INIT(&workers->workers, h2_worker, link);
-        APR_RING_INIT(&workers->zombies, h2_worker, link);
-        APR_RING_INIT(&workers->mplxs, h2_mplx, link);
-        
-        status = apr_thread_mutex_create(&workers->lock,
-                                         APR_THREAD_MUTEX_DEFAULT,
-                                         workers->pool);
-        if (status == APR_SUCCESS) {
-            status = apr_thread_cond_create(&workers->mplx_added, workers->pool);
-        }
-        
-        if (status == APR_SUCCESS) {
-            status = apr_thread_mutex_create(&workers->tx_lock,
-                                             APR_THREAD_MUTEX_DEFAULT,
-                                             workers->pool);
-        }
-        
-        if (status == APR_SUCCESS) {
-            status = h2_workers_start(workers);
-        }
-        
-        if (status != APR_SUCCESS) {
-            h2_workers_destroy(workers);
-            workers = NULL;
-        }
+    if (!workers) {
+        return NULL;
     }
-    return workers;
-}
-
-void h2_workers_destroy(h2_workers *workers)
-{
-    /* before we go, cleanup any zombie workers that may have accumulated */
-    cleanup_zombies(workers, 1);
     
-    if (workers->mplx_added) {
-        apr_thread_cond_destroy(workers->mplx_added);
-        workers->mplx_added = NULL;
-    }
-    if (workers->lock) {
-        apr_thread_mutex_destroy(workers->lock);
-        workers->lock = NULL;
-    }
-    while (!H2_MPLX_LIST_EMPTY(&workers->mplxs)) {
-        h2_mplx *m = H2_MPLX_LIST_FIRST(&workers->mplxs);
-        H2_MPLX_REMOVE(m);
+    workers->s = s;
+    workers->pool = pool;
+    workers->min_workers = min_workers;
+    workers->max_workers = max_workers;
+    workers->max_idle_secs = (idle_secs > 0)? idle_secs : 10;
+
+    status = h2_fifo_create(&workers->mplxs, pool, 2 * workers->max_workers);
+    if (status != APR_SUCCESS) {
+        return NULL;
     }
-    while (!H2_WORKER_LIST_EMPTY(&workers->workers)) {
-        h2_worker *w = H2_WORKER_LIST_FIRST(&workers->workers);
-        H2_WORKER_REMOVE(w);
+    
+    status = apr_threadattr_create(&workers->thread_attr, workers->pool);
+    if (status != APR_SUCCESS) {
+        return NULL;
     }
-    if (workers->pool) {
-        apr_pool_destroy(workers->pool);
-        /* workers is gone */
+    
+    if (ap_thread_stacksize != 0) {
+        apr_threadattr_stacksize_set(workers->thread_attr,
+                                     ap_thread_stacksize);
+        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, s,
+                     "h2_workers: using stacksize=%ld", 
+                     (long)ap_thread_stacksize);
     }
-}
-
-apr_status_t h2_workers_register(h2_workers *workers, struct h2_mplx *m)
-{
-    apr_status_t status = apr_thread_mutex_lock(workers->lock);
-    if (status == APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_TRACE3, status, workers->s,
-                     "h2_workers: register mplx(%ld), idle=%d", 
-                     m->id, workers->idle_workers);
-        if (in_list(workers, m)) {
-            status = APR_EAGAIN;
-        }
-        else {
-            H2_MPLX_LIST_INSERT_TAIL(&workers->mplxs, m);
-            ++workers->mplx_count;
-            status = APR_SUCCESS;
-        }
-        
-        if (workers->idle_workers > 0) { 
-            apr_thread_cond_signal(workers->mplx_added);
+    
+    status = apr_thread_mutex_create(&workers->lock,
+                                     APR_THREAD_MUTEX_DEFAULT,
+                                     workers->pool);
+    if (status == APR_SUCCESS) {        
+        n = workers->nslots = workers->max_workers;
+        workers->slots = apr_pcalloc(workers->pool, n * sizeof(h2_slot));
+        if (workers->slots == NULL) {
+            workers->nslots = 0;
+            status = APR_ENOMEM;
         }
-        else if (status == APR_SUCCESS 
-                 && workers->worker_count < workers->max_workers) {
-            ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
-                         "h2_workers: got %d worker, adding 1", 
-                         workers->worker_count);
-            add_worker(workers);
+        for (i = 0; i < n; ++i) {
+            workers->slots[i].id = i;
         }
-        apr_thread_mutex_unlock(workers->lock);
     }
-    return status;
-}
-
-apr_status_t h2_workers_unregister(h2_workers *workers, struct h2_mplx *m)
-{
-    apr_status_t status = apr_thread_mutex_lock(workers->lock);
     if (status == APR_SUCCESS) {
-        status = APR_EAGAIN;
-        if (in_list(workers, m)) {
-            H2_MPLX_REMOVE(m);
-            status = APR_SUCCESS;
+        /* we activate all for now, TODO: support min_workers again.
+         * do this in reverse for vanity reasons so slot 0 will most
+         * likely be at head of idle queue. */
+        n = workers->max_workers;
+        for (i = n-1; i >= 0; --i) {
+            status = activate_slot(workers, &workers->slots[i]);
+        }
+        /* the rest of the slots go on the free list */
+        for(i = n; i < workers->nslots; ++i) {
+            push_slot(&workers->free, &workers->slots[i]);
         }
-        apr_thread_mutex_unlock(workers->lock);
+        workers->dynamic = (workers->worker_count < workers->max_workers);
     }
-    return status;
-}
-
-void h2_workers_set_max_idle_secs(h2_workers *workers, int idle_secs)
-{
-    if (idle_secs <= 0) {
-        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, workers->s,
-                     APLOGNO(02962) "h2_workers: max_worker_idle_sec value of %d"
-                     " is not valid, ignored.", idle_secs);
-        return;
+    if (status == APR_SUCCESS) {
+        apr_pool_pre_cleanup_register(pool, workers, workers_pool_cleanup);    
+        return workers;
     }
-    workers->max_idle_secs = idle_secs;
+    return NULL;
 }
 
-apr_size_t h2_workers_tx_reserve(h2_workers *workers, apr_size_t count)
+apr_status_t h2_workers_register(h2_workers *workers, struct h2_mplx *m)
 {
-    apr_status_t status = apr_thread_mutex_lock(workers->tx_lock);
-    if (status == APR_SUCCESS) {
-        count = H2MIN(workers->spare_tx_handles, count);
-        workers->spare_tx_handles -= count;
-        ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, workers->s,
-                     "h2_workers: reserved %d tx handles, %d/%d left", 
-                     (int)count, (int)workers->spare_tx_handles,
-                     (int)workers->max_tx_handles);
-        apr_thread_mutex_unlock(workers->tx_lock);
-        return count;
-    }
-    return 0;
+    apr_status_t status = h2_fifo_push(workers->mplxs, m);
+    wake_idle_worker(workers);
+    return status;
 }
 
-void h2_workers_tx_free(h2_workers *workers, apr_size_t count)
+apr_status_t h2_workers_unregister(h2_workers *workers, struct h2_mplx *m)
 {
-    apr_status_t status = apr_thread_mutex_lock(workers->tx_lock);
-    if (status == APR_SUCCESS) {
-        workers->spare_tx_handles += count;
-        ap_log_error(APLOG_MARK, APLOG_TRACE2, 0, workers->s,
-                     "h2_workers: freed %d tx handles, %d/%d left", 
-                     (int)count, (int)workers->spare_tx_handles,
-                     (int)workers->max_tx_handles);
-        apr_thread_mutex_unlock(workers->tx_lock);
-    }
+    return h2_fifo_remove(workers->mplxs, m);
 }
-
