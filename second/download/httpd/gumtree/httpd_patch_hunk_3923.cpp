             ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, workers->s,
                          "h2_workers: got %d worker, adding 1", 
                          workers->worker_count);
             add_worker(workers);
         }
         
+        /* cleanup any zombie workers that may have accumulated */
+        cleanup_zombies(workers, 0);
+        
         apr_thread_mutex_unlock(workers->lock);
     }
     return status;
 }
 
 apr_status_t h2_workers_unregister(h2_workers *workers, struct h2_mplx *m)
