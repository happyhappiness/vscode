            ap_rputs("</table>\n", r);
            ++balancer;
        }
        ap_rputs("<hr />\n", r);
        if (wsel && bsel) {
            ap_rputs("<h3>Edit worker settings for ", r);
            ap_rvputs(r, (*wsel->s->uds_path?"<i>":""), ap_proxy_worker_name(r->pool, wsel), (*wsel->s->uds_path?"</i>":""), "</h3>\n", NULL);
            ap_rputs("<form method=\"POST\" enctype=\"application/x-www-form-urlencoded\" action=\"", r);
            ap_rvputs(r, ap_escape_uri(r->pool, action), "\">\n", NULL);
            ap_rputs("<dl>\n<table><tr><td>Load factor:</td><td><input name='w_lf' id='w_lf' type=text ", r);
            ap_rprintf(r, "value='%d'></td></tr>\n", wsel->s->lbfactor);
            ap_rputs("<tr><td>LB Set:</td><td><input name='w_ls' id='w_ls' type=text ", r);
            ap_rprintf(r, "value='%d'></td></tr>\n", wsel->s->lbset);
