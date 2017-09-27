                   "inherited from main server.</dt>", NULL);
         ap_rputs("</dl>\n", r);
         balancer = (proxy_balancer *)conf->balancers->elts;
         for (i = 0; i < conf->balancers->nelts; i++) {
 
             ap_rputs("<hr />\n<h3>LoadBalancer Status for ", r);
-            ap_rvputs(r, "<a href=\"", ap_escape_uri(r->pool, r->uri), "?b=",
+            ap_rvputs(r, "<a href='", ap_escape_uri(r->pool, r->uri), "?b=",
                       balancer->s->name + sizeof(BALANCER_PREFIX) - 1,
-                      "&nonce=", balancer->s->nonce,
-                      "\">", NULL);
+                      "&amp;nonce=", balancer->s->nonce,
+                      "'>", NULL);
             ap_rvputs(r, balancer->s->name, "</a> [",balancer->s->sname, "]</h3>\n", NULL);
             ap_rputs("\n\n<table><tr>"
                 "<th>MaxMembers</th><th>StickySession</th><th>DisableFailover</th><th>Timeout</th><th>FailoverAttempts</th><th>Method</th>"
                 "<th>Path</th><th>Active</th></tr>\n<tr>", r);
             /* the below is a safe cast, since the number of slots total will
              * never be more than max_workers, which is restricted to int */
