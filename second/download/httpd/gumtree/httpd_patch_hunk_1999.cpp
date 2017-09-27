         if (wsel && bsel) {
             ap_rputs("<h3>Edit worker settings for ", r);
             ap_rvputs(r, wsel->name, "</h3>\n", NULL);
             ap_rvputs(r, "<form method=\"GET\" action=\"", NULL);
             ap_rvputs(r, r->uri, "\">\n<dl>", NULL);
             ap_rputs("<table><tr><td>Load factor:</td><td><input name=\"lf\" type=text ", r);
-            ap_rprintf(r, "value=\"%d\"></td><tr>\n", wsel->s->lbfactor);
+            ap_rprintf(r, "value=\"%d\"></td></tr>\n", wsel->s->lbfactor);
+            ap_rputs("<tr><td>LB Set:</td><td><input name=\"ls\" type=text ", r);
+            ap_rprintf(r, "value=\"%d\"></td></tr>\n", wsel->s->lbset);
             ap_rputs("<tr><td>Route:</td><td><input name=\"wr\" type=text ", r);
             ap_rvputs(r, "value=\"", wsel->route, NULL);
-            ap_rputs("\"></td><tr>\n", r);
+            ap_rputs("\"></td></tr>\n", r);
             ap_rputs("<tr><td>Route Redirect:</td><td><input name=\"rr\" type=text ", r);
             ap_rvputs(r, "value=\"", wsel->redirect, NULL);
-            ap_rputs("\"></td><tr>\n", r);
+            ap_rputs("\"></td></tr>\n", r);
             ap_rputs("<tr><td>Status:</td><td>Disabled: <input name=\"dw\" value=\"Disable\" type=radio", r);
             if (wsel->s->status & PROXY_WORKER_DISABLED)
                 ap_rputs(" checked", r);
             ap_rputs("> | Enabled: <input name=\"dw\" value=\"Enable\" type=radio", r);
             if (!(wsel->s->status & PROXY_WORKER_DISABLED))
                 ap_rputs(" checked", r);
-            ap_rputs("></td><tr>\n", r);
+            ap_rputs("></td></tr>\n", r);
             ap_rputs("<tr><td colspan=2><input type=submit value=\"Submit\"></td></tr>\n", r);
             ap_rvputs(r, "</table>\n<input type=hidden name=\"w\" ",  NULL);
             ap_rvputs(r, "value=\"", ap_escape_uri(r->pool, wsel->name), "\">\n", NULL);
             ap_rvputs(r, "<input type=hidden name=\"b\" ", NULL);
             ap_rvputs(r, "value=\"", bsel->name + sizeof("balancer://") - 1,
                       "\">\n</form>\n", NULL);
