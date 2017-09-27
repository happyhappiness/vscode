     b->length = (apr_size_t)(-1);
     b->start = -1;
 
     /* Create the pollset */
     rv = apr_pollset_create(&data->pollset, 2, r->pool, 0);
     if (rv != APR_SUCCESS) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                     "cgi: apr_pollset_create(); check system or user limits");
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01217)
+                     "apr_pollset_create(); check system or user limits");
         return NULL;
     }
 
     fd.desc_type = APR_POLL_FILE;
     fd.reqevents = APR_POLLIN;
     fd.p = r->pool;
     fd.desc.f = out; /* script's stdout */
     fd.client_data = (void *)1;
     rv = apr_pollset_add(data->pollset, &fd);
     if (rv != APR_SUCCESS) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                     "cgi: apr_pollset_add(); check system or user limits");
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01218)
+                     "apr_pollset_add(); check system or user limits");
         return NULL;
     }
 
     fd.desc.f = err; /* script's stderr */
     fd.client_data = (void *)2;
     rv = apr_pollset_add(data->pollset, &fd);
     if (rv != APR_SUCCESS) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                     "cgi: apr_pollset_add(); check system or user limits");
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01219)
+                     "apr_pollset_add(); check system or user limits");
         return NULL;
     }
 
     data->r = r;
     b->data = data;
     return b;
