         ap_log_error(APLOG_MARK, APLOG_CRIT, rc, s,
                      "mod_rewrite: Parent could not create RewriteLock "
                      "file %s", lockname);
         return rc;
     }
 
-#if APR_USE_SYSVSEM_SERIALIZE
+#ifdef MOD_REWRITE_SET_MUTEX_PERMS
     rc = unixd_set_global_mutex_perms(rewrite_mapr_lock_acquire);
     if (rc != APR_SUCCESS) {
         ap_log_error(APLOG_MARK, APLOG_CRIT, rc, s,
                      "mod_rewrite: Parent could not set permissions "
                      "on RewriteLock; check User and Group directives");
         return rc;
