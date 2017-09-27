             ap_rprintf(r, "<td>%s</td>\n",
                        balancer->lbmethod->name);
             ap_rputs("</table>\n<br />", r);
             ap_rputs("\n\n<table border=\"0\" style=\"text-align: left;\"><tr>"
                 "<th>Worker URL</th>"
                 "<th>Route</th><th>RouteRedir</th>"
-                "<th>Factor</th><th>Status</th>"
+                "<th>Factor</th><th>Set</th><th>Status</th>"
+                "<th>Elected</th><th>To</th><th>From</th>"
                 "</tr>\n", r);
 
             worker = (proxy_worker *)balancer->workers->elts;
             for (n = 0; n < balancer->workers->nelts; n++) {
-
+                char fbuf[50];
                 ap_rvputs(r, "<tr>\n<td><a href=\"", r->uri, "?b=",
                           balancer->name + sizeof("balancer://") - 1, "&w=",
                           ap_escape_uri(r->pool, worker->name),
                           "\">", NULL);
                 ap_rvputs(r, worker->name, "</a></td>", NULL);
                 ap_rvputs(r, "<td>", worker->s->route, NULL);
                 ap_rvputs(r, "</td><td>", worker->s->redirect, NULL);
-                ap_rprintf(r, "</td><td>%d</td><td>", worker->s->lbfactor);
+                ap_rprintf(r, "</td><td>%d</td>", worker->s->lbfactor);
+                ap_rprintf(r, "<td>%d</td><td>", worker->s->lbset);
                 if (worker->s->status & PROXY_WORKER_DISABLED)
-                    ap_rputs("Dis", r);
-                else if (worker->s->status & PROXY_WORKER_IN_ERROR)
-                    ap_rputs("Err", r);
-                else if (worker->s->status & PROXY_WORKER_INITIALIZED)
+                   ap_rputs("Dis ", r);
+                if (worker->s->status & PROXY_WORKER_IN_ERROR)
+                   ap_rputs("Err ", r);
+                if (worker->s->status & PROXY_WORKER_STOPPED)
+                   ap_rputs("Stop ", r);
+                if (worker->s->status & PROXY_WORKER_HOT_STANDBY)
+                   ap_rputs("Stby ", r);
+                if (PROXY_WORKER_IS_USABLE(worker))
                     ap_rputs("Ok", r);
-                else
+                if (!PROXY_WORKER_IS_INITIALIZED(worker))
                     ap_rputs("-", r);
+                ap_rputs("</td>", r);
+                ap_rprintf(r, "<td>%" APR_SIZE_T_FMT "</td><td>", worker->s->elected);
+                ap_rputs(apr_strfsize(worker->s->transferred, fbuf), r);
+                ap_rputs("</td><td>", r);
+                ap_rputs(apr_strfsize(worker->s->read, fbuf), r);
                 ap_rputs("</td></tr>\n", r);
 
                 ++worker;
             }
             ap_rputs("</table>\n", r);
             ++balancer;
