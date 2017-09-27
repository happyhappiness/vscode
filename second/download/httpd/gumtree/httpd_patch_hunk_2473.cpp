 
     b = apr_bucket_flush_create(f->c->bucket_alloc);
     APR_BRIGADE_INSERT_TAIL(upgradebb, b);
 
     rv = ap_pass_brigade(f->next, upgradebb);
     if (rv) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(02132)
                       "could not send interim 101 Upgrade response");
         return AP_FILTER_ERROR;
     }
 
     key = get_port_key(r->connection);
 
