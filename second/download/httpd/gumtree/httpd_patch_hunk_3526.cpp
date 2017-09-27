 
     return newcfg;
 }
 
 static void log_bad_create_options(server_rec *s, const char *type)
 {
-    ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s,
+    ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(00021)
                  "Invalid options were specified when creating the %s mutex",
                  type);
 }
 
 static void log_unknown_type(server_rec *s, const char *type)
 {
-    ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s,
+    ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(00022)
                  "Can't create mutex of unknown type %s", type);
 }
 
 static void log_create_failure(apr_status_t rv, server_rec *s, const char *type,
                                const char *fname)
 {
-    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s,
+    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(00023)
                  "Couldn't create the %s mutex %s%s%s", type,
                  fname ? "(file " : "",
                  fname ? fname : "",
                  fname ? ")" : "");
 }
 
+#ifdef AP_NEED_SET_MUTEX_PERMS
 static void log_perms_failure(apr_status_t rv, server_rec *s, const char *type)
 {
-    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s,
+    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(00024)
                  "Couldn't set permissions on the %s mutex; "
                  "check User and Group directives",
                  type);
 }
+#endif
 
 AP_DECLARE(apr_status_t) ap_global_mutex_create(apr_global_mutex_t **mutex,
                                                 const char **name,
                                                 const char *type,
                                                 const char *instance_id,
                                                 server_rec *s, apr_pool_t *p,
