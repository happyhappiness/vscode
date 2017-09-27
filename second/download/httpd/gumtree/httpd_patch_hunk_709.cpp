         return proxy_ssl_disable(c);
     }
 
     return 0;
 }
 
+PROXY_DECLARE(int) ap_proxy_conn_is_https(conn_rec *c)
+{
+    if (proxy_is_https) {
+        return proxy_is_https(c);
+    }
+    else
+        return 0;
+}
+
+PROXY_DECLARE(const char *) ap_proxy_ssl_val(apr_pool_t *p, server_rec *s,
+                                             conn_rec *c, request_rec *r,
+                                             const char *var)
+{
+    if (proxy_ssl_val) {
+        /* XXX Perhaps the casting useless */
+        return (const char *)proxy_ssl_val(p, s, c, r, (char *)var);
+    }
+    else
+        return NULL;
+}
+
 static int proxy_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                              apr_pool_t *ptemp, server_rec *s)
 {
+
     proxy_ssl_enable = APR_RETRIEVE_OPTIONAL_FN(ssl_proxy_enable);
     proxy_ssl_disable = APR_RETRIEVE_OPTIONAL_FN(ssl_engine_disable);
+    proxy_is_https = APR_RETRIEVE_OPTIONAL_FN(ssl_is_https);
+    proxy_ssl_val = APR_RETRIEVE_OPTIONAL_FN(ssl_var_lookup);
 
     return OK;
 }
 
