ap_rvputs(r, "<a href=\"", ap_escape_uri(r->pool, r->uri), "?b=",
                      balancer->s->name + sizeof(BALANCER_PREFIX) - 1,
                      "&nonce=", balancer->s->nonce,
                      "\">", NULL);