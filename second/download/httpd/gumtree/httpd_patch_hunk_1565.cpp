 static int filter_lookup(ap_filter_t *f, ap_filter_rec_t *filter)
 {
     ap_filter_provider_t *provider;
     const char *str = NULL;
     char *str1;
     int match;
+    int err = 0;
     unsigned int proto_flags;
     request_rec *r = f->r;
     harness_ctx *ctx = f->ctx;
     provider_ctx *pctx;
     mod_filter_ctx *rctx = ap_get_module_config(r->request_config,
                                                 &filter_module);
 
     /* Check registered providers in order */
     for (provider = filter->providers; provider; provider = provider->next) {
-        match = 1;
-        switch (provider->dispatch) {
-        case REQUEST_HEADERS:
-            str = apr_table_get(r->headers_in, provider->value);
-            break;
-        case RESPONSE_HEADERS:
-            /* Try r->headers_out first, fall back on err_headers_out. */
-            str = apr_table_get(r->headers_out, provider->value);
-            if (str) {
-                break;
-            }
-            str = apr_table_get(r->err_headers_out, provider->value);
-            break;
-        case SUBPROCESS_ENV:
-            str = apr_table_get(r->subprocess_env, provider->value);
-            break;
-        case CONTENT_TYPE:
-            str = r->content_type;
-            break;
-        case HANDLER:
-            str = r->handler;
-            break;
-        }
-
-        /* treat nulls so we don't have to check every strcmp individually
-         * Not sure if there's anything better to do with them
-         */
-        if (!str) {
-            match = 0;
-        }
-        /* we can't check for NULL in provider as that kills integer 0
-         * so we have to test each string/regexp case in the switch
-         */
-        else {
-            switch (provider->match_type) {
-            case STRING_MATCH:
-                if (strcasecmp(str, provider->match.string)) {
-                    match = 0;
-                }
-                break;
-            case STRING_CONTAINS:
-                str1 = apr_pstrdup(r->pool, str);
-                ap_str_tolower(str1);
-                if (!strstr(str1, provider->match.string)) {
-                    match = 0;
-                }
-                break;
-            case REGEX_MATCH:
-                if (ap_regexec(provider->match.regex, str, 0, NULL, 0)
-                    == AP_REG_NOMATCH) {
-                    match = 0;
-                }
-                break;
-            case INT_EQ:
-                if (atoi(str) != provider->match.number) {
-                    match = 0;
-                }
-                break;
-            /* Integer comparisons should be [var] OP [match]
-             * We need to set match = 0 if the condition fails
-             */
-            case INT_LT:
-                if (atoi(str) >= provider->match.number) {
-                    match = 0;
-                }
-                break;
-            case INT_LE:
-                if (atoi(str) > provider->match.number) {
-                    match = 0;
-                }
-                break;
-            case INT_GT:
-                if (atoi(str) <= provider->match.number) {
-                    match = 0;
-                }
-                break;
-            case INT_GE:
-                if (atoi(str) < provider->match.number) {
-                    match = 0;
-                }
-                break;
-            case DEFINED:        /* we already handled this:-) */
-                break;
-            }
+        match = ap_expr_eval(r, provider->expr, &err, NULL, ap_expr_string, NULL);
+        if (err) {
+            /* log error but accept match value ? */
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                          "Error evaluating filter dispatch condition");
         }
 
-        if (match != provider->not) {
+        if (match) {
             /* condition matches this provider */
 #ifndef NO_PROTOCOL
             /* check protocol
              *
              * FIXME:
              * This is a quick hack and almost certainly buggy.
