             ap_rputs("</table>\n", r);
             ++balancer;
         }
         ap_rputs("<hr />\n", r);
         if (wsel && bsel) {
             ap_rputs("<h3>Edit worker settings for ", r);
-            ap_rvputs(r, wsel->name, "</h3>\n", NULL);
-            ap_rvputs(r, "<form method=\"GET\" action=\"", NULL);
-            ap_rvputs(r, r->uri, "\">\n<dl>", NULL);
-            ap_rputs("<table><tr><td>Load factor:</td><td><input name=\"lf\" type=text ", r);
-            ap_rprintf(r, "value=\"%d\"></td></tr>\n", wsel->s->lbfactor);
-            ap_rputs("<tr><td>LB Set:</td><td><input name=\"ls\" type=text ", r);
-            ap_rprintf(r, "value=\"%d\"></td></tr>\n", wsel->s->lbset);
-            ap_rputs("<tr><td>Route:</td><td><input name=\"wr\" type=text ", r);
-            ap_rvputs(r, "value=\"", ap_escape_html(r->pool, wsel->s->route),
+            ap_rvputs(r, wsel->s->name, "</h3>\n", NULL);
+            ap_rputs("<form method='POST' enctype='application/x-www-form-urlencoded' action='", r);
+            ap_rvputs(r, action, "'>\n", NULL);
+            ap_rputs("<dl>\n<table><tr><td>Load factor:</td><td><input name='w_lf' id='w_lf' type=text ", r);
+            ap_rprintf(r, "value='%d'></td></tr>\n", wsel->s->lbfactor);
+            ap_rputs("<tr><td>LB Set:</td><td><input name='w_ls' id='w_ls' type=text ", r);
+            ap_rprintf(r, "value='%d'></td></tr>\n", wsel->s->lbset);
+            ap_rputs("<tr><td>Route:</td><td><input name='w_wr' id='w_wr' type=text ", r);
+            ap_rvputs(r, "value='", ap_escape_html(r->pool, wsel->s->route),
                       NULL);
-            ap_rputs("\"></td></tr>\n", r);
-            ap_rputs("<tr><td>Route Redirect:</td><td><input name=\"rr\" type=text ", r);
-            ap_rvputs(r, "value=\"", ap_escape_html(r->pool, wsel->s->redirect),
+            ap_rputs("'></td></tr>\n", r);
+            ap_rputs("<tr><td>Route Redirect:</td><td><input name='w_rr' id='w_rr' type=text ", r);
+            ap_rvputs(r, "value='", ap_escape_html(r->pool, wsel->s->redirect),
                       NULL);
-            ap_rputs("\"></td></tr>\n", r);
-            ap_rputs("<tr><td>Status:</td><td>Disabled: <input name=\"dw\" value=\"Disable\" type=radio", r);
-            if (wsel->s->status & PROXY_WORKER_DISABLED)
-                ap_rputs(" checked", r);
-            ap_rputs("> | Enabled: <input name=\"dw\" value=\"Enable\" type=radio", r);
-            if (!(wsel->s->status & PROXY_WORKER_DISABLED))
-                ap_rputs(" checked", r);
-            ap_rputs("></td></tr>\n", r);
-            ap_rputs("<tr><td colspan=2><input type=submit value=\"Submit\"></td></tr>\n", r);
-            ap_rvputs(r, "</table>\n<input type=hidden name=\"w\" ",  NULL);
-            ap_rvputs(r, "value=\"", ap_escape_uri(r->pool, wsel->name), "\">\n", NULL);
-            ap_rvputs(r, "<input type=hidden name=\"b\" ", NULL);
-            ap_rvputs(r, "value=\"", bsel->name + sizeof("balancer://") - 1,
-                      "\">\n", NULL);
-            ap_rvputs(r, "<input type=hidden name=\"nonce\" value=\"", 
-                      balancer_nonce, "\">\n", NULL);
+            ap_rputs("'></td></tr>\n", r);
+            ap_rputs("<tr><td>Status:</td>", r);
+            ap_rputs("<td><table><tr><th>Ign</th><th>Drn</th><th>Dis</th><th>Stby</th></tr>\n<tr>", r);
+            create_radio("w_status_I", (PROXY_WORKER_IGNORE_ERRORS & wsel->s->status), r);
+            create_radio("w_status_N", (PROXY_WORKER_DRAIN & wsel->s->status), r);
+            create_radio("w_status_D", (PROXY_WORKER_DISABLED & wsel->s->status), r);
+            create_radio("w_status_H", (PROXY_WORKER_HOT_STANDBY & wsel->s->status), r);
+            ap_rputs("</tr></table>\n", r);
+            ap_rputs("<tr><td colspan=2><input type=submit value='Submit'></td></tr>\n", r);
+            ap_rvputs(r, "</table>\n<input type=hidden name='w' id='w' ",  NULL);
+            ap_rvputs(r, "value='", ap_escape_uri(r->pool, wsel->s->name), "'>\n", NULL);
+            ap_rvputs(r, "<input type=hidden name='b' id='b' ", NULL);
+            ap_rvputs(r, "value='", bsel->s->name + sizeof(BALANCER_PREFIX) - 1,
+                      "'>\n", NULL);
+            ap_rvputs(r, "<input type=hidden name='nonce' id='nonce' value='",
+                      bsel->s->nonce, "'>\n", NULL);
+            ap_rvputs(r, "</form>\n", NULL);
+            ap_rputs("<hr />\n", r);
+        } else if (bsel) {
+            const apr_array_header_t *provs;
+            const ap_list_provider_names_t *pname;
+            int i;
+            ap_rputs("<h3>Edit balancer settings for ", r);
+            ap_rvputs(r, bsel->s->name, "</h3>\n", NULL);
+            ap_rputs("<form method='POST' enctype='application/x-www-form-urlencoded' action='", r);
+            ap_rvputs(r, action, "'>\n", NULL);
+            ap_rputs("<dl>\n<table>\n", r);
+            provs = ap_list_provider_names(r->pool, PROXY_LBMETHOD, "0");
+            if (provs) {
+                ap_rputs("<tr><td>LBmethod:</td>", r);
+                ap_rputs("<td>\n<select name='b_lbm' id='b_lbm'>", r);
+                pname = (ap_list_provider_names_t *)provs->elts;
+                for (i = 0; i < provs->nelts; i++, pname++) {
+                    ap_rvputs(r,"<option value='", pname->provider_name, "'", NULL);
+                    if (strcmp(pname->provider_name, bsel->s->lbpname) == 0)
+                        ap_rputs(" selected ", r);
+                    ap_rvputs(r, ">", pname->provider_name, "\n", NULL);
+                }
+                ap_rputs("</select>\n</td></tr>\n", r);
+            }
+            ap_rputs("<tr><td>Timeout:</td><td><input name='b_tmo' id='b_tmo' type=text ", r);
+            ap_rprintf(r, "value='%" APR_TIME_T_FMT "'></td></tr>\n", apr_time_sec(bsel->s->timeout));
+            ap_rputs("<tr><td>Failover Attempts:</td><td><input name='b_max' id='b_max' type=text ", r);
+            ap_rprintf(r, "value='%d'></td></tr>\n", bsel->s->max_attempts);
+            ap_rputs("<tr><td>Disable Failover:</td>", r);
+            create_radio("b_sforce", bsel->s->sticky_force, r);
+            ap_rputs("<tr><td>Sticky Session:</td><td><input name='b_ss' id='b_ss' size=64 type=text ", r);
+            if (strcmp(bsel->s->sticky, bsel->s->sticky_path)) {
+                ap_rvputs(r, "value ='", bsel->s->sticky, " | ",
+                          bsel->s->sticky_path, NULL);
+            }
+            else {
+                ap_rvputs(r, "value ='", bsel->s->sticky, NULL);
+            }
+            ap_rputs("'>&nbsp;&nbsp;&nbsp;&nbsp;(Use '-' to delete)</td></tr>\n", r);
+            if (storage->num_free_slots(bsel->wslot) != 0) {
+                ap_rputs("<tr><td>Add New Worker:</td><td><input name='b_nwrkr' id='b_nwrkr' size=32 type=text>"
+                         "&nbsp;&nbsp;&nbsp;&nbsp;Are you sure? <input name='b_wyes' id='b_wyes' type=checkbox value='1'>"
+                         "</td></tr>", r);
+            }
+            ap_rputs("<tr><td colspan=2><input type=submit value='Submit'></td></tr>\n", r);
+            ap_rvputs(r, "</table>\n<input type=hidden name='b' id='b' ", NULL);
+            ap_rvputs(r, "value='", bsel->s->name + sizeof(BALANCER_PREFIX) - 1,
+                      "'>\n", NULL);
+            ap_rvputs(r, "<input type=hidden name='nonce' id='nonce' value='",
+                      bsel->s->nonce, "'>\n", NULL);
             ap_rvputs(r, "</form>\n", NULL);
             ap_rputs("<hr />\n", r);
         }
         ap_rputs(ap_psignature("",r), r);
         ap_rputs("</body></html>\n", r);
+        ap_rflush(r);
     }
-    return OK;
+    return DONE;
 }
 
