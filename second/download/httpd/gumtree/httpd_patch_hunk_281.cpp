 }
 
 static int util_ldap_post_config(apr_pool_t *p, apr_pool_t *plog, 
                                  apr_pool_t *ptemp, server_rec *s)
 {
     int rc = LDAP_SUCCESS;
+    apr_status_t result;
+    char buf[MAX_STRING_LEN];
 
-    util_ldap_state_t *st = (util_ldap_state_t *)ap_get_module_config(
-                                                s->module_config, 
-                                                &ldap_module);
+    util_ldap_state_t *st =
+        (util_ldap_state_t *)ap_get_module_config(s->module_config, &ldap_module);
 
-        /* log the LDAP SDK used 
-        */
+#if APR_HAS_SHARED_MEMORY
+    server_rec *s_vhost;
+    util_ldap_state_t *st_vhost;
+    
+    /* initializing cache if file is here and we already don't have shm addr*/
+    if (st->cache_file && !st->cache_shm) {
+#endif
+        result = util_ldap_cache_init(p, st);
+        apr_strerror(result, buf, sizeof(buf));
+        ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, result, s,
+                     "LDAP cache init: %s", buf);
+
+#if APR_HAS_SHARED_MEMORY
+        /* merge config in all vhost */
+        s_vhost = s->next;
+        while (s_vhost) {
+            ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, result, s, 
+                         "LDAP merging Shared Cache conf: shm=0x%x rmm=0x%x for VHOST: %s",
+                         st->cache_shm, st->cache_rmm, s_vhost->server_hostname);
+
+            st_vhost = (util_ldap_state_t *)ap_get_module_config(s_vhost->module_config, &ldap_module);
+            st_vhost->cache_shm = st->cache_shm;
+            st_vhost->cache_rmm = st->cache_rmm;
+            st_vhost->cache_file = st->cache_file;
+            s_vhost = s_vhost->next;
+        }
+    }
+    else {
+        ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, 0 , s, "LDAP cache: Unable to init Shared Cache: no file");
+    }
+#endif
+    
+    /* log the LDAP SDK used 
+     */
     #if APR_HAS_NETSCAPE_LDAPSDK 
     
         ap_log_error(APLOG_MARK, APLOG_NOTICE, 0, s, 
              "LDAP: Built with Netscape LDAP SDK" );
 
     #elif APR_HAS_NOVELL_LDAPSDK
