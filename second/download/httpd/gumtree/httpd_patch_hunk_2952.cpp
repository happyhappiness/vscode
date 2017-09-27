     proxy_worker **worker;
     proxy_worker *mycandidate = NULL;
     int cur_lbset = 0;
     int max_lbset = 0;
     int checking_standby;
     int checked_standby;
-    
-    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
+
+    if (!ap_proxy_retry_worker_fn) {
+        ap_proxy_retry_worker_fn =
+                APR_RETRIEVE_OPTIONAL_FN(ap_proxy_retry_worker);
+        if (!ap_proxy_retry_worker_fn) {
+            /* can only happen if mod_proxy isn't loaded */
+            return NULL;
+        }
+    }
+
+    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server, APLOGNO(01207)
                  "proxy: Entering byrequests for BALANCER (%s)",
-                 balancer->name);
+                 balancer->s->name);
 
     /* First try to see if we have available candidate */
     do {
         checking_standby = checked_standby = 0;
         while (!mycandidate && !checked_standby) {
             worker = (proxy_worker **)balancer->workers->elts;
             for (i = 0; i < balancer->workers->nelts; i++, worker++) {
                 if (!checking_standby) {    /* first time through */
                     if ((*worker)->s->lbset > max_lbset)
                         max_lbset = (*worker)->s->lbset;
                 }
-                if ((*worker)->s->lbset != cur_lbset)
-                    continue;
-                if ( (checking_standby ? !PROXY_WORKER_IS_STANDBY(*worker) : PROXY_WORKER_IS_STANDBY(*worker)) )
+                if (
+                    ((*worker)->s->lbset != cur_lbset) ||
+                    (checking_standby ? !PROXY_WORKER_IS_STANDBY(*worker) : PROXY_WORKER_IS_STANDBY(*worker)) ||
+                    (PROXY_WORKER_IS_DRAINING(*worker))
+                    ) {
                     continue;
+                }
+
                 /* If the worker is in error state run
                  * retry on that worker. It will be marked as
                  * operational if the retry timeout is elapsed.
                  * The worker might still be unusable, but we try
                  * anyway.
                  */
                 if (!PROXY_WORKER_IS_USABLE(*worker))
-                    ap_proxy_retry_worker("BALANCER", *worker, r->server);
+                    ap_proxy_retry_worker_fn("BALANCER", *worker, r->server);
                 /* Take into calculation only the workers that are
                  * not in error state or not disabled.
                  */
                 if (PROXY_WORKER_IS_USABLE(*worker)) {
                     (*worker)->s->lbstatus += (*worker)->s->lbfactor;
                     total_factor += (*worker)->s->lbfactor;
