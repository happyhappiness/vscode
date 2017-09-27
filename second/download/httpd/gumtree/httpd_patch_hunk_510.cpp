     }
 
     if (!sec->have_ldap_url) {
         return DECLINED;
     }
 
+    /*
+     * It is possible that we've skipped mod_auth_ldap's
+     * check_user_id hook, but still get here. In that
+     * case, the req request_config struct hasn't been initialized
+     * causing problems when we try to use req->dn and/or req->name
+     * below. So we simply create one.
+     *
+     * Unlike 2.2, we don't try to search or populate it.
+     */
+    if (!req) {
+        ap_log_rerror(APLOG_MARK, APLOG_WARNING|APLOG_NOERRNO, 0, r, 
+                      "[%d] auth_ldap authorise: "
+                      "no req struct - skipped mod_auth_ldap_check_user_id?",
+                      getpid());
+
+        req = (mod_auth_ldap_request_t *)apr_pcalloc(r->pool,
+                                                     sizeof(mod_auth_ldap_request_t));
+        ap_set_module_config(r->request_config, &auth_ldap_module, req);
+    }
+
     if (sec->host) {
         ldc = util_ldap_connection_find(r, sec->host, sec->port,
                                        sec->binddn, sec->bindpw, sec->deref,
                                        sec->secure);
         apr_pool_cleanup_register(r->pool, ldc,
                                   mod_auth_ldap_cleanup_connection_close,
