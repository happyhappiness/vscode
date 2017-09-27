            ap_rputs("<hr />\n<h3>LoadBalancer Status for ", r);
            ap_rvputs(r, balancer->name, "</h3>\n\n", NULL);
            ap_rputs("\n\n<table border=\"0\" style=\"text-align: left;\"><tr>"
                "<th>StickySession</th><th>Timeout</th><th>FailoverAttempts</th><th>Method</th>"
                "</tr>\n<tr>", r);
            if (balancer->sticky) {
                ap_rvputs(r, "<td>", balancer->sticky, NULL);
            }
            else {
                ap_rputs("<td> - ", r);
            }
            ap_rprintf(r, "</td><td>%" APR_TIME_T_FMT "</td>",
                apr_time_sec(balancer->timeout));
