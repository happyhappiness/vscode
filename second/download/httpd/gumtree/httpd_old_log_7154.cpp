ap_rvputs(r, "<a href='", r->uri, "?b=",
                      balancer->s->name + sizeof(BALANCER_PREFIX) - 1,
                      "&nonce=", balancer->s->nonce,
                      "'>", NULL);