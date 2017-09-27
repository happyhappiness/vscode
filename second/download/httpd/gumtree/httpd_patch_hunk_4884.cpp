             ++balancer;
         }
         ap_rputs("<hr />\n", r);
         if (wsel && bsel) {
             ap_rputs("<h3>Edit worker settings for ", r);
             ap_rvputs(r, wsel->s->name, "</h3>\n", NULL);
-            ap_rputs("<form method='POST' enctype='application/x-www-form-urlencoded' action='", r);
-            ap_rvputs(r, action, "'>\n", NULL);
+            ap_rputs("<form method=\"POST\" enctype=\"application/x-www-form-urlencoded\" action=\"", r);
+            ap_rvputs(r, ap_escape_uri(r->pool, action), "\">\n", NULL);
             ap_rputs("<dl>\n<table><tr><td>Load factor:</td><td><input name='w_lf' id='w_lf' type=text ", r);
             ap_rprintf(r, "value='%d'></td></tr>\n", wsel->s->lbfactor);
             ap_rputs("<tr><td>LB Set:</td><td><input name='w_ls' id='w_ls' type=text ", r);
             ap_rprintf(r, "value='%d'></td></tr>\n", wsel->s->lbset);
             ap_rputs("<tr><td>Route:</td><td><input name='w_wr' id='w_wr' type=text ", r);
-            ap_rvputs(r, "value='", ap_escape_html(r->pool, wsel->s->route),
+            ap_rvputs(r, "value=\"", ap_escape_html(r->pool, wsel->s->route),
                       NULL);
-            ap_rputs("'></td></tr>\n", r);
+            ap_rputs("\"></td></tr>\n", r);
             ap_rputs("<tr><td>Route Redirect:</td><td><input name='w_rr' id='w_rr' type=text ", r);
-            ap_rvputs(r, "value='", ap_escape_html(r->pool, wsel->s->redirect),
+            ap_rvputs(r, "value=\"", ap_escape_html(r->pool, wsel->s->redirect),
                       NULL);
-            ap_rputs("'></td></tr>\n", r);
+            ap_rputs("\"></td></tr>\n", r);
             ap_rputs("<tr><td>Status:</td>", r);
-            ap_rputs("<td><table><tr><th>Ign</th><th>Drn</th><th>Dis</th><th>Stby</th></tr>\n<tr>", r);
+            ap_rputs("<td><table><tr>"
+                     "<th>Ignore Errors</th>"
+                     "<th>Draining Mode</th>"
+                     "<th>Disabled</th>"
+                     "<th>Hot Standby</th></tr>\n<tr>", r);
             create_radio("w_status_I", (PROXY_WORKER_IGNORE_ERRORS & wsel->s->status), r);
             create_radio("w_status_N", (PROXY_WORKER_DRAIN & wsel->s->status), r);
             create_radio("w_status_D", (PROXY_WORKER_DISABLED & wsel->s->status), r);
             create_radio("w_status_H", (PROXY_WORKER_HOT_STANDBY & wsel->s->status), r);
             ap_rputs("</tr></table>\n", r);
             ap_rputs("<tr><td colspan=2><input type=submit value='Submit'></td></tr>\n", r);
