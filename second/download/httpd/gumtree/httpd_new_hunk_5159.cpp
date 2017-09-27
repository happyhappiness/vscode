            ap_rputs("      <httpd:workers>\n", r);
            workers = (proxy_worker **)balancer->workers->elts;
            for (n = 0; n < balancer->workers->nelts; n++) {
                worker = *workers;
                /* Start proxy_worker */
                ap_rputs("        <httpd:worker>\n", r);
                ap_rvputs(r, "          <httpd:name>", ap_proxy_worker_name(r->pool, worker),
                          "</httpd:name>\n", NULL);
                ap_rvputs(r, "          <httpd:scheme>", worker->s->scheme,
                          "</httpd:scheme>\n", NULL);
                ap_rvputs(r, "          <httpd:hostname>", worker->s->hostname,
                          "</httpd:hostname>\n", NULL);
                ap_rprintf(r, "          <httpd:loadfactor>%d</httpd:loadfactor>\n",
