         ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                     "internal error: bad expires code: %s", r->filename);
         return HTTP_INTERNAL_SERVER_ERROR;
     }
 
     expires = base + additional;
-    apr_table_mergen(r->headers_out, "Cache-Control",
-		    apr_psprintf(r->pool, "max-age=%" APR_TIME_T_FMT,
-                                 apr_time_sec(expires - r->request_time)));
+    apr_table_mergen(t, "Cache-Control",
+                     apr_psprintf(r->pool, "max-age=%" APR_TIME_T_FMT,
+                                  apr_time_sec(expires - r->request_time)));
     timestr = apr_palloc(r->pool, APR_RFC822_DATE_LEN);
     apr_rfc822_date(timestr, expires);
-    apr_table_setn(r->headers_out, "Expires", timestr);
+    apr_table_setn(t, "Expires", timestr);
     return OK;
 }
 
+/*
+ * Output filter to set the Expires response header field
+ * according to the content-type of the response -- if it hasn't
+ * already been set.
+ */
+static apr_status_t expires_filter(ap_filter_t *f,
+                                   apr_bucket_brigade *b)
+{
+    request_rec *r;
+    expires_dir_config *conf;
+    const char *expiry;
+    apr_table_t *t;
+
+    r = f->r;
+    conf = (expires_dir_config *) ap_get_module_config(r->per_dir_config,
+                                                       &expires_module);
+
+    /*
+     * Check to see which output header table we should use;
+     * mod_cgi loads script fields into r->err_headers_out,
+     * for instance.
+     */
+    expiry = apr_table_get(r->err_headers_out, "Expires");
+    if (expiry != NULL) {
+        t = r->err_headers_out;
+    }
+    else {
+        expiry = apr_table_get(r->headers_out, "Expires");
+        t = r->headers_out;
+    }
+    if (expiry == NULL) {
+        /*
+         * No expiration has been set, so we can apply any managed by
+         * this module.  First, check to see if there is an applicable
+         * ExpiresByType directive.
+         */
+        expiry = apr_table_get(conf->expiresbytype, 
+                               ap_field_noparam(r->pool, r->content_type));
+        if (expiry == NULL) {
+            /* Use the ExpiresDefault directive */
+            expiry = conf->expiresdefault;
+        }
+        if (expiry != NULL) {
+            set_expiration_fields(r, expiry, t);
+        }
+    }
+    ap_remove_output_filter(f);
+    return ap_pass_brigade(f->next, b);
+}
+
+static void expires_insert_filter(request_rec *r)
+{
+    expires_dir_config *conf;
+
+    /* Don't add Expires headers to errors */
+    if (ap_is_HTTP_ERROR(r->status)) {
+        return;
+    }
+    /* Say no to subrequests */
+    if (r->main != NULL) {
+        return;
+    }
+    conf = (expires_dir_config *) ap_get_module_config(r->per_dir_config,
+                                                       &expires_module);
+
+    /* Check to see if the filter is enabled and if there are any applicable 
+     * config directives for this directory scope
+     */
+    if (conf->active != ACTIVE_ON ||
+        (apr_is_empty_table(conf->expiresbytype) && !conf->expiresdefault)) {
+        return;
+    }
+    ap_add_output_filter("MOD_EXPIRES", NULL, r, r->connection);
+    return;
+}
 static void register_hooks(apr_pool_t *p)
 {
-    ap_hook_fixups(add_expires,NULL,NULL,APR_HOOK_MIDDLE);
+    ap_register_output_filter("MOD_EXPIRES", expires_filter, NULL,
+                              AP_FTYPE_CONTENT_SET);
+    ap_hook_insert_filter(expires_insert_filter, NULL, NULL, APR_HOOK_MIDDLE);
 }
 
 module AP_MODULE_DECLARE_DATA expires_module =
 {
     STANDARD20_MODULE_STUFF,
     create_dir_expires_config,  /* dir config creater */
