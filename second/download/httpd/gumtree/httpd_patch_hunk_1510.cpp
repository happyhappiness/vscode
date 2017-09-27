                                                        &authn_file_module);
     ap_configfile_t *f;
     char l[MAX_STRING_LEN];
     apr_status_t status;
     char *file_hash = NULL;
 
-    if (!conf->pwfile) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                      "AuthUserFile not specified in the configuration");
-        return AUTH_GENERAL_ERROR;
-    }
-
     status = ap_pcfg_openfile(&f, r->pool, conf->pwfile);
 
     if (status != APR_SUCCESS) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, status, r,
                       "Could not open password file: %s", conf->pwfile);
         return AUTH_GENERAL_ERROR;
