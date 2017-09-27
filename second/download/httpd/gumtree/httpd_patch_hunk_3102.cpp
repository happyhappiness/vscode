     apr_int64_t expiry = (apr_int64_t) apr_time_now();
 
     session_dbd_dir_conf *conf = ap_get_module_config(r->per_dir_config,
                                                       &session_dbd_module);
 
     if (conf->selectlabel == NULL) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01853)
                       "no SessionDBDselectlabel has been specified");
         return APR_EGENERAL;
     }
 
     rv = dbd_init(r, conf->selectlabel, &dbd, &statement);
     if (rv) {
         return rv;
     }
     rv = apr_dbd_pvbselect(dbd->driver, r->pool, dbd->handle, &res, statement,
                           0, key, &expiry, NULL);
     if (rv) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, LOG_PREFIX
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01854)
                       "query execution error saving session '%s' "
                       "in database using query '%s': %s", key, conf->selectlabel,
                       apr_dbd_error(dbd->driver, dbd->handle, rv));
         return APR_EGENERAL;
     }
     for (rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1);
          rv != -1;
          rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1)) {
         if (rv != 0) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, LOG_PREFIX
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01855)
                           "error retrieving results while saving '%s' "
                           "in database using query '%s': %s", key, conf->selectlabel,
                            apr_dbd_error(dbd->driver, dbd->handle, rv));
             return APR_EGENERAL;
         }
         if (*val == NULL) {
