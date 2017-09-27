                 ap_rprintf(r,
                            "      <httpd:maxattempts>%d</httpd:maxattempts>\n",
                            balancer->s->max_attempts);
             }
             ap_rvputs(r, "      <httpd:lbmethod>", balancer->lbmethod->name,
                       "</httpd:lbmethod>\n", NULL);
-            if (balancer->s->sticky) {
+            if (*balancer->s->sticky) {
                 ap_rprintf(r,
                            "      <httpd:scolonpathdelim>%s</httpd:scolonpathdelim>\n",
                            (balancer->s->scolonsep ? "On" : "Off"));
             }
             /* End proxy_balancer */
             ap_rputs("      <httpd:workers>\n", r);
