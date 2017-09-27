         ap_rputs("  <httpd:balancers>\n", r);
         balancer = (proxy_balancer *)conf->balancers->elts;
         for (i = 0; i < conf->balancers->nelts; i++) {
             ap_rputs("    <httpd:balancer>\n", r);
             /* Start proxy_balancer */
             ap_rvputs(r, "      <httpd:name>", balancer->s->name, "</httpd:name>\n", NULL);
-            if (balancer->s->sticky) {
+            if (*balancer->s->sticky) {
                 ap_rvputs(r, "      <httpd:stickysession>", balancer->s->sticky,
                           "</httpd:stickysession>\n", NULL);
                 ap_rprintf(r,
                            "      <httpd:nofailover>%s</httpd:nofailover>\n",
                            (balancer->s->sticky_force ? "On" : "Off"));
             }
