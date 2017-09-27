                 }
             }
             
             if (!task) {
                 /* Need to wait for either a new mplx to arrive.
                  */
+                cleanup_zombies(workers, 0);
+                
                 if (workers->worker_count > workers->min_size) {
                     apr_time_t now = apr_time_now();
                     if (now >= (start_wait + max_wait)) {
                         /* waited long enough without getting a task. */
-                        status = APR_TIMEUP;
-                    }
-                    else {
-                        ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, workers->s,
-                                     "h2_worker(%d): waiting signal, "
-                                     "worker_count=%d", worker->id, 
-                                     (int)workers->worker_count);
-                        status = apr_thread_cond_timedwait(workers->mplx_added,
-                                                           workers->lock, max_wait);
-                    }
-                    
-                    if (status == APR_TIMEUP) {
-                        /* waited long enough */
                         if (workers->worker_count > workers->min_size) {
                             ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, 
                                          workers->s,
                                          "h2_workers: aborting idle worker");
                             h2_worker_abort(worker);
                             break;
                         }
                     }
+                    ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, workers->s,
+                                 "h2_worker(%d): waiting signal, "
+                                 "worker_count=%d", worker->id, 
+                                 (int)workers->worker_count);
+                    apr_thread_cond_timedwait(workers->mplx_added,
+                                              workers->lock, max_wait);
                 }
                 else {
                     ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, workers->s,
                                  "h2_worker(%d): waiting signal (eternal), "
                                  "worker_count=%d", worker->id, 
                                  (int)workers->worker_count);
