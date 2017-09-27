     parms.override = (RSRC_CONF | OR_ALL) & ~(OR_AUTHCFG | OR_LIMIT);
     parms.override_opts = OPT_ALL | OPT_SYM_OWNER | OPT_MULTI;
     parms.limited = -1;
 
     errmsg = ap_walk_config(conftree, &parms, s->lookup_defaults);
     if (errmsg) {
-        ap_log_perror(APLOG_MARK, APLOG_STARTUP, 0, p,
-                     "Syntax error on line %d of %s:",
-                     parms.err_directive->line_num,
-                     parms.err_directive->filename);
-        ap_log_perror(APLOG_MARK, APLOG_STARTUP, 0, p,
-                     "%s", errmsg);
+        if (parms.err_directive)
+            ap_log_perror(APLOG_MARK, APLOG_STARTUP, 0, p, APLOGNO(00526)
+                          "Syntax error on line %d of %s:",
+                          parms.err_directive->line_num,
+                          parms.err_directive->filename);
+        ap_log_perror(APLOG_MARK, APLOG_STARTUP, 0, p, "%s", errmsg);
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
     return OK;
 }
 
 AP_CORE_DECLARE(int) ap_parse_htaccess(ap_conf_vector_t **result,
                                        request_rec *r, int override,
-                                       int override_opts,
+                                       int override_opts, apr_table_t *override_list,
                                        const char *d, const char *access_name)
 {
     ap_configfile_t *f = NULL;
     cmd_parms parms;
     char *filename = NULL;
     const struct htaccess_result *cache;
