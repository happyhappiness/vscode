 
             len = strlen(*identifier);
             /*
              * Check that we have a parameter separator in the last segment
              * of the path and that the parameter matches our identifier
              */
-            if ((param = ap_strrchr_c(path, ';'))
+            if ((param = ap_strrchr_c(kpath, ';'))
                     && !strncmp(param + 1, *identifier, len)
                     && (*(param + len + 1) == '=')
                     && !ap_strchr_c(param + len + 2, '/')) {
-                path = apr_pstrmemdup(p, path, param - path);
+                kpath = apr_pstrmemdup(p, kpath, param - kpath);
                 continue;
             }
             /*
-             * Check if the identifier is in the querystring and cut it out.
+             * Check if the identifier is in the query string and cut it out.
              */
-            if (querystring && *querystring) {
+            if (kquery && *kquery) {
                 /*
                  * First check if the identifier is at the beginning of the
-                 * querystring and followed by a '='
+                 * query string and followed by a '='
                  */
-                if (!strncmp(querystring, *identifier, len)
-                        && (*(querystring + len) == '=')) {
-                    param = querystring;
+                if (!strncmp(kquery, *identifier, len) && kquery[len] == '=') {
+                    param = kquery;
                 }
                 else {
                     char *complete;
 
                     /*
                      * In order to avoid subkey matching (PR 48401) prepend
                      * identifier with a '&' and append a '='
                      */
                     complete = apr_pstrcat(p, "&", *identifier, "=", NULL);
-                    param = ap_strstr_c(querystring, complete);
+                    param = ap_strstr_c(kquery, complete);
                     /* If we found something we are sitting on the '&' */
                     if (param) {
                         param++;
                     }
                 }
                 if (param) {
                     const char *amp;
+                    char *dup = NULL;
 
-                    if (querystring != param) {
-                        querystring = apr_pstrndup(p, querystring,
-                                param - querystring);
+                    if (kquery != param) {
+                        dup = apr_pstrmemdup(p, kquery, param - kquery);
+                        kquery = dup;
                     }
                     else {
-                        querystring = "";
+                        kquery = "";
                     }
 
                     if ((amp = ap_strchr_c(param + len + 1, '&'))) {
-                        querystring = apr_pstrcat(p, querystring, amp + 1,
-                                NULL);
+                        kquery = apr_pstrcat(p, kquery, amp + 1, NULL);
                     }
                     else {
                         /*
-                         * If querystring is not "", then we have the case
+                         * If query string is not "", then we have the case
                          * that the identifier parameter we removed was the
-                         * last one in the original querystring. Hence we have
+                         * last one in the original query string. Hence we have
                          * a trailing '&' which needs to be removed.
                          */
-                        if (*querystring) {
-                            querystring[strlen(querystring) - 1] = '\0';
+                        if (dup) {
+                            dup[strlen(dup) - 1] = '\0';
                         }
                     }
                 }
             }
         }
     }
 
-    /* Key format is a URI, optionally without the query-string */
-    if (conf->ignorequerystring) {
-        *key = apr_pstrcat(p, scheme, "://", hostname, port_str, path, "?",
-                NULL);
-    }
-    else {
-        *key = apr_pstrcat(p, scheme, "://", hostname, port_str, path, "?",
-                querystring, NULL);
-    }
+    /* Key format is a URI, optionally without the query-string (NULL
+     * per above if conf->ignorequerystring)
+     */
+    *key = apr_pstrcat(p, scheme, "://", hostname, port_str,
+                       kpath, "?", kquery, NULL);
 
     /*
      * Store the key in the request_config for the cache as r->parsed_uri
      * might have changed in the time from our first visit here triggered by the
      * quick handler and our possible second visit triggered by the CACHE_SAVE
      * filter (e.g. r->parsed_uri got unescaped). In this case we would save the
      * resource in the cache under a key where it is never found by the quick
      * handler during following requests.
      */
-    ap_log_rerror(
-            APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00698) "cache: Key for entity %s?%s is %s", uri, parsed_uri->query, *key);
+    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, APR_SUCCESS, r, APLOGNO(00698)
+                  "cache: Key for entity %s?%s is %s", path, query, *key);
 
     return APR_SUCCESS;
 }
 
 apr_status_t cache_generate_key_default(request_rec *r, apr_pool_t* p,
-        const char **key)
+                                        const char **key)
 {
-    /* We want the actual query-string, which may differ from
-     * r->parsed_uri.query (immutable), so use "" (not NULL).
+    /* In early processing (quick-handler, forward proxy), we want the initial
+     * query-string from r->parsed_uri, since any change before CACHE_SAVE
+     * shouldn't modify the key. Otherwise we want the actual query-string.
      */
-    const char *args = r->args ? r->args : "";
-    return cache_canonicalise_key(r, p, r->uri, args, &r->parsed_uri, key);
+    const char *path = r->uri;
+    const char *query = r->args;
+    if (cache_use_early_url(r)) {
+        path = r->parsed_uri.path;
+        query = r->parsed_uri.query;
+    }
+    return cache_canonicalise_key(r, p, path, query, &r->parsed_uri, key);
 }
 
 /*
  * Invalidate a specific URL entity in all caches
  *
  * All cached entities for this URL are removed, usually in
