                    ap_rprintf(r,
                               "          <httpd:keepalive>%s</httpd:keepalive>\n",
                               (worker->s->keepalive ? "On" : "Off"));
                }
                /* Begin proxy_worker_stat */
                ap_rputs("          <httpd:status>", r);
                if (worker->s->status & PROXY_WORKER_DISABLED)
                    ap_rputs("Disabled", r);
                else if (worker->s->status & PROXY_WORKER_IN_ERROR)
                    ap_rputs("Error", r);
                else if (worker->s->status & PROXY_WORKER_STOPPED)
                    ap_rputs("Stopped", r);
                else if (worker->s->status & PROXY_WORKER_HOT_STANDBY)
                    ap_rputs("Standby", r);
                else if (PROXY_WORKER_IS_USABLE(worker))
                    ap_rputs("OK", r);
                else if (!PROXY_WORKER_IS_INITIALIZED(worker))
                    ap_rputs("Uninitialized", r);
                ap_rputs("</httpd:status>\n", r);
                if ((worker->s->error_time > 0) && apr_rfc822_date(date, worker->s->error_time) == APR_SUCCESS) {
                    ap_rvputs(r, "          <httpd:error_time>", date,
                              "</httpd:error_time>\n", NULL);
                }
                ap_rprintf(r,
