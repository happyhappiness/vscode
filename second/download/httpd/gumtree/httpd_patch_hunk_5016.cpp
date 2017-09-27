         *cpp = SSL_X509_NAME_ENTRY_to_string(p, X509_NAME_get_entry(subj, i));
     }
 
     return apr_is_empty_array(*ids) ? FALSE : TRUE;
 }
 
+/* 
+ * Check if a certificate matches for a particular name, by iterating over its
+ * DNS-IDs and CN-IDs (RFC 6125), optionally with basic wildcard matching.
+ * If server_rec is non-NULL, some (debug/trace) logging is enabled.
+ */
+BOOL SSL_X509_match_name(apr_pool_t *p, X509 *x509, const char *name,
+                         BOOL allow_wildcard, server_rec *s)
+{
+    BOOL matched = FALSE;
+    apr_array_header_t *ids;
+
+    /*
+     * At some day in the future, this might be replaced with X509_check_host()
+     * (available in OpenSSL 1.0.2 and later), but two points should be noted:
+     * 1) wildcard matching in X509_check_host() might yield different
+     *    results (by default, it supports a broader set of patterns, e.g.
+     *    wildcards in non-initial positions);
+     * 2) we lose the option of logging each DNS- and CN-ID (until a match
+     *    is found).
+     */
+
+    if (SSL_X509_getIDs(p, x509, &ids)) {
+        const char *cp;
+        int i;
+        char **id = (char **)ids->elts;
+        BOOL is_wildcard;
+
+        for (i = 0; i < ids->nelts; i++) {
+            if (!id[i])
+                continue;
+
+            /*
+             * Determine if it is a wildcard ID - we're restrictive
+             * in the sense that we require the wildcard character to be
+             * THE left-most label (i.e., the ID must start with "*.")
+             */
+            is_wildcard = (*id[i] == '*' && *(id[i]+1) == '.') ? TRUE : FALSE;
+
+            /*
+             * If the ID includes a wildcard character (and the caller is
+             * allowing wildcards), check if it matches for the left-most
+             * DNS label - i.e., the wildcard character is not allowed
+             * to match a dot. Otherwise, try a simple string compare.
+             */
+            if ((allow_wildcard == TRUE && is_wildcard == TRUE &&
+                 (cp = ap_strchr_c(name, '.')) && !strcasecmp(id[i]+1, cp)) ||
+                !strcasecmp(id[i], name)) {
+                matched = TRUE;
+            }
+
+            if (s) {
+                ap_log_error(APLOG_MARK, APLOG_TRACE3, 0, s,
+                             "[%s] SSL_X509_match_name: expecting name '%s', "
+                             "%smatched by ID '%s'",
+                             (mySrvConfig(s))->vhost_id, name,
+                             matched == TRUE ? "" : "NOT ", id[i]);
+            }
+
+            if (matched == TRUE) {
+                break;
+            }
+        }
+
+    }
+
+    if (s) {
+        ssl_log_xerror(SSLLOG_MARK, APLOG_DEBUG, 0, p, s, x509,
+                       APLOGNO(02412) "[%s] Cert %s for name '%s'",
+                       (mySrvConfig(s))->vhost_id,
+                       matched == TRUE ? "matches" : "does not match",
+                       name);
+    }
+
+    return matched;
+}
+
 /*  _________________________________________________________________
 **
 **  Low-Level CA Certificate Loading
 **  _________________________________________________________________
 */
 
