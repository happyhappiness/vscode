                               path, NULL);
 
     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01060)
                   "set r->filename to %s", r->filename);
 
     rconf = ap_get_module_config(r->request_config, &proxy_fcgi_module);
-    if (rconf == NULL) { 
+    if (rconf == NULL) {
         rconf = apr_pcalloc(r->pool, sizeof(fcgi_req_config_t));
         ap_set_module_config(r->request_config, &proxy_fcgi_module, rconf);
     }
 
     if (NULL != (pathinfo_type = apr_table_get(r->subprocess_env, "proxy-fcgi-pathinfo"))) {
         /* It has to be on disk for this to work */
-        if (!strcasecmp(pathinfo_type, "full")) { 
+        if (!strcasecmp(pathinfo_type, "full")) {
             rconf->need_dirwalk = 1;
             ap_unescape_url_keep2f(path, 0);
         }
-        else if (!strcasecmp(pathinfo_type, "first-dot")) { 
+        else if (!strcasecmp(pathinfo_type, "first-dot")) {
             char *split = ap_strchr(path, '.');
-            if (split) { 
+            if (split) {
                 char *slash = ap_strchr(split, '/');
-                if (slash) { 
+                if (slash) {
                     r->path_info = apr_pstrdup(r->pool, slash);
                     ap_unescape_url_keep2f(r->path_info, 0);
                     *slash = '\0'; /* truncate path */
                 }
             }
         }
-        else if (!strcasecmp(pathinfo_type, "last-dot")) { 
+        else if (!strcasecmp(pathinfo_type, "last-dot")) {
             char *split = ap_strrchr(path, '.');
-            if (split) { 
+            if (split) {
                 char *slash = ap_strchr(split, '/');
-                if (slash) { 
+                if (slash) {
                     r->path_info = apr_pstrdup(r->pool, slash);
                     ap_unescape_url_keep2f(r->path_info, 0);
                     *slash = '\0'; /* truncate path */
                 }
             }
         }
-        else { 
+        else {
             /* before proxy-fcgi-pathinfo had multi-values. This requires the
              * the FCGI server to fixup PATH_INFO because it's the entire path
              */
             r->path_info = apr_pstrcat(r->pool, "/", path, NULL);
-            if (!strcasecmp(pathinfo_type, "unescape")) { 
+            if (!strcasecmp(pathinfo_type, "unescape")) {
                 ap_unescape_url_keep2f(r->path_info, 0);
             }
             ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01061)
                     "set r->path_info to %s", r->path_info);
         }
     }
 
     return OK;
 }
 
+
+/*
+  ProxyFCGISetEnvIf "reqenv('PATH_INFO') =~ m#/foo(\d+)\.php$#" COVENV1 "$1"
+  ProxyFCGISetEnvIf "reqenv('PATH_INFO') =~ m#/foo(\d+)\.php$#" PATH_INFO "/foo.php"
+  ProxyFCGISetEnvIf "reqenv('PATH_TRANSLATED') =~ m#(/.*foo)(\d+)(.*)#" PATH_TRANSLATED "$1$3"
+*/
+static void fix_cgivars(request_rec *r, fcgi_dirconf_t *dconf)
+{
+    sei_entry *entries;
+    const char *err, *src;
+    int i = 0, rc = 0;
+    ap_regmatch_t regm[AP_MAX_REG_MATCH];
+
+    entries = (sei_entry *) dconf->env_fixups->elts;
+    for (i = 0; i < dconf->env_fixups->nelts; i++) {
+        sei_entry *entry = &entries[i];
+
+        if (entry->envname[0] == '!') {
+            apr_table_unset(r->subprocess_env, entry->envname+1);
+        }
+        else if (0 < (rc = ap_expr_exec_re(r, entry->cond, AP_MAX_REG_MATCH, regm, &src, &err)))  {
+            const char *val = ap_expr_str_exec_re(r, entry->subst, AP_MAX_REG_MATCH, regm, &src, &err);
+            if (err) {
+                ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, r, APLOGNO(03514)
+                              "Error evaluating expression for replacement of %s: '%s'",
+                               entry->envname, err);
+                continue;
+            }
+            if (APLOGrtrace4(r)) {
+                const char *oldval = apr_table_get(r->subprocess_env, entry->envname);
+                ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
+                              "fix_cgivars: override %s from '%s' to '%s'",
+                              entry->envname, oldval, val);
+
+            }
+            apr_table_setn(r->subprocess_env, entry->envname, val);
+        }
+        else {
+            ap_log_rerror(APLOG_MARK, APLOG_TRACE8, 0, r, "fix_cgivars: Condition returned %d", rc);
+        }
+    }
+}
+
 /* Wrapper for apr_socket_sendv that handles updating the worker stats. */
 static apr_status_t send_data(proxy_conn_rec *conn,
                               struct iovec *vec,
                               int nvec,
                               apr_size_t *len)
 {
