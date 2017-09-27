                    ap_rprintf(r,
                               "          <httpd:keepalive>%s</httpd:keepalive>\n",
                               (worker->s->keepalive ? "On" : "Off"));
                }
                /* Begin proxy_worker_stat */
                ap_rputs("          <httpd:status>", r);
                ap_rputs(ap_proxy_parse_wstatus(r->pool, worker), r);
                ap_rputs("</httpd:status>\n", r);
                if ((worker->s->error_time > 0) && apr_rfc822_date(date, worker->s->error_time) == APR_SUCCESS) {
                    ap_rvputs(r, "          <httpd:error_time>", date,
                              "</httpd:error_time>\n", NULL);
                }
                ap_rprintf(r,
