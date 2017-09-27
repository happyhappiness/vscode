                 ap_rprintf(r, "<td>%" APR_SIZE_T_FMT "</td>", worker->s->elected);
                 ap_rprintf(r, "<td>%" APR_SIZE_T_FMT "</td>", worker->s->busy);
                 ap_rprintf(r, "<td>%d</td><td>", worker->s->lbstatus);
                 ap_rputs(apr_strfsize(worker->s->transferred, fbuf), r);
                 ap_rputs("</td><td>", r);
                 ap_rputs(apr_strfsize(worker->s->read, fbuf), r);
+                if (set_worker_hc_param_f) {
+                    ap_rprintf(r, "</td><td>%s</td>", ap_proxy_show_hcmethod(worker->s->method));
+                    ap_rprintf(r, "<td>%d</td>", (int)apr_time_sec(worker->s->interval));
+                    ap_rprintf(r, "<td>%d (%d)</td>", worker->s->passes,worker->s->pcount);
+                    ap_rprintf(r, "<td>%d (%d)</td>", worker->s->fails, worker->s->fcount);
+                    ap_rprintf(r, "<td>%s</td>", worker->s->hcuri);
+                    ap_rprintf(r, "<td>%s", worker->s->hcexpr);
+                }
                 ap_rputs("</td></tr>\n", r);
 
                 ++workers;
             }
             ap_rputs("</table>\n", r);
             ++balancer;
         }
         ap_rputs("<hr />\n", r);
