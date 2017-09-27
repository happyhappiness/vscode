     runtime = find_session_route(*balancer, r, &route, url);
     /* Lock the LoadBalancer
      * XXX: perhaps we need the process lock here
      */
     if ((rv = PROXY_THREAD_LOCK(*balancer)) != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
-                     "proxy: BALANCER: lock");
+                     "proxy: BALANCER: (%s). Lock failed for pre_request",
+                     (*balancer)->name);
         return DECLINED;
     }
     if (runtime) {
         int i, total_factor = 0;
         proxy_worker *workers;
         /* We have a sticky load balancer
