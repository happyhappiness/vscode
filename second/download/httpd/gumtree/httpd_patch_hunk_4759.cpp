 
     if (!apr_is_empty_array(balancer->errstatuses)) {
         int i;
         for (i = 0; i < balancer->errstatuses->nelts; i++) {
             int val = ((int *)balancer->errstatuses->elts)[i];
             if (r->status == val) {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01174)
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01174)
                               "%s: Forcing worker (%s) into error state " 
                               "due to status code %d matching 'failonstatus' "
                               "balancer parameter",
                               balancer->s->name, worker->s->name, val);
                 worker->s->status |= PROXY_WORKER_IN_ERROR;
                 worker->s->error_time = apr_time_now();
