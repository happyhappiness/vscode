                                  r->proxyreq);
         search = r->args;
     }
     if (path == NULL)
         return HTTP_BAD_REQUEST;
 
-    r->filename = apr_pstrcat(r->pool, "proxy:balancer://", host,
+    r->filename = apr_pstrcat(r->pool, "proxy:", BALANCER_PREFIX, host,
             "/", path, (search) ? "?" : "", (search) ? search : "", NULL);
 
     r->path_info = apr_pstrcat(r->pool, "/", path, NULL);
 
     return OK;
 }
 
-static int init_balancer_members(proxy_server_conf *conf, server_rec *s,
+static void init_balancer_members(apr_pool_t *p, server_rec *s,
                                  proxy_balancer *balancer)
 {
     int i;
     proxy_worker **workers;
 
     workers = (proxy_worker **)balancer->workers->elts;
 
     for (i = 0; i < balancer->workers->nelts; i++) {
         int worker_is_initialized;
-        worker_is_initialized = PROXY_WORKER_IS_INITIALIZED(*workers);
-        if (!worker_is_initialized) {
-            proxy_worker_stat *slot;
-            /*
-             * If the worker is not initialized check whether its scoreboard
-             * slot is already initialized.
-             */
-            slot = (proxy_worker_stat *) ap_get_scoreboard_lb((*workers)->id);
-            if (slot) {
-                worker_is_initialized = slot->status & PROXY_WORKER_INITIALIZED;
-            }
-            else {
-                worker_is_initialized = 0;
-            }
-        }
-        ap_proxy_initialize_worker_share(conf, *workers, s);
-        ap_proxy_initialize_worker(*workers, s, conf->pool);
+        proxy_worker *worker = *workers;
+        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01158)
+                     "Looking at %s -> %s initialized?", balancer->s->name, worker->s->name);
+        worker_is_initialized = PROXY_WORKER_IS_INITIALIZED(worker);
         if (!worker_is_initialized) {
-            /* Set to the original configuration */
-            (*workers)->s->lbstatus = (*workers)->s->lbfactor =
-            ((*workers)->lbfactor ? (*workers)->lbfactor : 1);
-            (*workers)->s->lbset = (*workers)->lbset;
+            ap_proxy_initialize_worker(worker, s, p);
         }
         ++workers;
     }
 
     /* Set default number of attempts to the number of
      * workers.
      */
-    if (!balancer->max_attempts_set && balancer->workers->nelts > 1) {
-        balancer->max_attempts = balancer->workers->nelts - 1;
-        balancer->max_attempts_set = 1;
+    if (!balancer->s->max_attempts_set && balancer->workers->nelts > 1) {
+        balancer->s->max_attempts = balancer->workers->nelts - 1;
+        balancer->s->max_attempts_set = 1;
     }
-    return 0;
 }
 
 /* Retrieve the parameter with the given name
  * Something like 'JSESSIONID=12345...N'
  */
 static char *get_path_param(apr_pool_t *pool, char *url,
