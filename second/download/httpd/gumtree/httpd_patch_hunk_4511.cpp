     return NULL;
 }
 
 static const char *h2_conf_set_session_extra_files(cmd_parms *parms,
                                                    void *arg, const char *value)
 {
-    h2_config *cfg = (h2_config *)h2_config_sget(parms->server);
-    apr_int64_t max = (int)apr_atoi64(value);
-    if (max < 0) {
-        return "value must be a non-negative number";
-    }
-    cfg->session_extra_files = (int)max;
+    /* deprecated, ignore */
     (void)arg;
+    (void)value;
+    ap_log_perror(APLOG_MARK, APLOG_WARNING, 0, parms->pool, /* NO LOGNO */
+                  "H2SessionExtraFiles is obsolete and will be ignored");
     return NULL;
 }
 
 static const char *h2_conf_set_serialize_headers(cmd_parms *parms,
                                                  void *arg, const char *value)
 {
