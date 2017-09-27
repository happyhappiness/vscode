         *plimit = NULL;
         ap_log_error(APLOG_MARK, APLOG_ERR, errno, cmd->server, APLOGNO(02172)
                      "%s: getrlimit failed", cmd->cmd->name);
         return;
     }
 
-    if (*(str = ap_getword_conf(cmd->pool, &arg)) != '\0') {
+    if (*(str = ap_getword_conf(cmd->temp_pool, &arg)) != '\0') {
         if (!strcasecmp(str, "max")) {
             cur = limit->rlim_max;
         }
         else {
             cur = atol(str);
         }