+/*
+ *  proxy Extension to mod_status
+ */
+static int proxy_status_hook(request_rec *r, int flags)
+{
+    int i, n;
+    void *sconf = r->server->module_config;
+    proxy_server_conf *conf = (proxy_server_conf *)
+        ap_get_module_config(sconf, &proxy_module);
+    proxy_balancer *balancer = NULL;
+    proxy_worker *worker = NULL;
+
+    if (flags & AP_STATUS_SHORT || conf->balancers->nelts == 0 ||
+        conf->proxy_status == status_off)
+        return OK;
+
+    balancer = (proxy_balancer *)conf->balancers->elts;
+    for (i = 0; i < conf->balancers->nelts; i++) {
+        ap_rputs("<hr />\n<h1>Proxy LoadBalancer Status for ", r);
+        ap_rvputs(r, balancer->name, "</h1>\n\n", NULL);
+        ap_rputs("\n\n<table border=\"0\"><tr>"
+                 "<th>SSes</th><th>Timeout</th><th>Method</th>"
+                 "</tr>\n<tr>", r);
+        ap_rvputs(r, "<td>", balancer->sticky, NULL);
+        ap_rprintf(r, "</td><td>%" APR_TIME_T_FMT "</td>",
+                   apr_time_sec(balancer->timeout));
+        ap_rprintf(r, "<td>%s</td>\n",
+                   balancer->lbmethod->name);
+        ap_rputs("</table>\n", r);
+        ap_rputs("\n\n<table border=\"0\"><tr>"
+                 "<th>Sch</th><th>Host</th><th>Stat</th>"
+                 "<th>Route</th><th>Redir</th>"
+                 "<th>F</th><th>Acc</th><th>Wr</th><th>Rd</th>"
+                 "</tr>\n", r);
+
+        worker = (proxy_worker *)balancer->workers->elts;
+        for (n = 0; n < balancer->workers->nelts; n++) {
+            char fbuf[50];
+            ap_rvputs(r, "<tr>\n<td>", worker->scheme, "</td>", NULL);
+            ap_rvputs(r, "<td>", worker->hostname, "</td><td>", NULL);
+            if (worker->s->status & PROXY_WORKER_DISABLED)
+                ap_rputs("Dis", r);
+            else if (worker->s->status & PROXY_WORKER_IN_ERROR)
+                ap_rputs("Err", r);
+            else if (worker->s->status & PROXY_WORKER_INITIALIZED)
+                ap_rputs("Ok", r);
+            else
+                ap_rputs("-", r);
+            ap_rvputs(r, "</td><td>", worker->s->route, NULL);
+            ap_rvputs(r, "</td><td>", worker->s->redirect, NULL);
+            ap_rprintf(r, "</td><td>%d</td>", worker->s->lbfactor);
+            ap_rprintf(r, "<td>%d</td><td>", (int)(worker->s->elected));
+            ap_rputs(apr_strfsize(worker->s->transferred, fbuf), r);
+            ap_rputs("</td><td>", r);
+            ap_rputs(apr_strfsize(worker->s->read, fbuf), r);
+            ap_rputs("</td>\n", r);
+
+            /* TODO: Add the rest of dynamic worker data */
+            ap_rputs("</tr>\n", r);
+
+            ++worker;
+        }
+        ap_rputs("</table>\n", r);
+        ++balancer;
+    }
+    ap_rputs("<hr /><table>\n"
+             "<tr><th>SSes</th><td>Sticky session name</td></tr>\n"
+             "<tr><th>Timeout</th><td>Balancer Timeout</td></tr>\n"
+             "<tr><th>Sch</th><td>Connection scheme</td></tr>\n"
+             "<tr><th>Host</th><td>Backend Hostname</td></tr>\n"
+             "<tr><th>Stat</th><td>Worker status</td></tr>\n"
+             "<tr><th>Route</th><td>Session Route</td></tr>\n"
+             "<tr><th>Redir</th><td>Session Route Redirection</td></tr>\n"
+             "<tr><th>F</th><td>Load Balancer Factor in %</td></tr>\n"
+             "<tr><th>Acc</th><td>Number of requests</td></tr>\n"
+             "<tr><th>Wr</th><td>Number of bytes transferred</td></tr>\n"
+             "<tr><th>Rd</th><td>Number of bytes read</td></tr>\n"
+             "</table>", r);
+
+    return OK;
+}
+
+static void child_init(apr_pool_t *p, server_rec *s)
+{
+    proxy_worker *reverse = NULL;
+
+    while (s) {
+        void *sconf = s->module_config;
+        proxy_server_conf *conf;
+        proxy_worker *worker;
+        int i;
+
+        conf = (proxy_server_conf *)ap_get_module_config(sconf, &proxy_module);
+        /* Initialize worker's shared scoreboard data */
+        worker = (proxy_worker *)conf->workers->elts;
+        for (i = 0; i < conf->workers->nelts; i++) {
+            ap_proxy_initialize_worker_share(conf, worker, s);
+            ap_proxy_initialize_worker(worker, s);
+            worker++;
+        }
+        /* Initialize forward worker if defined */
+        if (conf->forward) {
+            ap_proxy_initialize_worker_share(conf, conf->forward, s);
+            ap_proxy_initialize_worker(conf->forward, s);
+            /* Do not disable worker in case of errors */
+            conf->forward->s->status |= PROXY_WORKER_IGNORE_ERRORS;
+            /* Disable address cache for generic forward worker */
+            conf->forward->is_address_reusable = 0;
+        }
+        if (!reverse) {
+            reverse = ap_proxy_create_worker(p);
+            reverse->name     = "proxy:reverse";
+            reverse->hostname = "*";
+            reverse->scheme   = "*";
+            ap_proxy_initialize_worker_share(conf, reverse, s);
+            ap_proxy_initialize_worker(reverse, s);
+            /* Do not disable worker in case of errors */
+            reverse->s->status |= PROXY_WORKER_IGNORE_ERRORS;
+            /* Disable address cache for generic reverse worker */
+            reverse->is_address_reusable = 0;
+        }
+        conf->reverse = reverse;
+        s = s->next;
+    }
+}
+
+/*
+ * This routine is called before the server processes the configuration
+ * files.  There is no return value.
+ */
+static int proxy_pre_config(apr_pool_t *pconf, apr_pool_t *plog,
+                            apr_pool_t *ptemp)
+{
+    APR_OPTIONAL_HOOK(ap, status_hook, proxy_status_hook, NULL, NULL,
+                      APR_HOOK_MIDDLE);
+    /* Reset workers count on gracefull restart */
+    proxy_lb_workers = 0;
+    return OK;
+}
+
 static void register_hooks(apr_pool_t *p)
 {
     /* fixup before mod_rewrite, so that the proxied url will not
      * escaped accidentally by our fixup.
      */
     static const char * const aszSucc[]={ "mod_rewrite.c", NULL };
+    /* Only the mpm_winnt has child init hook handler.
+     * make sure that we are called after the mpm
+     * initializes.
+     */
+    static const char *const aszPred[] = { "mpm_winnt.c", NULL};
 
+    APR_REGISTER_OPTIONAL_FN(ap_proxy_lb_workers);
     /* handler */
     ap_hook_handler(proxy_handler, NULL, NULL, APR_HOOK_FIRST);
     /* filename-to-URI translation */
-    ap_hook_translate_name(proxy_trans, NULL, NULL, APR_HOOK_FIRST);
+    ap_hook_translate_name(proxy_trans, aszSucc, NULL, APR_HOOK_FIRST);
     /* walk <Proxy > entries and suppress default TRACE behavior */
     ap_hook_map_to_storage(proxy_map_location, NULL,NULL, APR_HOOK_FIRST);
     /* fixups */
     ap_hook_fixups(proxy_fixup, NULL, aszSucc, APR_HOOK_FIRST);
     /* post read_request handling */
     ap_hook_post_read_request(proxy_detect, NULL, NULL, APR_HOOK_FIRST);
+    /* pre config handling */
+    ap_hook_pre_config(proxy_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
     /* post config handling */
     ap_hook_post_config(proxy_post_config, NULL, NULL, APR_HOOK_MIDDLE);
+    /* child init handling */
+    ap_hook_child_init(child_init, aszPred, NULL, APR_HOOK_MIDDLE);
+
 }
 
 module AP_MODULE_DECLARE_DATA proxy_module =
 {
     STANDARD20_MODULE_STUFF,
     create_proxy_dir_config,    /* create per-directory config structure */
