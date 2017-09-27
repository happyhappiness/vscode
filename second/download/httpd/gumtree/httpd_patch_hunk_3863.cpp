     }
     ap_fputs(x.f, x.bb, CRLF_ASCII);
     ap_fflush(x.f, x.bb);
     apr_brigade_destroy(x.bb);
 }
 
+/*
+ * Compare two protocol identifier. Result is similar to strcmp():
+ * 0 gives same precedence, >0 means proto1 is preferred.
+ */
+static int protocol_cmp(const apr_array_header_t *preferences,
+                        const char *proto1,
+                        const char *proto2)
+{
+    if (preferences && preferences->nelts > 0) {
+        int index1 = ap_array_str_index(preferences, proto1, 0);
+        int index2 = ap_array_str_index(preferences, proto2, 0);
+        if (index2 > index1) {
+            return (index1 >= 0) ? 1 : -1;
+        }
+        else if (index1 > index2) {
+            return (index2 >= 0) ? -1 : 1;
+        }
+    }
+    /* both have the same index (mabye -1 or no pref configured) and we compare
+     * the names so that spdy3 gets precedence over spdy2. That makes
+     * the outcome at least deterministic. */
+    return strcmp(proto1, proto2);
+}
+
+AP_DECLARE(const char *) ap_get_protocol(conn_rec *c)
+{
+    const char *protocol = ap_run_protocol_get(c);
+    return protocol? protocol : AP_PROTOCOL_HTTP1;
+}
+
+AP_DECLARE(const char *) ap_select_protocol(conn_rec *c, request_rec *r, 
+                                            server_rec *s,
+                                            const apr_array_header_t *choices)
+{
+    apr_pool_t *pool = r? r->pool : c->pool;
+    core_server_config *conf = ap_get_core_module_config(s->module_config);
+    const char *protocol = NULL, *existing;
+    apr_array_header_t *proposals;
+
+    if (APLOGcdebug(c)) {
+        const char *p = apr_array_pstrcat(pool, conf->protocols, ',');
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, 
+                      "select protocol from %s, choices=%s for server %s", 
+                      p, apr_array_pstrcat(pool, choices, ','),
+                      s->server_hostname);
+    }
+
+    if (conf->protocols->nelts <= 0) {
+        /* nothing configured, by default, we only allow http/1.1 here.
+         * For now...
+         */
+        if (ap_array_str_contains(choices, AP_PROTOCOL_HTTP1)) {
+            return AP_PROTOCOL_HTTP1;
+        }
+        else {
+            return NULL;
+        }
+    }
+
+    proposals = apr_array_make(pool, choices->nelts + 1, sizeof(char *));
+    ap_run_protocol_propose(c, r, s, choices, proposals);
+
+    /* If the existing protocol has not been proposed, but is a choice,
+     * add it to the proposals implicitly.
+     */
+    existing = ap_get_protocol(c);
+    if (!ap_array_str_contains(proposals, existing)
+        && ap_array_str_contains(choices, existing)) {
+        APR_ARRAY_PUSH(proposals, const char*) = existing;
+    }
+
+    if (proposals->nelts > 0) {
+        int i;
+        const apr_array_header_t *prefs = NULL;
+
+        /* Default for protocols_honor_order is 'on' or != 0 */
+        if (conf->protocols_honor_order == 0 && choices->nelts > 0) {
+            prefs = choices;
+        }
+        else {
+            prefs = conf->protocols;
+        }
+
+        /* Select the most preferred protocol */
+        if (APLOGcdebug(c)) {
+            ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, 
+                          "select protocol, proposals=%s preferences=%s configured=%s", 
+                          apr_array_pstrcat(pool, proposals, ','),
+                          apr_array_pstrcat(pool, prefs, ','),
+                          apr_array_pstrcat(pool, conf->protocols, ','));
+        }
+        for (i = 0; i < proposals->nelts; ++i) {
+            const char *p = APR_ARRAY_IDX(proposals, i, const char *);
+            if (!ap_array_str_contains(conf->protocols, p)) {
+                /* not a configured protocol here */
+                continue;
+            }
+            else if (!protocol 
+                     || (protocol_cmp(prefs, protocol, p) < 0)) {
+                /* none selected yet or this one has preference */
+                protocol = p;
+            }
+        }
+    }
+    if (APLOGcdebug(c)) {
+        ap_log_cerror(APLOG_MARK, APLOG_DEBUG, 0, c, "selected protocol=%s", 
+                      protocol? protocol : "(none)");
+    }
+
+    return protocol;
+}
+
+AP_DECLARE(apr_status_t) ap_switch_protocol(conn_rec *c, request_rec *r, 
+                                            server_rec *s,
+                                            const char *protocol)
+{
+    const char *current = ap_get_protocol(c);
+    int rc;
+    
+    if (!strcmp(current, protocol)) {
+        ap_log_cerror(APLOG_MARK, APLOG_WARNING, 0, c, APLOGNO(02906)
+                      "already at it, protocol_switch to %s", 
+                      protocol);
+        return APR_SUCCESS;
+    }
+    
+    rc = ap_run_protocol_switch(c, r, s, protocol);
+    switch (rc) {
+        case DECLINED:
+            ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(02907)
+                          "no implementation for protocol_switch to %s", 
+                          protocol);
+            return APR_ENOTIMPL;
+        case OK:
+        case DONE:
+            return APR_SUCCESS;
+        default:
+            ap_log_cerror(APLOG_MARK, APLOG_ERR, 0, c, APLOGNO(02905)
+                          "unexpected return code %d from protocol_switch to %s"
+                          , rc, protocol);
+            return APR_EOF;
+    }    
+}
+
 
 AP_IMPLEMENT_HOOK_VOID(pre_read_request,
                        (request_rec *r, conn_rec *c),
                        (r, c))
 AP_IMPLEMENT_HOOK_RUN_ALL(int,post_read_request,
                           (request_rec *r), (r), OK, DECLINED)
