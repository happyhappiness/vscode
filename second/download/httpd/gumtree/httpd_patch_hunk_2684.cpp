     f->ctx = fctx;
     return OK;
 }
 static int filter_lookup(ap_filter_t *f, ap_filter_rec_t *filter)
 {
     ap_filter_provider_t *provider;
-    int match;
-    int err = 0;
-    unsigned int proto_flags;
+    int match = 0;
+    const char *err = NULL;
     request_rec *r = f->r;
     harness_ctx *ctx = f->ctx;
     provider_ctx *pctx;
 #ifndef NO_PROTOCOL
+    unsigned int proto_flags;
     mod_filter_ctx *rctx = ap_get_module_config(r->request_config,
                                                 &filter_module);
 #endif
 
     /* Check registered providers in order */
     for (provider = filter->providers; provider; provider = provider->next) {
-        match = ap_expr_eval(r, provider->expr, &err, NULL, ap_expr_string, NULL);
-        if (err) {
-            /* log error but accept match value ? */
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                          "Error evaluating filter dispatch condition");
+        if (provider->expr) {
+            match = ap_expr_exec(r, provider->expr, &err);
+            if (err) {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(01379)
+                              "Error evaluating filter dispatch condition: %s",
+                              err);
+                match = 0;
+            }
+            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
+                          "Expression condition for '%s' %s",
+                          provider->frec->name,
+                          match ? "matched" : "did not match");
+        }
+        else if (r->content_type) {
+            const char **type = provider->types;
+            size_t len = strcspn(r->content_type, "; \t");
+            AP_DEBUG_ASSERT(type != NULL);
+            while (*type) {
+                /* Handle 'content-type;charset=...' correctly */
+                if (strncmp(*type, r->content_type, len) == 0
+                    && (*type)[len] == '\0') {
+                    match = 1;
+                    break;
+                }
+                type++;
+            }
+            ap_log_rerror(APLOG_MARK, APLOG_TRACE2, 0, r,
+                          "Content-Type condition for '%s' %s",
+                          provider->frec->name,
+                          match ? "matched" : "did not match");
         }
 
         if (match) {
             /* condition matches this provider */
 #ifndef NO_PROTOCOL
             /* check protocol
