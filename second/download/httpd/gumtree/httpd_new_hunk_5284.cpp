            const apr_array_header_t *provs;
            const ap_list_provider_names_t *pname;
            int i;
            ap_rputs("<h3>Edit balancer settings for ", r);
            ap_rvputs(r, bsel->s->name, "</h3>\n", NULL);
            ap_rputs("<form method='POST' enctype='application/x-www-form-urlencoded' action='", r);
            ap_rvputs(r, ap_escape_uri(r->pool, action), "'>\n", NULL);
            ap_rputs("<dl>\n<table>\n", r);
            provs = ap_list_provider_names(r->pool, PROXY_LBMETHOD, "0");
            if (provs) {
                ap_rputs("<tr><td>LBmethod:</td>", r);
                ap_rputs("<td>\n<select name='b_lbm' id='b_lbm'>", r);
                pname = (ap_list_provider_names_t *)provs->elts;
