 
     authn_dbd_conf *conf = ap_get_module_config(r->per_dir_config,
                                                 &authn_dbd_module);
     ap_dbd_t *dbd = authn_dbd_acquire_fn(r);
     if (dbd == NULL) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                      "Error looking up %s in database", user);
+                      "Failed to acquire database connection to look up "
+                      "user '%s:%s'", user, realm);
         return AUTH_GENERAL_ERROR;
     }
     if (conf->realm == NULL) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "No AuthDBDUserRealmQuery has been specified.");
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                      "No AuthDBDUserRealmQuery has been specified");
         return AUTH_GENERAL_ERROR;
     }
     statement = apr_hash_get(dbd->prepared, conf->realm, APR_HASH_KEY_STRING);
     if (statement == NULL) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "A prepared statement could not be found for AuthDBDUserRealmQuery, key '%s'.", conf->realm);
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                      "A prepared statement could not be found for "
+                      "AuthDBDUserRealmQuery with the key '%s'", conf->realm);
         return AUTH_GENERAL_ERROR;
     }
     if (apr_dbd_pvselect(dbd->driver, r->pool, dbd->handle, &res, statement,
                               0, user, realm, NULL) != 0) {
         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                      "Error looking up %s:%s in database", user, realm);
+                      "Query execution error looking up '%s:%s' "
+                      "in database", user, realm);
         return AUTH_GENERAL_ERROR;
     }
     for (rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1);
          rv != -1;
          rv = apr_dbd_get_row(dbd->driver, r->pool, res, &row, -1)) {
         if (rv != 0) {
             ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                      "Error looking up %s in database", user);
+                          "Error retrieving results while looking up '%s:%s' "
+                          "in database", user, realm);
             return AUTH_GENERAL_ERROR;
         }
         if (dbd_hash == NULL) {
-            dbd_hash = apr_dbd_get_entry(dbd->driver, row, 0);
-
 #if APU_MAJOR_VERSION > 1 || (APU_MAJOR_VERSION == 1 && APU_MINOR_VERSION >= 3)
             /* add the rest of the columns to the environment */
             int i = 1;
             const char *name;
             for (name = apr_dbd_get_name(dbd->driver, res, i);
                  name != NULL;
