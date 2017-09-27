      * At any time, a request marked "no-cache" will force a refresh,
      * ignoring the lock, ensuring an extended lockout is impossible.
      *
      * A lock that exceeds a maximum age will be deleted, and another
      * request gets to make a new lock and try again.
      */
-    status = ap_cache_try_lock(conf, r, (char *)h->cache_obj->key);
+    status = cache_try_lock(conf, cache, r);
     if (APR_SUCCESS == status) {
         /* we obtained a lock, follow the stale path */
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                     "Cache lock obtained for stale cached URL, "
-                     "revalidating entry: %s",
-                     r->unparsed_uri);
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00782)
+                "Cache lock obtained for stale cached URL, "
+                "revalidating entry: %s",
+                r->unparsed_uri);
         return 0;
     }
     else if (APR_EEXIST == status) {
         /* lock already exists, return stale data anyway, with a warning */
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
-                     "Cache already locked for stale cached URL, "
-                     "pretend it is fresh: %s",
-                     r->unparsed_uri);
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00783)
+                "Cache already locked for stale cached URL, "
+                "pretend it is fresh: %s",
+                r->unparsed_uri);
 
         /* make sure we don't stomp on a previous warning */
         warn_head = apr_table_get(h->resp_hdrs, "Warning");
         if ((warn_head == NULL) ||
             ((warn_head != NULL) && (ap_strstr_c(warn_head, "110") == NULL))) {
-            apr_table_merge(h->resp_hdrs, "Warning",
-                        "110 Response is stale");
+            apr_table_mergen(h->resp_hdrs, "Warning",
+                             "110 Response is stale");
         }
 
         return 1;
     }
     else {
         /* some other error occurred, just treat the object as stale */
-        ap_log_error(APLOG_MARK, APLOG_DEBUG, status, r->server,
-                     "Attempt to obtain a cache lock for stale "
-                     "cached URL failed, revalidating entry anyway: %s",
-                     r->unparsed_uri);
+        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, status, r, APLOGNO(00784)
+                "Attempt to obtain a cache lock for stale "
+                "cached URL failed, revalidating entry anyway: %s",
+                r->unparsed_uri);
         return 0;
     }
 
 }
 
-/*
- * list is a comma-separated list of case-insensitive tokens, with
- * optional whitespace around the tokens.
- * The return returns 1 if the token val is found in the list, or 0
- * otherwise.
- */
-CACHE_DECLARE(int) ap_cache_liststr(apr_pool_t *p, const char *list,
-                                    const char *key, char **val)
-{
-    apr_size_t key_len;
-    const char *next;
-
-    if (!list) {
-        return 0;
-    }
-
-    key_len = strlen(key);
-    next = list;
-
-    for (;;) {
-
-        /* skip whitespace and commas to find the start of the next key */
-        while (*next && (apr_isspace(*next) || (*next == ','))) {
-            next++;
-        }
-
-        if (!*next) {
-            return 0;
-        }
-
-        if (!strncasecmp(next, key, key_len)) {
-            /* this field matches the key (though it might just be
-             * a prefix match, so make sure the match is followed
-             * by either a space or an equals sign)
-             */
-            next += key_len;
-            if (!*next || (*next == '=') || apr_isspace(*next) ||
-                (*next == ',')) {
-                /* valid match */
-                if (val) {
-                    while (*next && (*next != '=') && (*next != ',')) {
-                        next++;
-                    }
-                    if (*next == '=') {
-                        next++;
-                        while (*next && apr_isspace(*next )) {
-                            next++;
-                        }
-                        if (!*next) {
-                            *val = NULL;
-                        }
-                        else {
-                            const char *val_start = next;
-                            while (*next && !apr_isspace(*next) &&
-                                   (*next != ',')) {
-                                next++;
-                            }
-                            *val = apr_pstrmemdup(p, val_start,
-                                                  next - val_start);
-                        }
-                    }
-                    else {
-                        *val = NULL;
-                    }
-                }
-                return 1;
-            }
-        }
-
-        /* skip to the next field */
-        do {
-            next++;
-            if (!*next) {
-                return 0;
-            }
-        } while (*next != ',');
-    }
-}
-
 /* return each comma separated token, one at a time */
 CACHE_DECLARE(const char *)ap_cache_tokstr(apr_pool_t *p, const char *list,
                                            const char **str)
 {
     apr_size_t i;
     const char *s;
