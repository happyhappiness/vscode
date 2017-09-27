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
