 */
 
     if (!sec->have_ldap_url) {
         return DECLINED;
     }
 
+    /* pre-scan for ldap-* requirements so we can get out of the way early */
+    for(x=0; x < reqs_arr->nelts; x++) {
+        if (! (reqs[x].method_mask & (AP_METHOD_BIT << m))) {
+            continue;
+        }
+
+        t = reqs[x].requirement;
+        w = ap_getword_white(r->pool, &t);
+
+        if (strncmp(w, "ldap-",5) == 0) {
+            required_ldap = 1;
+            break;
+        }
+    }
+
+    if (!required_ldap) {
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
+                      "[%" APR_PID_T_FMT "] auth_ldap authorise: declining to authorise (no ldap requirements)", getpid());
+        return DECLINED;
+    }
+
+
+
     if (sec->host) {
         ldc = util_ldap_connection_find(r, sec->host, sec->port,
                                        sec->binddn, sec->bindpw, sec->deref,
                                        sec->secure);
         apr_pool_cleanup_register(r->pool, ldc,
                                   authnz_ldap_cleanup_connection_close,
