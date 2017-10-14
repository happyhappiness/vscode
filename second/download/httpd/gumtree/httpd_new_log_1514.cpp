ap_rvputs(r, "<tr>\n<td><a href=\"",
                          ap_escape_uri(r->pool, r->uri), "?b=",
                          balancer->name + sizeof("balancer://") - 1, "&w=",
                          ap_escape_uri(r->pool, worker->name),
                          "&nonce=", balancer_nonce, 
                          "\">", NULL);