     else {
         proxy_worker *worker = ap_proxy_get_worker(cmd->temp_pool, conf, r);
         if (!worker) {
             const char *err = ap_proxy_add_worker(&worker, cmd->pool, conf, r);
             if (err)
                 return apr_pstrcat(cmd->temp_pool, "ProxyPass ", err, NULL);
+        } else {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
+                         "worker %s already used by another worker", worker->name);
         }
         PROXY_COPY_CONF_PARAMS(worker, conf);
 
         for (i = 0; i < arr->nelts; i++) {
             const char *err = set_worker_param(cmd->pool, worker, elts[i].key,
                                                elts[i].val);
