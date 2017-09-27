    }

    action = ap_construct_url(r->pool, r->uri, r);
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01204) "genning page");

    if (apr_table_get(params, "xml")) {
        ap_set_content_type(r, "text/xml");
        ap_rputs("<?xml version='1.0' encoding='UTF-8' ?>\n", r);
        ap_rputs("<httpd:manager xmlns:httpd='http://httpd.apache.org'>\n", r);
        ap_rputs("  <httpd:balancers>\n", r);
        balancer = (proxy_balancer *)conf->balancers->elts;
        for (i = 0; i < conf->balancers->nelts; i++) {
            ap_rputs("    <httpd:balancer>\n", r);
            ap_rvputs(r, "      <httpd:name>", balancer->s->name, "</httpd:name>\n", NULL);
            ap_rputs("      <httpd:workers>\n", r);
            workers = (proxy_worker **)balancer->workers->elts;
            for (n = 0; n < balancer->workers->nelts; n++) {
                worker = *workers;
                ap_rputs("        <httpd:worker>\n", r);
                ap_rvputs(r, "          <httpd:scheme>", worker->s->scheme,
                          "</httpd:scheme>\n", NULL);
                ap_rvputs(r, "          <httpd:hostname>", worker->s->hostname,
                          "</httpd:hostname>\n", NULL);
                ap_rprintf(r, "          <httpd:loadfactor>%d</httpd:loadfactor>\n",
                          worker->s->lbfactor);
                ap_rputs("        </httpd:worker>\n", r);
                ++workers;
            }
            ap_rputs("      </httpd:workers>\n", r);
            ap_rputs("    </httpd:balancer>\n", r);
            ++balancer;
