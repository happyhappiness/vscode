                "<th>Worker URL</th>"
                "<th>Route</th><th>RouteRedir</th>"
                "<th>Factor</th><th>Set</th><th>Status</th>"
                "<th>Elected</th><th>To</th><th>From</th>"
                "</tr>\n", r);

            worker = (proxy_worker *)balancer->workers->elts;
            for (n = 0; n < balancer->workers->nelts; n++) {
                char fbuf[50];
                ap_rvputs(r, "<tr>\n<td><a href=\"",
                          ap_escape_uri(r->pool, r->uri), "?b=",
                          balancer->name + sizeof("balancer://") - 1, "&w=",
                          ap_escape_uri(r->pool, worker->name),
                          "&nonce=", balancer_nonce, 
                          "\">", NULL);
                ap_rvputs(r, worker->name, "</a></td>", NULL);
                ap_rvputs(r, "<td>", ap_escape_html(r->pool, worker->s->route),
