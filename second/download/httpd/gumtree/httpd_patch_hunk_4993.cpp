         s = s->next;
     }
 }
 
 /*
  * This routine is called before the server processes the configuration
- * files.  There is no return value.
+ * files.
  */
 static int proxy_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
                             apr_pool_t *ptemp)
 {
+    apr_status_t rv = ap_mutex_register(pconf, proxy_id, NULL,
+            APR_LOCK_DEFAULT, 0);
+    if (rv != APR_SUCCESS) {
+        ap_log_perror(APLOG_MARK, APLOG_CRIT, rv, plog, APLOGNO(02480)
+                "failed to register %s mutex", proxy_id);
+        return 500; /* An HTTP status would be a misnomer! */
+    }
+
     APR_OPTIONAL_HOOK(ap, status_hook, proxy_status_hook, NULL, NULL,
                       APR_HOOK_MIDDLE);
     /* Reset workers count on gracefull restart */
     proxy_lb_workers = 0;
     return OK;
 }
