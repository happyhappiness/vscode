         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                       "Error looking up %s in database", user);
         return AUTH_GENERAL_ERROR;
     }
 
     if (conf->user == NULL) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "No DBD Authn configured!");
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "No AuthDBDUserPWQuery has been specified.");
         return AUTH_GENERAL_ERROR;
     }
 
     statement = apr_hash_get(dbd->prepared, conf->user, APR_HASH_KEY_STRING);
     if (statement == NULL) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "No DBD Authn configured!");
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "A prepared statement could not be found for AuthDBDUserPWQuery, key '%s'.", conf->user);
         return AUTH_GENERAL_ERROR;
     }
     if (apr_dbd_pvselect(dbd->driver, r->pool, dbd->handle, &res, statement,
                               0, user, NULL) != 0) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                       "Error looking up %s in database", user);
