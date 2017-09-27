                "</tr>\n", r);

            workers = (proxy_worker **)balancer->workers->elts;
            for (n = 0; n < balancer->workers->nelts; n++) {
                char fbuf[50];
                worker = *workers;
                ap_rvputs(r, "<tr>\n<td><a href='", r->uri, "?b=",
                          balancer->s->name + sizeof(BALANCER_PREFIX) - 1, "&w=",
                          ap_escape_uri(r->pool, worker->s->name),
                          "&nonce=", balancer->s->nonce,
                          "'>", NULL);
                ap_rvputs(r, worker->s->name, "</a></td>", NULL);
                ap_rvputs(r, "<td>", ap_escape_html(r->pool, worker->s->route),
                          NULL);
                ap_rvputs(r, "</td><td>",
                          ap_escape_html(r->pool, worker->s->redirect), NULL);
                ap_rprintf(r, "</td><td>%d</td>", worker->s->lbfactor);
