 
     if (!apr_is_empty_array(balancer->errstatuses)) {
         int i;
         for (i = 0; i < balancer->errstatuses->nelts; i++) {
             int val = ((int *)balancer->errstatuses->elts)[i];
             if (r->status == val) {
-                ap_log_error(APLOG_MARK, APLOG_NOTICE, rv, r->server,
-                    "Detected ErrorOnState (%d) for member (%s). Forcing worker into error state.", val, worker->name);
+                ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
+                             "proxy: BALANCER: (%s).  Forcing recovery for worker (%s), failonstatus %d",
+                             balancer->name, worker->name, val);
                 worker->s->status |= PROXY_WORKER_IN_ERROR;
                 worker->s->error_time = apr_time_now();
                 break;
             }
         }
     }
