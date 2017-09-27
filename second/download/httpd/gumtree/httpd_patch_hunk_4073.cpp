             return 1;
         }
     }
     return 0;
 }
 
-static void cleanup_zombies(h2_workers *workers, int lock) {
+static void cleanup_zombies(h2_workers *workers, int lock)
+{
     if (lock) {
         apr_thread_mutex_lock(workers->lock);
     }
     while (!H2_WORKER_LIST_EMPTY(&workers->zombies)) {
         h2_worker *zombie = H2_WORKER_LIST_FIRST(&workers->zombies);
         H2_WORKER_REMOVE(zombie);
-        ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, workers->s,
+        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
                       "h2_workers: cleanup zombie %d", zombie->id);
         h2_worker_destroy(zombie);
     }
     if (lock) {
         apr_thread_mutex_unlock(workers->lock);
     }
 }
 
+static h2_task *next_task(h2_workers *workers)
+{
+    h2_task *task = NULL;
+    h2_mplx *last = NULL;
+    int has_more;
+    
+    /* Get the next h2_mplx to process that has a task to hand out.
+     * If it does, place it at the end of the queu and return the
+     * task to the worker.
+     * If it (currently) has no tasks, remove it so that it needs
+     * to register again for scheduling.
+     * If we run out of h2_mplx in the queue, we need to wait for
+     * new mplx to arrive. Depending on how many workers do exist,
+     * we do a timed wait or block indefinitely.
+     */
+    while (!task && !H2_MPLX_LIST_EMPTY(&workers->mplxs)) {
+        h2_mplx *m = H2_MPLX_LIST_FIRST(&workers->mplxs);
+        
+        if (last == m) {
+            break;
+        }
+        H2_MPLX_REMOVE(m);
+        --workers->mplx_count;
+        
+        task = h2_mplx_pop_task(m, &has_more);
+        if (has_more) {
+            H2_MPLX_LIST_INSERT_TAIL(&workers->mplxs, m);
+            ++workers->mplx_count;
+            if (!last) {
+                last = m;
+            }
+        }
+    }
+    return task;
+}
 
 /**
  * Get the next task for the given worker. Will block until a task arrives
  * or the max_wait timer expires and more than min workers exist.
- * The previous h2_mplx instance might be passed in and will be served
- * with preference, since we can ask it for the next task without aquiring
- * the h2_workers lock.
  */
