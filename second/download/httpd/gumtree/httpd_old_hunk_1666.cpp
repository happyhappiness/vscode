        ap_rputs("  <httpd:balancers>\n", r);
        balancer = (proxy_balancer *)conf->balancers->elts;
        for (i = 0; i < conf->balancers->nelts; i++) {
            ap_rputs("    <httpd:balancer>\n", r);
            ap_rvputs(r, "      <httpd:name>", balancer->name, "</httpd:name>\n", NULL);
            ap_rputs("      <httpd:workers>\n", r);
            worker = (proxy_worker *)balancer->workers->elts;
            for (n = 0; n < balancer->workers->nelts; n++) {
                ap_rputs("        <httpd:worker>\n", r);
                ap_rvputs(r, "          <httpd:scheme>", worker->scheme,
                          "</httpd:scheme>\n", NULL);
                ap_rvputs(r, "          <httpd:hostname>", worker->hostname,
                          "</httpd:hostname>\n", NULL);
               ap_rprintf(r, "          <httpd:loadfactor>%d</httpd:loadfactor>\n",
                          worker->s->lbfactor);
                ap_rputs("        </httpd:worker>\n", r);
                ++worker;
            }
            ap_rputs("      </httpd:workers>\n", r);
            ap_rputs("    </httpd:balancer>\n", r);
            ++balancer;
        }
        ap_rputs("  </httpd:balancers>\n", r);
