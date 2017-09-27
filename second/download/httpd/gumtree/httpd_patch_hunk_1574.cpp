     if ((*route) && (**route)) {
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                                   "proxy: BALANCER: Found route %s", *route);
         /* We have a route in path or in cookie
          * Find the worker that has this route defined.
          */
-        worker = find_route_worker(balancer, *route);
-        if (worker && !PROXY_WORKER_IS_USABLE(worker)) {
-            /* We have a worker that is unusable.
-             * It can be in error or disabled, but in case
-             * it has a redirection set use that redirection worker.
-             * This enables to safely remove the member from the
-             * balancer. Of course you will need a some kind of
-             * session replication between those two remote.
+        worker = find_route_worker(balancer, *route, r);
+        if (worker && strcmp(*route, worker->s->route)) {
+            /*
+             * Notice that the route of the worker chosen is different from
+             * the route supplied by the client.
              */
-            if (*worker->s->redirect)
-                worker = find_route_worker(balancer, worker->s->redirect);
-            /* Check if the redirect worker is usable */
-            if (worker && !PROXY_WORKER_IS_USABLE(worker))
-                worker = NULL;
+            apr_table_setn(r->subprocess_env, "BALANCER_ROUTE_CHANGED", "1");
+            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+                         "proxy: BALANCER: Route changed from %s to %s",
+                         *route, worker->s->route);
         }
         return worker;
     }
     else
         return NULL;
 }
 
 static proxy_worker *find_best_worker(proxy_balancer *balancer,
                                       request_rec *r)
 {
     proxy_worker *candidate = NULL;
+    apr_status_t rv;
 
-    if (PROXY_THREAD_LOCK(balancer) != APR_SUCCESS)
+    if ((rv = PROXY_THREAD_LOCK(balancer)) != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
+        "proxy: BALANCER: (%s). Lock failed for find_best_worker()", balancer->name);
         return NULL;
+    }
 
     candidate = (*balancer->lbmethod->finder)(balancer, r);
 
+    if (candidate)
+        candidate->s->elected++;
+
 /*
         PROXY_THREAD_UNLOCK(balancer);
         return NULL;
 */
 
-    PROXY_THREAD_UNLOCK(balancer);
+    if ((rv = PROXY_THREAD_UNLOCK(balancer)) != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
+        "proxy: BALANCER: (%s). Unlock failed for find_best_worker()", balancer->name);
+    }
 
     if (candidate == NULL) {
         /* All the workers are in error state or disabled.
          * If the balancer has a timeout sleep for a while
          * and try again to find the worker. The chances are
          * that some other thread will release a connection.