-static void child_init(apr_pool_t *p, server_rec *s)
+static void balancer_child_init(apr_pool_t *p, server_rec *s)
 {
     while (s) {
-        void *sconf = s->module_config;
-        proxy_server_conf *conf;
         proxy_balancer *balancer;
         int i;
-        conf = (proxy_server_conf *)ap_get_module_config(sconf, &proxy_module);
+        void *sconf = s->module_config;
+        proxy_server_conf *conf = (proxy_server_conf *)ap_get_module_config(sconf, &proxy_module);
+        apr_status_t rv;
 
-        /* Initialize shared scoreboard data */
-        balancer = (proxy_balancer *)conf->balancers->elts;
-        for (i = 0; i < conf->balancers->nelts; i++) {
-            if (balancer->lbmethod && balancer->lbmethod->reset)
-               balancer->lbmethod->reset(balancer, s);
-            init_balancer_members(conf, s, balancer);
-            balancer++;
+        if (conf->balancers->nelts) {
+            apr_size_t size;
+            unsigned int num;
+            storage->attach(&(conf->bslot), conf->id, &size, &num, p);
+            if (!conf->bslot) {
+                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01205) "slotmem_attach failed");
+                exit(1); /* Ugly, but what else? */
+            }
         }
-        s = s->next;
-    }
 
