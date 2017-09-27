     if (r->uri[0] != '/' && r->uri[0] != '\0') {
         return DECLINED;
     }
 
     if ((ret = try_alias_list(r, serverconf->redirects, 1, &status)) != NULL) {
         if (ap_is_HTTP_REDIRECT(status)) {
-            /* include QUERY_STRING if any */
-            if (r->args) {
+            char *orig_target = ret;
+            if (ret[0] == '/') {
+
+                ret = ap_construct_url(r->pool, ret, r);
+                ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
+                              "incomplete redirection target of '%s' for "
+                              "URI '%s' modified to '%s'",
+                              orig_target, r->uri, ret);
+            }
+            if (!ap_is_url(ret)) {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                              "cannot redirect '%s' to '%s'; "
+                              "target is not a valid absoluteURI or abs_path",
+                              r->uri, ret);
+                /* restore the config value, so as not to get a
+                 * "regression" on existing "working" configs.
+                 */
+                ret = orig_target;
+            }
+            /* append requested query only, if the config didn't
+             * supply its own.
+             */
+            if (r->args && !ap_strchr(ret, '?')) {
                 ret = apr_pstrcat(r->pool, ret, "?", r->args, NULL);
             }
             apr_table_setn(r->headers_out, "Location", ret);
         }
         return status;
     }
