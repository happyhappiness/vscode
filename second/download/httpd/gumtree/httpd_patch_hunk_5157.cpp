     workers = (proxy_worker **)balancer->workers->elts;
 
     for (i = 0; i < balancer->workers->nelts; i++) {
         int worker_is_initialized;
         proxy_worker *worker = *workers;
         ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01158)
-                     "Looking at %s -> %s initialized?", balancer->s->name, worker->s->name);
+                     "Looking at %s -> %s initialized?", balancer->s->name,
+                     ap_proxy_worker_name(p, worker));
         worker_is_initialized = PROXY_WORKER_IS_INITIALIZED(worker);
         if (!worker_is_initialized) {
             ap_proxy_initialize_worker(worker, s, p);
         }
         ++workers;
     }
