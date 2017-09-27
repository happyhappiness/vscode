     p = db ? db->pool : p;
 
     /* There might not be a <db> if we had problems creating it. */
     if (db == NULL) {
         errcode = 1;
         errstr = "Could not open property database.";
-        if (APR_STATUS_IS_EDSOOPEN(status))
-            ap_log_error(APLOG_MARK, APLOG_CRIT, status, NULL,
-                         "The DBM driver could not be loaded");
     }
     else {
         (void) apr_dbm_geterror(db->file, &errcode, errbuf, sizeof(errbuf));
         errstr = apr_pstrdup(p, errbuf);
     }
 
-    err = dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, errcode, errstr);
-    err->save_errno = save_errno;
+    err = dav_new_error(p, HTTP_INTERNAL_SERVER_ERROR, errcode, status, errstr);
     return err;
 }
 
 /* ensure that our state subdirectory is present */
 /* ### does this belong here or in dav_fs_repos.c ?? */
 void dav_fs_ensure_state_dir(apr_pool_t * p, const char *dirname)
