            ap_rprintf(r, "<td>%s</td>\n",
                       balancer->lbmethod->name);
            ap_rputs("</table>\n<br />", r);
            ap_rputs("\n\n<table border=\"0\" style=\"text-align: left;\"><tr>"
                "<th>Worker URL</th>"
                "<th>Route</th><th>RouteRedir</th>"
                "<th>Factor</th><th>Status</th>"
                "</tr>\n", r);

            worker = (proxy_worker *)balancer->workers->elts;
            for (n = 0; n < balancer->workers->nelts; n++) {

                ap_rvputs(r, "<tr>\n<td><a href=\"", r->uri, "?b=",
                          balancer->name + sizeof("balancer://") - 1, "&w=",
                          ap_escape_uri(r->pool, worker->name),
                          "\">", NULL);
                ap_rvputs(r, worker->name, "</a></td>", NULL);
                ap_rvputs(r, "<td>", worker->s->route, NULL);
                ap_rvputs(r, "</td><td>", worker->s->redirect, NULL);
                ap_rprintf(r, "</td><td>%d</td><td>", worker->s->lbfactor);
                if (worker->s->status & PROXY_WORKER_DISABLED)
                    ap_rputs("Dis", r);
                else if (worker->s->status & PROXY_WORKER_IN_ERROR)
                    ap_rputs("Err", r);
                else if (worker->s->status & PROXY_WORKER_INITIALIZED)
                    ap_rputs("Ok", r);
                else
                    ap_rputs("-", r);
                ap_rputs("</td></tr>\n", r);

                ++worker;
            }
            ap_rputs("</table>\n", r);
            ++balancer;