-}
-
-static const char *set_balancer_nonce (cmd_parms *cmd, void *dummy, const char *arg,
-                                       const char *val)
-{
-    const char *err = ap_check_cmd_context(cmd, GLOBAL_ONLY);
-    if (err != NULL) {
-        return err;
-    }
+        balancer = (proxy_balancer *)conf->balancers->elts;
+        for (i = 0; i < conf->balancers->nelts; i++, balancer++) {
+            rv = ap_proxy_initialize_balancer(balancer, s, p);
 
-    if (!strcasecmp(arg, "None")) {
-        *balancer_nonce = '\0';
-    } else if (!strcasecmp(arg, "Set")) {
-        if (val) {
-            apr_cpystrn(balancer_nonce, val, sizeof(balancer_nonce));
-        } else {
-            return "BalancerNonce Set requires an argument";
+            if (rv != APR_SUCCESS) {
+                ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(01206)
+                             "Failed to init balancer %s in child",
+                             balancer->s->name);
+                exit(1); /* Ugly, but what else? */
+            }
+            init_balancer_members(conf->pool, s, balancer);
         }
-    } else if (strcasecmp(arg, "Default")) {
-        return "Bad argument for BalancerNonce: Must be 'Set', 'None' or 'Default'";
+        s = s->next;
     }
-    return NULL;
-}
 
-static const command_rec balancer_cmds[] =
-{
-    AP_INIT_TAKE12("BalancerNonce", set_balancer_nonce, NULL,
-       RSRC_CONF, "Set value for balancer-manager nonce"),
-    {NULL}
-};
+}
 
 static void ap_proxy_balancer_register_hook(apr_pool_t *p)
 {
     /* Only the mpm_winnt has child init hook handler.
      * make sure that we are called after the mpm
      * initializes
      */
-    static const char *const aszPred[] = { "mpm_winnt.c", NULL};
+    static const char *const aszPred[] = { "mpm_winnt.c", "mod_slotmem_shm.c", NULL};
      /* manager handler */
-    ap_hook_post_config(balancer_init, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_post_config(balancer_post_config, NULL, NULL, APR_HOOK_MIDDLE);
+    ap_hook_pre_config(balancer_pre_config, NULL, NULL, APR_HOOK_MIDDLE);
     ap_hook_handler(balancer_handler, NULL, NULL, APR_HOOK_FIRST);
-    ap_hook_child_init(child_init, aszPred, NULL, APR_HOOK_MIDDLE);
+    ap_hook_child_init(balancer_child_init, aszPred, NULL, APR_HOOK_MIDDLE);
     proxy_hook_pre_request(proxy_balancer_pre_request, NULL, NULL, APR_HOOK_FIRST);
     proxy_hook_post_request(proxy_balancer_post_request, NULL, NULL, APR_HOOK_FIRST);
     proxy_hook_canon_handler(proxy_balancer_canon, NULL, NULL, APR_HOOK_FIRST);
 }
 
 AP_DECLARE_MODULE(proxy_balancer) = {
     STANDARD20_MODULE_STUFF,
     NULL,       /* create per-directory config structure */
     NULL,       /* merge per-directory config structures */
     NULL,       /* create per-server config structure */
     NULL,       /* merge per-server config structures */
-    balancer_cmds,       /* command apr_table_t */
+    NULL,       /* command apr_table_t */
     ap_proxy_balancer_register_hook /* register hooks */
 };
