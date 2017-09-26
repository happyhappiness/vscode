                char fbuf[50];
                ap_rvputs(r, "<tr>\n<td><a href=\"", r->uri, "?b=",
                          balancer->name + sizeof("balancer://") - 1, "&w=",
                          ap_escape_uri(r->pool, worker->name),
                          "\">", NULL);
                ap_rvputs(r, worker->name, "</a></td>", NULL);
                ap_rvputs(r, "<td>", worker->s->route, NULL);
                ap_rvputs(r, "</td><td>", worker->s->redirect, NULL);
                ap_rprintf(r, "</td><td>%d</td>", worker->s->lbfactor);
                ap_rprintf(r, "<td>%d</td><td>", worker->s->lbset);
                if (worker->s->status & PROXY_WORKER_DISABLED)
                   ap_rputs("Dis ", r);
                if (worker->s->status & PROXY_WORKER_IN_ERROR)
                   ap_rputs("Err ", r);