+        if (hc_show_exprs_f) {
+            hc_show_exprs_f(r);
+        }
         if (wsel && bsel) {
             ap_rputs("<h3>Edit worker settings for ", r);
             ap_rvputs(r, (*wsel->s->uds_path?"<i>":""), ap_proxy_worker_name(r->pool, wsel), (*wsel->s->uds_path?"</i>":""), "</h3>\n", NULL);
-            ap_rputs("<form method=\"POST\" enctype=\"application/x-www-form-urlencoded\" action=\"", r);
-            ap_rvputs(r, ap_escape_uri(r->pool, action), "\">\n", NULL);
-            ap_rputs("<dl>\n<table><tr><td>Load factor:</td><td><input name='w_lf' id='w_lf' type=text ", r);
+            ap_rputs("<form method='POST' enctype='application/x-www-form-urlencoded' action='", r);
+            ap_rvputs(r, ap_escape_uri(r->pool, action), "'>\n", NULL);
+            ap_rputs("<table><tr><td>Load factor:</td><td><input name='w_lf' id='w_lf' type=text ", r);
             ap_rprintf(r, "value='%d'></td></tr>\n", wsel->s->lbfactor);
             ap_rputs("<tr><td>LB Set:</td><td><input name='w_ls' id='w_ls' type=text ", r);
             ap_rprintf(r, "value='%d'></td></tr>\n", wsel->s->lbset);
             ap_rputs("<tr><td>Route:</td><td><input name='w_wr' id='w_wr' type=text ", r);
-            ap_rvputs(r, "value=\"", ap_escape_html(r->pool, wsel->s->route),
+            ap_rvputs(r, "value='", ap_escape_html(r->pool, wsel->s->route),
                       NULL);
-            ap_rputs("\"></td></tr>\n", r);
+            ap_rputs("'></td></tr>\n", r);
             ap_rputs("<tr><td>Route Redirect:</td><td><input name='w_rr' id='w_rr' type=text ", r);
-            ap_rvputs(r, "value=\"", ap_escape_html(r->pool, wsel->s->redirect),
+            ap_rvputs(r, "value='", ap_escape_html(r->pool, wsel->s->redirect),
                       NULL);
-            ap_rputs("\"></td></tr>\n", r);
+            ap_rputs("'></td></tr>\n", r);
             ap_rputs("<tr><td>Status:</td>", r);
             ap_rputs("<td><table><tr>"
                      "<th>Ignore Errors</th>"
                      "<th>Draining Mode</th>"
                      "<th>Disabled</th>"
-                     "<th>Hot Standby</th></tr>\n<tr>", r);
-            create_radio("w_status_I", (PROXY_WORKER_IGNORE_ERRORS & wsel->s->status), r);
-            create_radio("w_status_N", (PROXY_WORKER_DRAIN & wsel->s->status), r);
-            create_radio("w_status_D", (PROXY_WORKER_DISABLED & wsel->s->status), r);
-            create_radio("w_status_H", (PROXY_WORKER_HOT_STANDBY & wsel->s->status), r);
-            ap_rputs("</tr></table>\n", r);
-            ap_rputs("<tr><td colspan=2><input type=submit value='Submit'></td></tr>\n", r);
+                     "<th>Hot Standby</th>", r);
+            if (hc_show_exprs_f) {
+                ap_rputs("<th>HC Fail</th>", r);
+            }
+            ap_rputs("<th>Stopped</th></tr>\n<tr>", r);
+            create_radio("w_status_I", (PROXY_WORKER_IS(wsel, PROXY_WORKER_IGNORE_ERRORS)), r);
+            create_radio("w_status_N", (PROXY_WORKER_IS(wsel, PROXY_WORKER_DRAIN)), r);
+            create_radio("w_status_D", (PROXY_WORKER_IS(wsel, PROXY_WORKER_DISABLED)), r);
+            create_radio("w_status_H", (PROXY_WORKER_IS(wsel, PROXY_WORKER_HOT_STANDBY)), r);
+            if (hc_show_exprs_f) {
+                create_radio("w_status_C", (PROXY_WORKER_IS(wsel, PROXY_WORKER_HC_FAIL)), r);
+            }
+            create_radio("w_status_S", (PROXY_WORKER_IS(wsel, PROXY_WORKER_STOPPED)), r);
+            ap_rputs("</tr></table></td></tr>\n", r);
+            if (hc_select_exprs_f) {
+                proxy_hcmethods_t *method = proxy_hcmethods;
+                ap_rputs("<tr><td colspan='2'>\n<table align='center'><tr><th>Health Check param</th><th>Value</th></tr>\n", r);
+                ap_rputs("<tr><td>Method</td><td><select name='w_hm'>\n", r);
+                for (; method->name; method++) {
+                    if (method->implemented) {
+                        ap_rprintf(r, "<option value='%s' %s >%s</option>\n",
+                                method->name,
+                                (wsel->s->method == method->method) ? "selected" : "",
+                                method->name);
+                    }
+                }
+                ap_rputs("</select>\n</td></tr>\n", r);
+                ap_rputs("<tr><td>Expr</td><td><select name='w_he'>\n", r);
+                hc_select_exprs_f(r, wsel->s->hcexpr);
+                ap_rputs("</select>\n</td></tr>\n", r);
+                ap_rprintf(r, "<tr><td>Interval (secs)</td><td><input name='w_hi' id='w_hi' type='text'"
+                           "value='%d'></td></tr>\n", (int)apr_time_sec(wsel->s->interval));
+                ap_rprintf(r, "<tr><td>Passes trigger</td><td><input name='w_hp' id='w_hp' type='text'"
+                           "value='%d'></td></tr>\n", wsel->s->passes);
+                ap_rprintf(r, "<tr><td>Fails trigger)</td><td><input name='w_hf' id='w_hf' type='text'"
+                           "value='%d'></td></tr>\n", wsel->s->fails);
+                ap_rprintf(r, "<tr><td>HC uri</td><td><input name='w_hu' id='w_hu' type='text'"
+                        "value='%s'</td></tr>\n", ap_escape_html(r->pool, wsel->s->hcuri));
+                ap_rputs("</table>\n</td></tr>\n", r);
+            }
+            ap_rputs("<tr><td colspan='2'><input type=submit value='Submit'></td></tr>\n", r);
             ap_rvputs(r, "</table>\n<input type=hidden name='w' id='w' ",  NULL);
             ap_rvputs(r, "value='", ap_escape_uri(r->pool, wsel->s->name), "'>\n", NULL);
             ap_rvputs(r, "<input type=hidden name='b' id='b' ", NULL);
             ap_rvputs(r, "value='", bsel->s->name + sizeof(BALANCER_PREFIX) - 1,
                       "'>\n", NULL);
             ap_rvputs(r, "<input type=hidden name='nonce' id='nonce' value='",
