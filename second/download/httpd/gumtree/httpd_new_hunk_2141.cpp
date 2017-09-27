            ++balancer;
        }
        ap_rputs("  </httpd:balancers>\n", r);
        ap_rputs("</httpd:manager>", r);
    }
    else {
        ap_set_content_type(r, "text/html; charset=ISO-8859-1");
        ap_rputs(DOCTYPE_HTML_3_2
                 "<html><head><title>Balancer Manager</title></head>\n", r);
        ap_rputs("<body><h1>Load Balancer Manager for ", r);
        ap_rvputs(r, ap_get_server_name(r), "</h1>\n\n", NULL);
        ap_rvputs(r, "<dl><dt>Server Version: ",
                  ap_get_server_description(), "</dt>\n", NULL);
        ap_rvputs(r, "<dt>Server Built: ",
                  ap_get_server_built(), "\n</dt></dl>\n", NULL);
        balancer = (proxy_balancer *)conf->balancers->elts;
        for (i = 0; i < conf->balancers->nelts; i++) {

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
            ap_rprintf(r, "<td>%d</td>\n", balancer->max_attempts);
            ap_rprintf(r, "<td>%s</td>\n",
                       balancer->lbmethod->name);
            ap_rputs("</table>\n<br />", r);
