ap_rvputs(r, "<a href='", ap_escape_uri(r->pool, r->uri), "?b=",
                      balancer->s->name + sizeof(BALANCER_PREFIX) - 1,
                      "&amp;nonce=", balancer->s->nonce,
                      "'>", NULL);