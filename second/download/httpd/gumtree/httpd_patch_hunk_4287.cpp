 static void worker_done(h2_worker *worker, void *ctx)
 {
     h2_workers *workers = ctx;
     apr_status_t status = apr_thread_mutex_lock(workers->lock);
     if (status == APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, workers->s,
-                     "h2_worker(%d): done", h2_worker_get_id(worker));
+                     "h2_worker(%d): done", worker->id);
         H2_WORKER_REMOVE(worker);
         --workers->worker_count;
         H2_WORKER_LIST_INSERT_TAIL(&workers->zombies, worker);
         
         apr_thread_mutex_unlock(workers->lock);
     }
