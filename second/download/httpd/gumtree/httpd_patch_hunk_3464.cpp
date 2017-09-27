     }
 
     ap_pid_fname = arg;
     return NULL;
 }
 
-int ap_max_requests_per_child = 0;
+void ap_mpm_dump_pidfile(apr_pool_t *p, apr_file_t *out)
+{
+    apr_file_printf(out, "PidFile: \"%s\"\n",
+                    ap_server_root_relative(p, ap_pid_fname));
+}
 
 const char *ap_mpm_set_max_requests(cmd_parms *cmd, void *dummy,
                                     const char *arg)
 {
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
     if (err != NULL) {
         return err;
     }
 
+    if (!strcasecmp(cmd->cmd->name, "MaxRequestsPerChild")) {
+        ap_log_error(APLOG_MARK, APLOG_INFO, 0, NULL, APLOGNO(00545)
+                     "MaxRequestsPerChild is deprecated, use "
+                     "MaxConnectionsPerChild instead.");
+    }
+
     ap_max_requests_per_child = atoi(arg);
 
     return NULL;
 }
 
-char ap_coredump_dir[MAX_STRING_LEN];
-int ap_coredumpdir_configured;
-
 const char *ap_mpm_set_coredumpdir(cmd_parms *cmd, void *dummy,
                                    const char *arg)
 {
     apr_finfo_t finfo;
     const char *fname;
     const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
