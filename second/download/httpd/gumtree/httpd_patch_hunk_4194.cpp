         s = (r? r->server : c->base_server);
     }
     conf = ap_get_core_module_config(s->module_config);
     
     if (APLOGcdebug(c)) {
         const char *p = apr_array_pstrcat(pool, conf->protocols, ',');
-        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, 
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, APLOGNO(03155) 
                       "select protocol from %s, choices=%s for server %s", 
                       p, apr_array_pstrcat(pool, choices, ','),
                       s->server_hostname);
     }
 
     if (conf->protocols->nelts <= 0) {
