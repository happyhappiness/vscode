         ap_rputs("  </httpd:balancers>\n", r);
         ap_rputs("</httpd:manager>", r);
     }
     else {
         ap_set_content_type(r, "text/html; charset=ISO-8859-1");
         ap_rputs(DOCTYPE_HTML_3_2
-                 "<html><head><title>Balancer Manager</title></head>\n", r);
+                 "<html><head><title>Balancer Manager</title>\n", r);
+        ap_rputs("<style type='text/css'>\n"
+                 "table {\n"
+                 " border-width: 1px;\n"
+                 " border-spacing: 3px;\n"
+                 " border-style: solid;\n"
+                 " border-color: gray;\n"
+                 " border-collapse: collapse;\n"
+                 " background-color: white;\n"
+                 " text-align: center;\n"
+                 "}\n"
+                 "th {\n"
+                 " border-width: 1px;\n"
+                 " padding: 2px;\n"
+                 " border-style: dotted;\n"
+                 " border-color: gray;\n"
+                 " background-color: white;\n"
+                 " text-align: center;\n"
+                 "}\n"
+                 "td {\n"
+                 " border-width: 1px;\n"
+                 " padding: 2px;\n"
+                 " border-style: dotted;\n"
+                 " border-color: gray;\n"
+                 " background-color: white;\n"
+                 " text-align: center;\n"
+                 "}\n"
+                 "</style>\n</head>\n", r);
         ap_rputs("<body><h1>Load Balancer Manager for ", r);
         ap_rvputs(r, ap_get_server_name(r), "</h1>\n\n", NULL);
         ap_rvputs(r, "<dl><dt>Server Version: ",
                   ap_get_server_description(), "</dt>\n", NULL);
         ap_rvputs(r, "<dt>Server Built: ",
                   ap_get_server_built(), "\n</dt></dl>\n", NULL);
         balancer = (proxy_balancer *)conf->balancers->elts;
         for (i = 0; i < conf->balancers->nelts; i++) {
 
             ap_rputs("<hr />\n<h3>LoadBalancer Status for ", r);
-            ap_rvputs(r, balancer->name, "</h3>\n\n", NULL);
-            ap_rputs("\n\n<table border=\"0\" style=\"text-align: left;\"><tr>"
-                "<th>StickySession</th><th>Timeout</th><th>FailoverAttempts</th><th>Method</th>"
-                "</tr>\n<tr>", r);
-            if (balancer->sticky) {
-                if (strcmp(balancer->sticky, balancer->sticky_path)) {
-                    ap_rvputs(r, "<td>", balancer->sticky, " | ",
-                              balancer->sticky_path, NULL);
+            ap_rvputs(r, "<a href='", r->uri, "?b=",
+                      balancer->s->name + sizeof(BALANCER_PREFIX) - 1,
+                      "&nonce=", balancer->s->nonce,
+                      "'>", NULL);
+            ap_rvputs(r, balancer->s->name, "</a></h3>\n", NULL);
+            ap_rputs("\n\n<table><tr>"
+                "<th>MaxMembers</th><th>StickySession</th><th>DisableFailover</th><th>Timeout</th><th>FailoverAttempts</th><th>Method</th>"
+                "<th>Path</th><th>Active</th></tr>\n<tr>", r);
+            /* the below is a safe cast, since the number of slots total will
+             * never be more than max_workers, which is restricted to int */
+            ap_rprintf(r, "<td>%d [%d Used]</td>\n", balancer->max_workers,
+                       balancer->max_workers - (int)storage->num_free_slots(balancer->wslot));
+            if (*balancer->s->sticky) {
+                if (strcmp(balancer->s->sticky, balancer->s->sticky_path)) {
+                    ap_rvputs(r, "<td>", balancer->s->sticky, " | ",
+                              balancer->s->sticky_path, NULL);
                 }
                 else {
-                    ap_rvputs(r, "<td>", balancer->sticky, NULL);
+                    ap_rvputs(r, "<td>", balancer->s->sticky, NULL);
                 }
             }
             else {
-                ap_rputs("<td> - ", r);
+                ap_rputs("<td> (None) ", r);
             }
+            ap_rprintf(r, "<td>%s</td>\n",
+                       balancer->s->sticky_force ? "On" : "Off");
             ap_rprintf(r, "</td><td>%" APR_TIME_T_FMT "</td>",
-                apr_time_sec(balancer->timeout));
-            ap_rprintf(r, "<td>%d</td>\n", balancer->max_attempts);
+                apr_time_sec(balancer->s->timeout));
+            ap_rprintf(r, "<td>%d</td>\n", balancer->s->max_attempts);
+            ap_rprintf(r, "<td>%s</td>\n",
+                       balancer->s->lbpname);
+            ap_rputs("<td>", r);
+            if (balancer->s->vhost && *(balancer->s->vhost)) {
+                ap_rvputs(r, balancer->s->vhost, " -> ", NULL);
+            }
+            ap_rvputs(r, balancer->s->vpath, "</td>\n", NULL);
             ap_rprintf(r, "<td>%s</td>\n",
-                       balancer->lbmethod->name);
+                       !balancer->s->inactive ? "Yes" : "No");
             ap_rputs("</table>\n<br />", r);
-            ap_rputs("\n\n<table border=\"0\" style=\"text-align: left;\"><tr>"
+            ap_rputs("\n\n<table><tr>"
                 "<th>Worker URL</th>"
                 "<th>Route</th><th>RouteRedir</th>"
                 "<th>Factor</th><th>Set</th><th>Status</th>"
-                "<th>Elected</th><th>To</th><th>From</th>"
+                "<th>Elected</th><th>Busy</th><th>Load</th><th>To</th><th>From</th>"
                 "</tr>\n", r);
 
             workers = (proxy_worker **)balancer->workers->elts;
             for (n = 0; n < balancer->workers->nelts; n++) {
                 char fbuf[50];
                 worker = *workers;
-                ap_rvputs(r, "<tr>\n<td><a href=\"", r->uri, "?b=",
-                          balancer->name + sizeof("balancer://") - 1, "&w=",
-                          ap_escape_uri(r->pool, worker->name),
-                          "&nonce=", balancer_nonce, 
-                          "\">", NULL);
-                ap_rvputs(r, worker->name, "</a></td>", NULL);
+                ap_rvputs(r, "<tr>\n<td><a href='", r->uri, "?b=",
+                          balancer->s->name + sizeof(BALANCER_PREFIX) - 1, "&w=",
+                          ap_escape_uri(r->pool, worker->s->name),
+                          "&nonce=", balancer->s->nonce,
+                          "'>", NULL);
+                ap_rvputs(r, worker->s->name, "</a></td>", NULL);
                 ap_rvputs(r, "<td>", ap_escape_html(r->pool, worker->s->route),
                           NULL);
                 ap_rvputs(r, "</td><td>",
                           ap_escape_html(r->pool, worker->s->redirect), NULL);
                 ap_rprintf(r, "</td><td>%d</td>", worker->s->lbfactor);
                 ap_rprintf(r, "<td>%d</td><td>", worker->s->lbset);
-                if (worker->s->status & PROXY_WORKER_DISABLED)
-                   ap_rputs("Dis ", r);
-                if (worker->s->status & PROXY_WORKER_IN_ERROR)
-                   ap_rputs("Err ", r);
-                if (worker->s->status & PROXY_WORKER_STOPPED)
-                   ap_rputs("Stop ", r);
-                if (worker->s->status & PROXY_WORKER_HOT_STANDBY)
-                   ap_rputs("Stby ", r);
-                if (PROXY_WORKER_IS_USABLE(worker))
-                    ap_rputs("Ok", r);
-                if (!PROXY_WORKER_IS_INITIALIZED(worker))
-                    ap_rputs("-", r);
+                ap_rvputs(r, ap_proxy_parse_wstatus(r->pool, worker), NULL);
                 ap_rputs("</td>", r);
-                ap_rprintf(r, "<td>%" APR_SIZE_T_FMT "</td><td>", worker->s->elected);
+                ap_rprintf(r, "<td>%" APR_SIZE_T_FMT "</td>", worker->s->elected);
+                ap_rprintf(r, "<td>%" APR_SIZE_T_FMT "</td>", worker->s->busy);
+                ap_rprintf(r, "<td>%d</td><td>", worker->s->lbstatus);
                 ap_rputs(apr_strfsize(worker->s->transferred, fbuf), r);
                 ap_rputs("</td><td>", r);
                 ap_rputs(apr_strfsize(worker->s->read, fbuf), r);
                 ap_rputs("</td></tr>\n", r);
 
                 ++workers;
