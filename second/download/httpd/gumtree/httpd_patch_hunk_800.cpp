 
     arr_param->curr_idx = arr_param->array->nelts;
 
     return 0;
 }
 
-static void process_command_config(server_rec *s, apr_array_header_t *arr,
-                                   ap_directive_t **conftree, apr_pool_t *p,
-                                   apr_pool_t *ptemp)
+static const char *process_command_config(server_rec *s,
+                                          apr_array_header_t *arr,
+                                          ap_directive_t **conftree,
+                                          apr_pool_t *p,
+                                          apr_pool_t *ptemp)
 {
     const char *errmsg;
     cmd_parms parms;
     arr_elts_param_t arr_parms;
 
     arr_parms.curr_idx = 0;
     arr_parms.array = arr;
 
+    if (ap_config_hash == NULL) {
+        rebuild_conf_hash(s->process->pconf, 1);
+    }
+
     parms = default_parms;
     parms.pool = p;
     parms.temp_pool = ptemp;
     parms.server = s;
     parms.override = (RSRC_CONF | OR_ALL) & ~(OR_AUTHCFG | OR_LIMIT);
+    parms.override_opts = OPT_ALL | OPT_INCNOEXEC | OPT_SYM_OWNER | OPT_MULTI;
 
     parms.config_file = ap_pcfg_open_custom(p, "-c/-C directives",
                                             &arr_parms, NULL,
                                             arr_elts_getstr, arr_elts_close);
 
     errmsg = ap_build_config(&parms, p, ptemp, conftree);
+    ap_cfg_closefile(parms.config_file);
+
     if (errmsg) {
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                     "Syntax error in -C/-c directive:");
-        ap_log_error(APLOG_MARK, APLOG_STARTUP, 0, NULL,
-                     "%s", errmsg);
-        exit(1);
+        return apr_pstrcat(p, "Syntax error in -C/-c directive: ", errmsg,
+                           NULL);
     }
 
-    ap_cfg_closefile(parms.config_file);
+    return NULL;
 }
 
 typedef struct {
     char *fname;
 } fnames;
 
