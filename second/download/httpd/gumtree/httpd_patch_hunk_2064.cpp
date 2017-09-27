     if (!*balancer &&
         !(*balancer = ap_proxy_get_balancer(r->pool, conf, *url)))
         return DECLINED;
 
     /* Step 2: find the session route */
 
-    runtime = find_session_route(*balancer, r, &route, url);
+    runtime = find_session_route(*balancer, r, &route, &sticky, url);
     /* Lock the LoadBalancer
      * XXX: perhaps we need the process lock here
      */
     if ((rv = PROXY_THREAD_LOCK(*balancer)) != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
                      "proxy: BALANCER: (%s). Lock failed for pre_request",