-static apr_status_t get_mplx_next(h2_worker *worker, h2_mplx **pm, 
-                                  h2_task **ptask, void *ctx)
+static apr_status_t get_mplx_next(h2_worker *worker, void *ctx, 
+                                  h2_task **ptask, int *psticky)
 {
     apr_status_t status;
-    h2_mplx *m = NULL;
+    apr_time_t wait_until = 0, now;
+    h2_workers *workers = ctx;
     h2_task *task = NULL;
-    apr_time_t max_wait, start_wait;
-    int has_more = 0;
-    h2_workers *workers = (h2_workers *)ctx;
-    
-    if (*pm && ptask != NULL) {
-        /* We have a h2_mplx instance and the worker wants the next task. 
-         * Try to get one from the given mplx. */
-        *ptask = h2_mplx_pop_task(*pm, worker, &has_more);
-        if (*ptask) {
-            return APR_SUCCESS;
-        }
-    }
-    
-    if (*pm) {
-        /* Got a mplx handed in, but did not get or want a task from it. 
-         * Release it, as the workers reference will be wiped.
-         */
-        h2_mplx_release(*pm);
-        *pm = NULL;
-    }
     
-    if (!ptask) {
-        /* the worker does not want a next task, we're done.
-         */
-        return APR_SUCCESS;
-    }
-    
-    max_wait = apr_time_from_sec(apr_atomic_read32(&workers->max_idle_secs));
-    start_wait = apr_time_now();
+    *ptask = NULL;
+    *psticky = 0;
     
     status = apr_thread_mutex_lock(workers->lock);
     if (status == APR_SUCCESS) {
-        ++workers->idle_worker_count;
-        ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, workers->s,
+        ++workers->idle_workers;
+        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
                      "h2_worker(%d): looking for work", h2_worker_get_id(worker));
         
-        while (!task && !h2_worker_is_aborted(worker) && !workers->aborted) {
-            
-            /* Get the next h2_mplx to process that has a task to hand out.
-             * If it does, place it at the end of the queu and return the
-             * task to the worker.
-             * If it (currently) has no tasks, remove it so that it needs
-             * to register again for scheduling.
-             * If we run out of h2_mplx in the queue, we need to wait for
-             * new mplx to arrive. Depending on how many workers do exist,
-             * we do a timed wait or block indefinitely.
-             */
-            m = NULL;
-            while (!task && !H2_MPLX_LIST_EMPTY(&workers->mplxs)) {
-                m = H2_MPLX_LIST_FIRST(&workers->mplxs);
-                H2_MPLX_REMOVE(m);
+        while (!h2_worker_is_aborted(worker) && !workers->aborted
+               && !(task = next_task(workers))) {
+        
+            /* Need to wait for a new tasks to arrive. If we are above
+             * minimum workers, we do a timed wait. When timeout occurs
+             * and we have still more workers, we shut down one after
+             * the other. */
+            cleanup_zombies(workers, 0);
+            if (workers->worker_count > workers->min_workers) {
+                now = apr_time_now();
+                if (now >= wait_until) {
+                    wait_until = now + apr_time_from_sec(workers->max_idle_secs);
+                }
                 
-                task = h2_mplx_pop_task(m, worker, &has_more);
-                if (task) {
-                    if (has_more) {
-                        H2_MPLX_LIST_INSERT_TAIL(&workers->mplxs, m);
-                    }
-                    else {
-                        has_more = !H2_MPLX_LIST_EMPTY(&workers->mplxs);
-                    }
+                ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
+                             "h2_worker(%d): waiting signal, "
+                             "workers=%d, idle=%d", worker->id, 
+                             (int)workers->worker_count, 
+                             workers->idle_workers);
+                status = apr_thread_cond_timedwait(workers->mplx_added,
+                                                   workers->lock, 
+                                                   wait_until - now);
+                if (status == APR_TIMEUP
+                    && workers->worker_count > workers->min_workers) {
+                    /* waited long enough without getting a task and
+                     * we are above min workers, abort this one. */
+                    ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, 
+                                 workers->s,
+                                 "h2_workers: aborting idle worker");
+                    h2_worker_abort(worker);
                     break;
                 }
             }
-            
-            if (!task) {
-                /* Need to wait for either a new mplx to arrive.
-                 */
-                cleanup_zombies(workers, 0);
-                
-                if (workers->worker_count > workers->min_size) {
-                    apr_time_t now = apr_time_now();
-                    if (now >= (start_wait + max_wait)) {
-                        /* waited long enough without getting a task. */
-                        if (workers->worker_count > workers->min_size) {
-                            ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, 
-                                         workers->s,
-                                         "h2_workers: aborting idle worker");
-                            h2_worker_abort(worker);
-                            break;
-                        }
-                    }
-                    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, workers->s,
-                                 "h2_worker(%d): waiting signal, "
-                                 "worker_count=%d", worker->id, 
-                                 (int)workers->worker_count);
-                    apr_thread_cond_timedwait(workers->mplx_added,
-                                              workers->lock, max_wait);
-                }
-                else {
-                    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, workers->s,
-                                 "h2_worker(%d): waiting signal (eternal), "
-                                 "worker_count=%d", worker->id, 
-                                 (int)workers->worker_count);
-                    apr_thread_cond_wait(workers->mplx_added, workers->lock);
-                }
+            else {
+                ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
+                             "h2_worker(%d): waiting signal (eternal), "
+                             "worker_count=%d, idle=%d", worker->id, 
+                             (int)workers->worker_count,
+                             workers->idle_workers);
+                apr_thread_cond_wait(workers->mplx_added, workers->lock);
             }
         }
         
-        /* Here, we either have gotten task and mplx for the worker or
-         * needed to give up with more than enough workers.
+        /* Here, we either have gotten task or decided to shut down
+         * the calling worker.
          */
         if (task) {
-            ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, workers->s,
-                         "h2_worker(%d): start task(%s)",
-                         h2_worker_get_id(worker), task->id);
-            /* Since we hand out a reference to the worker, we increase
-             * its ref count.
+            /* Ok, we got something to give back to the worker for execution. 
+             * If we have more idle workers than h2_mplx in our queue, then
+             * we let the worker be sticky, e.g. making it poll the task's
+             * h2_mplx instance for more work before asking back here.
+             * This avoids entering our global lock as long as enough idle
+             * workers remain. Stickiness of a worker ends when the connection
+             * has no new tasks to process, so the worker will get back here
+             * eventually.
              */
-            h2_mplx_reference(m);
-            *pm = m;
             *ptask = task;
+            *psticky = (workers->max_workers >= workers->mplx_count);
             
-            if (has_more && workers->idle_worker_count > 1) {
+            if (workers->mplx_count && workers->idle_workers > 1) {
                 apr_thread_cond_signal(workers->mplx_added);
             }
-            status = APR_SUCCESS;
-        }
-        else {
-            status = APR_EOF;
         }
         
-        --workers->idle_worker_count;
+        --workers->idle_workers;
         apr_thread_mutex_unlock(workers->lock);
     }
     
-    return status;
+    return *ptask? APR_SUCCESS : APR_EOF;
 }
 
 static void worker_done(h2_worker *worker, void *ctx)
 {
-    h2_workers *workers = (h2_workers *)ctx;
+    h2_workers *workers = ctx;
     apr_status_t status = apr_thread_mutex_lock(workers->lock);
     if (status == APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, workers->s,
+        ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
                      "h2_worker(%d): done", h2_worker_get_id(worker));
         H2_WORKER_REMOVE(worker);
         --workers->worker_count;
         H2_WORKER_LIST_INSERT_TAIL(&workers->zombies, worker);
         
         apr_thread_mutex_unlock(workers->lock);
