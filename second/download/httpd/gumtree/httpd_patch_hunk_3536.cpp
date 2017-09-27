 
 
 AP_DECLARE_NONSTD(const char *)ap_set_name_virtual_host(cmd_parms *cmd,
                                                         void *dummy,
                                                         const char *arg)
 {
-    /* use whatever port the main server has at this point */
-    return get_addresses(cmd->pool, arg, &name_vhost_list_tail,
-                         cmd->server->port);
+    static int warnonce = 0;
+    if (++warnonce == 1) {
+        ap_log_error(APLOG_MARK, APLOG_NOTICE|APLOG_STARTUP, APR_SUCCESS, NULL, APLOGNO(00548)
+                     "NameVirtualHost has no effect and will be removed in the "
+                     "next release %s:%d",
+                     cmd->directive->filename,
+                     cmd->directive->line_num);
+    }
+
+    return NULL;
 }
 
 
 /* hash table statistics, keep this in here for the beta period so
  * we can find out if the hash function is ok
  */
