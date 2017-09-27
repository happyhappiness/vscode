             return 1;
         }
     }
     return 0;
 }
 
+static void cleanup_zombies(h2_workers *workers, int lock) {
+    if (lock) {
+        apr_thread_mutex_lock(workers->lock);
+    }
+    while (!H2_WORKER_LIST_EMPTY(&workers->zombies)) {
+        h2_worker *zombie = H2_WORKER_LIST_FIRST(&workers->zombies);
+        H2_WORKER_REMOVE(zombie);
+        ap_log_error(APLOG_MARK, APLOG_TRACE1, 0, workers->s,
+                      "h2_workers: cleanup zombie %d", zombie->id);
+        h2_worker_destroy(zombie);
+    }
+    if (lock) {
+        apr_thread_mutex_unlock(workers->lock);
+    }
+}
+
 
 /**
  * Get the next task for the given worker. Will block until a task arrives
  * or the max_wait timer expires and more than min workers exist.
  * The previous h2_mplx instance might be passed in and will be served
  * with preference, since we can ask it for the next task without aquiring
