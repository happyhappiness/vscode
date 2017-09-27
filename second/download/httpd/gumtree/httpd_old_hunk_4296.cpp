                    ap_rvputs(r, "<td>", balancer->s->sticky, NULL);
                }
            }
            else {
                ap_rputs("<td> (None) ", r);
            }
            ap_rprintf(r, "<td>%s</td>\n",
                       balancer->s->sticky_force ? "On" : "Off");
            ap_rprintf(r, "</td><td>%" APR_TIME_T_FMT "</td>",
                apr_time_sec(balancer->s->timeout));
            ap_rprintf(r, "<td>%d</td>\n", balancer->s->max_attempts);
            ap_rprintf(r, "<td>%s</td>\n",
                       balancer->s->lbpname);
            ap_rputs("<td>", r);
            if (*balancer->s->vhost) {
