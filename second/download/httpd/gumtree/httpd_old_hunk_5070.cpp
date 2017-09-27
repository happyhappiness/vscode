        ap_rputs("<body><h1>Load Balancer Manager for ", r);
        ap_rvputs(r, ap_escape_html(r->pool, ap_get_server_name(r)),
                  "</h1>\n\n", NULL);
        ap_rvputs(r, "<dl><dt>Server Version: ",
                  ap_get_server_description(), "</dt>\n", NULL);
        ap_rvputs(r, "<dt>Server Built: ",
                  ap_get_server_built(), "\n</dt></dl>\n", NULL);
        balancer = (proxy_balancer *)conf->balancers->elts;
        for (i = 0; i < conf->balancers->nelts; i++) {

            ap_rputs("<hr />\n<h3>LoadBalancer Status for ", r);
            ap_rvputs(r, "<a href=\"", ap_escape_uri(r->pool, r->uri), "?b=",
                      balancer->s->name + sizeof(BALANCER_PREFIX) - 1,
