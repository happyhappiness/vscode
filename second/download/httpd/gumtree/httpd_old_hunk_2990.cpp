        conf->proxy_status == status_off)
        return OK;

    balancer = (proxy_balancer *)conf->balancers->elts;
    for (i = 0; i < conf->balancers->nelts; i++) {
        ap_rputs("<hr />\n<h1>Proxy LoadBalancer Status for ", r);
        ap_rvputs(r, balancer->name, "</h1>\n\n", NULL);
        ap_rputs("\n\n<table border=\"0\"><tr>"
                 "<th>SSes</th><th>Timeout</th><th>Method</th>"
                 "</tr>\n<tr>", r);
        if (balancer->sticky) {
            if (strcmp(balancer->sticky, balancer->sticky_path)) {
                ap_rvputs(r, "<td>", balancer->sticky, " | ",
                          balancer->sticky_path, NULL);
            }
            else {
                ap_rvputs(r, "<td>", balancer->sticky, NULL);
            }
        }
        else {
            ap_rputs("<td> - ", r);
        }
        ap_rprintf(r, "</td><td>%" APR_TIME_T_FMT "</td>",
                   apr_time_sec(balancer->timeout));
        ap_rprintf(r, "<td>%s</td>\n",
                   balancer->lbmethod->name);
        ap_rputs("</table>\n", r);
        ap_rputs("\n\n<table border=\"0\"><tr>"
                 "<th>Sch</th><th>Host</th><th>Stat</th>"
                 "<th>Route</th><th>Redir</th>"
                 "<th>F</th><th>Set</th><th>Acc</th><th>Wr</th><th>Rd</th>"
                 "</tr>\n", r);

        worker = (proxy_worker **)balancer->workers->elts;
        for (n = 0; n < balancer->workers->nelts; n++) {
            char fbuf[50];
            ap_rvputs(r, "<tr>\n<td>", (*worker)->scheme, "</td>", NULL);
            ap_rvputs(r, "<td>", (*worker)->hostname, "</td><td>", NULL);
            if ((*worker)->s->status & PROXY_WORKER_DISABLED)
                ap_rputs("Dis", r);
            else if ((*worker)->s->status & PROXY_WORKER_IN_ERROR)
                ap_rputs("Err", r);
            else if ((*worker)->s->status & PROXY_WORKER_INITIALIZED)
                ap_rputs("Ok", r);
            else
                ap_rputs("-", r);
            ap_rvputs(r, "</td><td>", (*worker)->s->route, NULL);
            ap_rvputs(r, "</td><td>", (*worker)->s->redirect, NULL);
            ap_rprintf(r, "</td><td>%d</td>", (*worker)->s->lbfactor);
            ap_rprintf(r, "<td>%d</td>", (*worker)->s->lbset);
            ap_rprintf(r, "<td>%" APR_SIZE_T_FMT "</td><td>", (*worker)->s->elected);
            ap_rputs(apr_strfsize((*worker)->s->transferred, fbuf), r);
