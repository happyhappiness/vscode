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
            ap_rputs("</td><td>", r);
            ap_rputs(apr_strfsize((*worker)->s->read, fbuf), r);
            ap_rputs("</td>\n", r);

            /* TODO: Add the rest of dynamic worker data */
            ap_rputs("</tr>\n", r);

            ++worker;
