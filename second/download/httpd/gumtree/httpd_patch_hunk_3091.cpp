      * no further connections to the worker could be made
      */
     if (!connected && PROXY_WORKER_IS_USABLE(worker) &&
         !(worker->s->status & PROXY_WORKER_IGNORE_ERRORS)) {
         worker->s->error_time = apr_time_now();
         worker->s->status |= PROXY_WORKER_IN_ERROR;
-        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
-            "ap_proxy_connect_backend disabling worker for (%s)",
-            worker->hostname);
+        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00959)
+            "ap_proxy_connect_backend disabling worker for (%s) for %"
+            APR_TIME_T_FMT "s",
+            worker->s->hostname, apr_time_sec(worker->s->retry));
     }
     else {
         if (worker->s->retries) {
             /*
              * A worker came back. So here is where we need to
              * either reset all params to initial conditions or
