     }
 
     action = ap_construct_url(r->pool, r->uri, r);
     ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01204) "genning page");
 
     if (apr_table_get(params, "xml")) {
+        char date[APR_RFC822_DATE_LEN];
         ap_set_content_type(r, "text/xml");
         ap_rputs("<?xml version='1.0' encoding='UTF-8' ?>\n", r);
         ap_rputs("<httpd:manager xmlns:httpd='http://httpd.apache.org'>\n", r);
         ap_rputs("  <httpd:balancers>\n", r);
         balancer = (proxy_balancer *)conf->balancers->elts;
         for (i = 0; i < conf->balancers->nelts; i++) {
             ap_rputs("    <httpd:balancer>\n", r);
+            /* Start proxy_balancer */
             ap_rvputs(r, "      <httpd:name>", balancer->s->name, "</httpd:name>\n", NULL);
+            if (balancer->s->sticky) {
+                ap_rvputs(r, "      <httpd:stickysession>", balancer->s->sticky,
+                          "</httpd:stickysession>\n", NULL);
+                ap_rprintf(r,
+                           "      <httpd:nofailover>%s</httpd:nofailover>\n",
+                           (balancer->s->sticky_force ? "On" : "Off"));
+            }
+            ap_rprintf(r,
+                       "      <httpd:timeout>%" APR_TIME_T_FMT "</httpd:timeout>",
+                       apr_time_sec(balancer->s->timeout));
+            if (balancer->s->max_attempts_set) {
+                ap_rprintf(r,
+                           "      <httpd:maxattempts>%d</httpd:maxattempts>\n",
+                           balancer->s->max_attempts);
+            }
+            ap_rvputs(r, "      <httpd:lbmethod>", balancer->lbmethod->name,
+                      "</httpd:lbmethod>\n", NULL);
+            if (balancer->s->sticky) {
+                ap_rprintf(r,
+                           "      <httpd:scolonpathdelim>%s</httpd:scolonpathdelim>\n",
+                           (balancer->s->scolonsep ? "On" : "Off"));
+            }
+            /* End proxy_balancer */
             ap_rputs("      <httpd:workers>\n", r);
             workers = (proxy_worker **)balancer->workers->elts;
             for (n = 0; n < balancer->workers->nelts; n++) {
                 worker = *workers;
+                /* Start proxy_worker */
                 ap_rputs("        <httpd:worker>\n", r);
+                ap_rvputs(r, "          <httpd:name>", worker->s->name,
+                          "</httpd:name>\n", NULL);
                 ap_rvputs(r, "          <httpd:scheme>", worker->s->scheme,
                           "</httpd:scheme>\n", NULL);
                 ap_rvputs(r, "          <httpd:hostname>", worker->s->hostname,
                           "</httpd:hostname>\n", NULL);
                 ap_rprintf(r, "          <httpd:loadfactor>%d</httpd:loadfactor>\n",
                           worker->s->lbfactor);
+                ap_rprintf(r,
+                           "          <httpd:port>%d</httpd:port>\n",
+                           worker->s->port);
+                ap_rprintf(r, "          <httpd:min>%d</httpd:min>\n",
+                           worker->s->min);
+                ap_rprintf(r, "          <httpd:smax>%d</httpd:smax>\n",
+                           worker->s->smax);
+                ap_rprintf(r, "          <httpd:max>%d</httpd:max>\n",
+                           worker->s->hmax);
+                ap_rprintf(r,
+                           "          <httpd:ttl>%" APR_TIME_T_FMT "</httpd:ttl>\n",
+                           apr_time_sec(worker->s->ttl));
+                if (worker->s->timeout_set) {
+                    ap_rprintf(r,
+                               "          <httpd:timeout>%" APR_TIME_T_FMT "</httpd:timeout>\n",
+                               apr_time_sec(worker->s->timeout));
+                }
+                if (worker->s->acquire_set) {
+                    ap_rprintf(r,
+                               "          <httpd:acquire>%" APR_TIME_T_FMT "</httpd:acquire>\n",
+                               apr_time_msec(worker->s->acquire));
+                }
+                if (worker->s->recv_buffer_size_set) {
+                    ap_rprintf(r,
+                               "          <httpd:recv_buffer_size>%" APR_SIZE_T_FMT "</httpd:recv_buffer_size>\n",
+                               worker->s->recv_buffer_size);
+                }
+                if (worker->s->io_buffer_size_set) {
+                    ap_rprintf(r,
+                               "          <httpd:io_buffer_size>%" APR_SIZE_T_FMT "</httpd:io_buffer_size>\n",
+                               worker->s->io_buffer_size);
+                }
+                if (worker->s->keepalive_set) {
+                    ap_rprintf(r,
+                               "          <httpd:keepalive>%s</httpd:keepalive>\n",
+                               (worker->s->keepalive ? "On" : "Off"));
+                }
+                /* Begin proxy_worker_stat */
+                ap_rputs("          <httpd:status>", r);
+                if (worker->s->status & PROXY_WORKER_DISABLED)
+                    ap_rputs("Disabled", r);
+                else if (worker->s->status & PROXY_WORKER_IN_ERROR)
+                    ap_rputs("Error", r);
+                else if (worker->s->status & PROXY_WORKER_STOPPED)
+                    ap_rputs("Stopped", r);
+                else if (worker->s->status & PROXY_WORKER_HOT_STANDBY)
+                    ap_rputs("Standby", r);
+                else if (PROXY_WORKER_IS_USABLE(worker))
+                    ap_rputs("OK", r);
+                else if (!PROXY_WORKER_IS_INITIALIZED(worker))
+                    ap_rputs("Uninitialized", r);
+                ap_rputs("</httpd:status>\n", r);
+                if ((worker->s->error_time > 0) && apr_rfc822_date(date, worker->s->error_time) == APR_SUCCESS) {
+                    ap_rvputs(r, "          <httpd:error_time>", date,
+                              "</httpd:error_time>\n", NULL);
+                }
+                ap_rprintf(r,
+                           "          <httpd:retries>%d</httpd:retries>\n",
+                           worker->s->retries);
+                ap_rprintf(r,
+                           "          <httpd:lbstatus>%d</httpd:lbstatus>\n",
+                           worker->s->lbstatus);
+                ap_rprintf(r,
+                           "          <httpd:loadfactor>%d</httpd:loadfactor>\n",
+                           worker->s->lbfactor);
+                ap_rprintf(r,
+                           "          <httpd:transferred>%" APR_OFF_T_FMT "</httpd:transferred>\n",
+                           worker->s->transferred);
+                ap_rprintf(r,
+                           "          <httpd:read>%" APR_OFF_T_FMT "</httpd:read>\n",
+                           worker->s->read);
+                ap_rprintf(r,
+                           "          <httpd:elected>%" APR_SIZE_T_FMT "</httpd:elected>\n",
+                           worker->s->elected);
+                ap_rvputs(r, "          <httpd:route>",
+                          ap_escape_html(r->pool, worker->s->route),
+                          "</httpd:route>\n", NULL);
+                ap_rvputs(r, "          <httpd:redirect>",
+                          ap_escape_html(r->pool, worker->s->redirect),
+                          "</httpd:redirect>\n", NULL);
+                ap_rprintf(r,
+                           "          <httpd:busy>%" APR_SIZE_T_FMT "</httpd:busy>\n",
+                           worker->s->busy);
+                ap_rprintf(r, "          <httpd:lbset>%d</httpd:lbset>\n",
+                           worker->s->lbset);
+                /* End proxy_worker_stat */
+                if (!strcasecmp(worker->s->scheme, "ajp")) {
+                    ap_rputs("          <httpd:flushpackets>", r);
+                    switch (worker->s->flush_packets) {
+                        case flush_off:
+                            ap_rputs("Off", r);
+                            break;
+                        case flush_on:
+                            ap_rputs("On", r);
+                            break;
+                        case flush_auto:
+                            ap_rputs("Auto", r);
+                            break;
+                    }
+                    ap_rputs("</httpd:flushpackets>\n", r);
+                    if (worker->s->flush_packets == flush_auto) {
+                        ap_rprintf(r,
+                                   "          <httpd:flushwait>%d</httpd:flushwait>\n",
+                                   worker->s->flush_wait);
+                    }
+                    if (worker->s->ping_timeout_set) {
+                        ap_rprintf(r,
+                                   "          <httpd:ping>%" APR_TIME_T_FMT "</httpd:ping>",
+                                   apr_time_msec(worker->s->ping_timeout));
+                    }
+                }
+                if (worker->s->disablereuse_set) {
+                    ap_rprintf(r,
+                               "      <httpd:disablereuse>%s</httpd:disablereuse>\n",
+                               (worker->s->disablereuse ? "On" : "Off"));
+                }
+                if (worker->s->conn_timeout_set) {
+                    ap_rprintf(r,
+                               "          <httpd:connectiontimeout>%" APR_TIME_T_FMT "</httpd:connectiontimeout>\n",
+                               apr_time_msec(worker->s->conn_timeout));
+                }
+                if (worker->s->retry_set) {
+                    ap_rprintf(r,
+                               "          <httpd:retry>%" APR_TIME_T_FMT "</httpd:retry>\n",
+                               apr_time_sec(worker->s->retry));
+                }
                 ap_rputs("        </httpd:worker>\n", r);
                 ++workers;
             }
             ap_rputs("      </httpd:workers>\n", r);
             ap_rputs("    </httpd:balancer>\n", r);
             ++balancer;
