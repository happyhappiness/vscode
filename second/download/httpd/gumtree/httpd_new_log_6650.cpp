ap_rvputs(r, "<tr>\n<td><a href='",
                          ap_escape_uri(r->pool, r->uri), "?b=",
                          balancer->s->name + sizeof(BALANCER_PREFIX) - 1, "&amp;w=",
                          ap_escape_uri(r->pool, worker->s->name),
                          "&amp;nonce=", balancer->s->nonce,
                          "'>", NULL);