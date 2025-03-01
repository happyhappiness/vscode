 
 static const char *set_override(cmd_parms *cmd, void *d_, const char *l)
 {
     core_dir_config *d = d_;
     char *w;
     char *k, *v;
+    const char *err;
 
     /* Throw a warning if we're in <Location> or <Files> */
     if (ap_check_cmd_context(cmd, NOT_IN_LOCATION | NOT_IN_FILES)) {
-        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server, APLOGNO(00114)
                      "Useless use of AllowOverride in line %d of %s.",
                      cmd->directive->line_num, cmd->directive->filename);
     }
+    if ((err = ap_check_cmd_context(cmd, NOT_IN_HTACCESS)) != NULL)
+        return err;
 
     d->override = OR_NONE;
     while (l[0]) {
-        w = ap_getword_conf(cmd->pool, &l);
+        w = ap_getword_conf(cmd->temp_pool, &l);
 
         k = w;
         v = strchr(k, '=');
         if (v) {
                 *v++ = '\0';
         }
