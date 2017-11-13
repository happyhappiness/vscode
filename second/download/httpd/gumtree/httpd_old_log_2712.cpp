ap_rvputs(r, "<a href=\"", r->uri, "?b=",
                      balancer->name + sizeof("balancer://") - 1,
                      "\">", NULL);