                       !balancer->s->inactive ? "Yes" : "No");
            ap_rputs("</table>\n<br />", r);
            ap_rputs("\n\n<table><tr>"
                "<th>Worker URL</th>"
                "<th>Route</th><th>RouteRedir</th>"
                "<th>Factor</th><th>Set</th><th>Status</th>"
                "<th>Elected</th><th>Busy</th><th>Load</th><th>To</th><th>From</th>"
                "</tr>\n", r);

            workers = (proxy_worker **)balancer->workers->elts;
            for (n = 0; n < balancer->workers->nelts; n++) {
                char fbuf[50];
                worker = *workers;
                ap_rvputs(r, "<tr>\n<td><a href=\"",
                          ap_escape_uri(r->pool, r->uri), "?b=",
                          balancer->s->name + sizeof(BALANCER_PREFIX) - 1, "&w=",
                          ap_escape_uri(r->pool, worker->s->name),
                          "&nonce=", balancer->s->nonce,
                          "\">", NULL);
                ap_rvputs(r, (*worker->s->uds_path ? "<i>" : ""), ap_proxy_worker_name(r->pool, worker),
                          (*worker->s->uds_path ? "</i>" : ""), "</a></td>", NULL);
                ap_rvputs(r, "<td>", ap_escape_html(r->pool, worker->s->route),
                          NULL);
                ap_rvputs(r, "</td><td>",
                          ap_escape_html(r->pool, worker->s->redirect), NULL);
