static int balancer_handler(request_rec *r)
{
    void *sconf;
    proxy_server_conf *conf;
    proxy_balancer *balancer, *bsel = NULL;
    proxy_worker *worker, *wsel = NULL;
    proxy_worker **workers = NULL;
    apr_table_t *params;
    int i, n;
    int ok2change = 1;
    const char *name;
    const char *action;
    apr_status_t rv;

    /* is this for us? */
    if (strcmp(r->handler, "balancer-manager")) {
        return DECLINED;
    }

    r->allowed = 0
    | (AP_METHOD_BIT << M_GET)
    | (AP_METHOD_BIT << M_POST);
    if ((r->method_number != M_GET) && (r->method_number != M_POST)) {
        return DECLINED;
    }

    sconf = r->server->module_config;
    conf = (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);
    params = apr_table_make(r->pool, 10);

    balancer = (proxy_balancer *)conf->balancers->elts;
    for (i = 0; i < conf->balancers->nelts; i++, balancer++) {
        if ((rv = PROXY_THREAD_LOCK(balancer)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01189)
                          "%s: Lock failed for balancer_handler",
                          balancer->s->name);
        }
        ap_proxy_sync_balancer(balancer, r->server, conf);
        if ((rv = PROXY_THREAD_UNLOCK(balancer)) != APR_SUCCESS) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01190)
                          "%s: Unlock failed for balancer_handler",
                          balancer->s->name);
        }
    }

    if (r->args && (r->method_number == M_GET)) {
        const char *allowed[] = { "w", "b", "nonce", "xml", NULL };
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01191) "parsing r->args");

        push2table(r->args, params, allowed, r->pool);
    }
    if (r->method_number == M_POST) {
        apr_bucket_brigade *ib;
        apr_size_t len = 1024;
        char *buf = apr_pcalloc(r->pool, len+1);

        ib = apr_brigade_create(r->connection->pool, r->connection->bucket_alloc);
        rv = ap_get_brigade(r->input_filters, ib, AP_MODE_READBYTES,
                                APR_BLOCK_READ, len);
        if (rv != APR_SUCCESS) {
            return HTTP_INTERNAL_SERVER_ERROR;
        }
        apr_brigade_flatten(ib, buf, &len);
        buf[len] = '\0';
        push2table(buf, params, NULL, r->pool);
    }
    if ((name = apr_table_get(params, "b")))
        bsel = ap_proxy_get_balancer(r->pool, conf,
            apr_pstrcat(r->pool, BALANCER_PREFIX, name, NULL), 0);

    if ((name = apr_table_get(params, "w"))) {
        wsel = ap_proxy_get_worker(r->pool, bsel, conf, name);
    }


    /* Check that the supplied nonce matches this server's nonce;
     * otherwise ignore all parameters, to prevent a CSRF attack. */
    if (!bsel ||
        (*bsel->s->nonce &&
         (
          (name = apr_table_get(params, "nonce")) == NULL ||
          strcmp(bsel->s->nonce, name) != 0
         )
        )
       ) {
        apr_table_clear(params);
        ok2change = 0;
    }

    /* First set the params */
    if (wsel && ok2change) {
        const char *val;
        int was_usable = PROXY_WORKER_IS_USABLE(wsel);

        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01192) "settings worker params");

        if ((val = apr_table_get(params, "w_lf"))) {
            int ival = atoi(val);
            if (ival >= 1 && ival <= 100) {
                wsel->s->lbfactor = ival;
                if (bsel)
                    recalc_factors(bsel);
            }
        }
        if ((val = apr_table_get(params, "w_wr"))) {
            if (strlen(val) && strlen(val) < sizeof(wsel->s->route))
                strcpy(wsel->s->route, val);
            else
                *wsel->s->route = '\0';
        }
        if ((val = apr_table_get(params, "w_rr"))) {
            if (strlen(val) && strlen(val) < sizeof(wsel->s->redirect))
                strcpy(wsel->s->redirect, val);
            else
                *wsel->s->redirect = '\0';
        }
        if ((val = apr_table_get(params, "w_status_I"))) {
            ap_proxy_set_wstatus('I', atoi(val), wsel);
        }
        if ((val = apr_table_get(params, "w_status_N"))) {
            ap_proxy_set_wstatus('N', atoi(val), wsel);
        }
        if ((val = apr_table_get(params, "w_status_D"))) {
            ap_proxy_set_wstatus('D', atoi(val), wsel);
        }
        if ((val = apr_table_get(params, "w_status_H"))) {
            ap_proxy_set_wstatus('H', atoi(val), wsel);
        }
        if ((val = apr_table_get(params, "w_ls"))) {
            int ival = atoi(val);
            if (ival >= 0 && ival <= 99) {
                wsel->s->lbset = ival;
             }
        }
        /* if enabling, we need to reset all lb params */
        if (bsel && !was_usable && PROXY_WORKER_IS_USABLE(wsel)) {
            bsel->s->need_reset = 1;
        }

    }

    if (bsel && ok2change) {
        const char *val;
        int ival;
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01193)
                      "settings balancer params");
        if ((val = apr_table_get(params, "b_lbm"))) {
            if ((strlen(val) < (sizeof(bsel->s->lbpname)-1)) &&
                strcmp(val, bsel->s->lbpname)) {
                proxy_balancer_method *lbmethod;
                lbmethod = ap_lookup_provider(PROXY_LBMETHOD, val, "0");
                if (lbmethod) {
                    PROXY_STRNCPY(bsel->s->lbpname, val);
                    bsel->lbmethod = lbmethod;
                    bsel->s->wupdated = apr_time_now();
                    bsel->s->need_reset = 1;
                }
            }
        }
        if ((val = apr_table_get(params, "b_tmo"))) {
            ival = atoi(val);
            if (ival >= 0 && ival <= 7200) { /* 2 hrs enuff? */
                bsel->s->timeout = apr_time_from_sec(ival);
            }
        }
        if ((val = apr_table_get(params, "b_max"))) {
            ival = atoi(val);
            if (ival >= 0 && ival <= 99) {
                bsel->s->max_attempts = ival;
            }
        }
        if ((val = apr_table_get(params, "b_sforce"))) {
            ival = atoi(val);
            bsel->s->sticky_force = (ival != 0);
        }
        if ((val = apr_table_get(params, "b_ss")) && *val) {
            if (strlen(val) < (sizeof(bsel->s->sticky_path)-1)) {
                if (*val == '-' && *(val+1) == '\0')
                    *bsel->s->sticky_path = *bsel->s->sticky = '\0';
                else {
                    char *path;
                    PROXY_STRNCPY(bsel->s->sticky_path, val);
                    PROXY_STRNCPY(bsel->s->sticky, val);

                    if ((path = strchr((char *)bsel->s->sticky, '|'))) {
                        *path++ = '\0';
                        PROXY_STRNCPY(bsel->s->sticky_path, path);
                    }
                }
            }
        }
        if ((val = apr_table_get(params, "b_wyes")) &&
            (*val == '1' && *(val+1) == '\0') &&
            (val = apr_table_get(params, "b_nwrkr"))) {
            char *ret;
            proxy_worker *nworker;
            nworker = ap_proxy_get_worker(r->pool, bsel, conf, val);
            if (!nworker && storage->num_free_slots(bsel->wslot)) {
                if ((rv = PROXY_GLOBAL_LOCK(bsel)) != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01194)
                                  "%s: Lock failed for adding worker",
                                  bsel->s->name);
                }
                ret = ap_proxy_define_worker(conf->pool, &nworker, bsel, conf, val, 0);
                if (!ret) {
                    unsigned int index;
                    proxy_worker_shared *shm;
                    PROXY_COPY_CONF_PARAMS(nworker, conf);
                    if ((rv = storage->grab(bsel->wslot, &index)) != APR_SUCCESS) {
                        ap_log_rerror(APLOG_MARK, APLOG_EMERG, rv, r, APLOGNO(01195)
                                      "worker slotmem_grab failed");
                        if ((rv = PROXY_GLOBAL_UNLOCK(bsel)) != APR_SUCCESS) {
                            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01196)
                                          "%s: Unlock failed for adding worker",
                                          bsel->s->name);
                        }
                        return HTTP_BAD_REQUEST;
                    }
                    if ((rv = storage->dptr(bsel->wslot, index, (void *)&shm)) != APR_SUCCESS) {
                        ap_log_rerror(APLOG_MARK, APLOG_EMERG, rv, r, APLOGNO(01197)
                                      "worker slotmem_dptr failed");
                        if ((rv = PROXY_GLOBAL_UNLOCK(bsel)) != APR_SUCCESS) {
                            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01198)
                                          "%s: Unlock failed for adding worker",
                                          bsel->s->name);
                        }
                        return HTTP_BAD_REQUEST;
                    }
                    if ((rv = ap_proxy_share_worker(nworker, shm, index)) != APR_SUCCESS) {
                        ap_log_rerror(APLOG_MARK, APLOG_EMERG, rv, r, APLOGNO(01199)
                                      "Cannot share worker");
                        if ((rv = PROXY_GLOBAL_UNLOCK(bsel)) != APR_SUCCESS) {
                            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01200)
                                          "%s: Unlock failed for adding worker",
                                          bsel->s->name);
                        }
                        return HTTP_BAD_REQUEST;
                    }
                    if ((rv = ap_proxy_initialize_worker(nworker, r->server, conf->pool)) != APR_SUCCESS) {
                        ap_log_rerror(APLOG_MARK, APLOG_EMERG, rv, r, APLOGNO(01201)
                                      "Cannot init worker");
                        if ((rv = PROXY_GLOBAL_UNLOCK(bsel)) != APR_SUCCESS) {
                            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01202)
                                          "%s: Unlock failed for adding worker",
                                          bsel->s->name);
                        }
                        return HTTP_BAD_REQUEST;
                    }
                    /* sync all timestamps */
                    bsel->wupdated = bsel->s->wupdated = nworker->s->updated = apr_time_now();
                    /* by default, all new workers are disabled */
                    ap_proxy_set_wstatus('D', 1, nworker);
                }
                if ((rv = PROXY_GLOBAL_UNLOCK(bsel)) != APR_SUCCESS) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r, APLOGNO(01203)
                                  "%s: Unlock failed for adding worker",
                                  bsel->s->name);
                }
            }

        }

    }

    action = ap_construct_url(r->pool, r->uri, r);
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(01204) "genning page");

    if (apr_table_get(params, "xml")) {
        char date[APR_RFC822_DATE_LEN];
        ap_set_content_type(r, "text/xml");
        ap_rputs("<?xml version='1.0' encoding='UTF-8' ?>\n", r);
        ap_rputs("<httpd:manager xmlns:httpd='http://httpd.apache.org'>\n", r);
        ap_rputs("  <httpd:balancers>\n", r);
        balancer = (proxy_balancer *)conf->balancers->elts;
        for (i = 0; i < conf->balancers->nelts; i++) {
            ap_rputs("    <httpd:balancer>\n", r);
            /* Start proxy_balancer */
            ap_rvputs(r, "      <httpd:name>", balancer->s->name, "</httpd:name>\n", NULL);
            if (balancer->s->sticky) {
                ap_rvputs(r, "      <httpd:stickysession>", balancer->s->sticky,
                          "</httpd:stickysession>\n", NULL);
                ap_rprintf(r,
                           "      <httpd:nofailover>%s</httpd:nofailover>\n",
                           (balancer->s->sticky_force ? "On" : "Off"));
            }
            ap_rprintf(r,
                       "      <httpd:timeout>%" APR_TIME_T_FMT "</httpd:timeout>",
                       apr_time_sec(balancer->s->timeout));
            if (balancer->s->max_attempts_set) {
                ap_rprintf(r,
                           "      <httpd:maxattempts>%d</httpd:maxattempts>\n",
                           balancer->s->max_attempts);
            }
            ap_rvputs(r, "      <httpd:lbmethod>", balancer->lbmethod->name,
                      "</httpd:lbmethod>\n", NULL);
            if (balancer->s->sticky) {
                ap_rprintf(r,
                           "      <httpd:scolonpathdelim>%s</httpd:scolonpathdelim>\n",
                           (balancer->s->scolonsep ? "On" : "Off"));
            }
            /* End proxy_balancer */
            ap_rputs("      <httpd:workers>\n", r);
            workers = (proxy_worker **)balancer->workers->elts;
            for (n = 0; n < balancer->workers->nelts; n++) {
                worker = *workers;
                /* Start proxy_worker */
                ap_rputs("        <httpd:worker>\n", r);
                ap_rvputs(r, "          <httpd:name>", worker->s->name,
                          "</httpd:name>\n", NULL);
                ap_rvputs(r, "          <httpd:scheme>", worker->s->scheme,
                          "</httpd:scheme>\n", NULL);
                ap_rvputs(r, "          <httpd:hostname>", worker->s->hostname,
                          "</httpd:hostname>\n", NULL);
                ap_rprintf(r, "          <httpd:loadfactor>%d</httpd:loadfactor>\n",
                          worker->s->lbfactor);
                ap_rprintf(r,
                           "          <httpd:port>%d</httpd:port>\n",
                           worker->s->port);
                ap_rprintf(r, "          <httpd:min>%d</httpd:min>\n",
                           worker->s->min);
                ap_rprintf(r, "          <httpd:smax>%d</httpd:smax>\n",
                           worker->s->smax);
                ap_rprintf(r, "          <httpd:max>%d</httpd:max>\n",
                           worker->s->hmax);
                ap_rprintf(r,
                           "          <httpd:ttl>%" APR_TIME_T_FMT "</httpd:ttl>\n",
                           apr_time_sec(worker->s->ttl));
                if (worker->s->timeout_set) {
                    ap_rprintf(r,
                               "          <httpd:timeout>%" APR_TIME_T_FMT "</httpd:timeout>\n",
                               apr_time_sec(worker->s->timeout));
                }
                if (worker->s->acquire_set) {
                    ap_rprintf(r,
                               "          <httpd:acquire>%" APR_TIME_T_FMT "</httpd:acquire>\n",
                               apr_time_msec(worker->s->acquire));
                }
                if (worker->s->recv_buffer_size_set) {
                    ap_rprintf(r,
                               "          <httpd:recv_buffer_size>%" APR_SIZE_T_FMT "</httpd:recv_buffer_size>\n",
                               worker->s->recv_buffer_size);
                }
                if (worker->s->io_buffer_size_set) {
                    ap_rprintf(r,
                               "          <httpd:io_buffer_size>%" APR_SIZE_T_FMT "</httpd:io_buffer_size>\n",
                               worker->s->io_buffer_size);
                }
                if (worker->s->keepalive_set) {
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
                           "          <httpd:retries>%d</httpd:retries>\n",
                           worker->s->retries);
                ap_rprintf(r,
                           "          <httpd:lbstatus>%d</httpd:lbstatus>\n",
                           worker->s->lbstatus);
                ap_rprintf(r,
                           "          <httpd:loadfactor>%d</httpd:loadfactor>\n",
                           worker->s->lbfactor);
                ap_rprintf(r,
                           "          <httpd:transferred>%" APR_OFF_T_FMT "</httpd:transferred>\n",
                           worker->s->transferred);
                ap_rprintf(r,
                           "          <httpd:read>%" APR_OFF_T_FMT "</httpd:read>\n",
                           worker->s->read);
                ap_rprintf(r,
                           "          <httpd:elected>%" APR_SIZE_T_FMT "</httpd:elected>\n",
                           worker->s->elected);
                ap_rvputs(r, "          <httpd:route>",
                          ap_escape_html(r->pool, worker->s->route),
                          "</httpd:route>\n", NULL);
                ap_rvputs(r, "          <httpd:redirect>",
                          ap_escape_html(r->pool, worker->s->redirect),
                          "</httpd:redirect>\n", NULL);
                ap_rprintf(r,
                           "          <httpd:busy>%" APR_SIZE_T_FMT "</httpd:busy>\n",
                           worker->s->busy);
                ap_rprintf(r, "          <httpd:lbset>%d</httpd:lbset>\n",
                           worker->s->lbset);
                /* End proxy_worker_stat */
                if (!strcasecmp(worker->s->scheme, "ajp")) {
                    ap_rputs("          <httpd:flushpackets>", r);
                    switch (worker->s->flush_packets) {
                        case flush_off:
                            ap_rputs("Off", r);
                            break;
                        case flush_on:
                            ap_rputs("On", r);
                            break;
                        case flush_auto:
                            ap_rputs("Auto", r);
                            break;
                    }
                    ap_rputs("</httpd:flushpackets>\n", r);
                    if (worker->s->flush_packets == flush_auto) {
                        ap_rprintf(r,
                                   "          <httpd:flushwait>%d</httpd:flushwait>\n",
                                   worker->s->flush_wait);
                    }
                    if (worker->s->ping_timeout_set) {
                        ap_rprintf(r,
                                   "          <httpd:ping>%" APR_TIME_T_FMT "</httpd:ping>",
                                   apr_time_msec(worker->s->ping_timeout));
                    }
                }
                if (worker->s->disablereuse_set) {
                    ap_rprintf(r,
                               "      <httpd:disablereuse>%s</httpd:disablereuse>\n",
                               (worker->s->disablereuse ? "On" : "Off"));
                }
                if (worker->s->conn_timeout_set) {
                    ap_rprintf(r,
                               "          <httpd:connectiontimeout>%" APR_TIME_T_FMT "</httpd:connectiontimeout>\n",
                               apr_time_msec(worker->s->conn_timeout));
                }
                if (worker->s->retry_set) {
                    ap_rprintf(r,
                               "          <httpd:retry>%" APR_TIME_T_FMT "</httpd:retry>\n",
                               apr_time_sec(worker->s->retry));
                }
                ap_rputs("        </httpd:worker>\n", r);
                ++workers;
            }
            ap_rputs("      </httpd:workers>\n", r);
            ap_rputs("    </httpd:balancer>\n", r);
            ++balancer;
        }
        ap_rputs("  </httpd:balancers>\n", r);
        ap_rputs("</httpd:manager>", r);
    }
    else {
        ap_set_content_type(r, "text/html; charset=ISO-8859-1");
        ap_rputs(DOCTYPE_HTML_3_2
                 "<html><head><title>Balancer Manager</title>\n", r);
        ap_rputs("<style type='text/css'>\n"
                 "table {\n"
                 " border-width: 1px;\n"
                 " border-spacing: 3px;\n"
                 " border-style: solid;\n"
                 " border-color: gray;\n"
                 " border-collapse: collapse;\n"
                 " background-color: white;\n"
                 " text-align: center;\n"
                 "}\n"
                 "th {\n"
                 " border-width: 1px;\n"
                 " padding: 2px;\n"
                 " border-style: dotted;\n"
                 " border-color: gray;\n"
                 " background-color: white;\n"
                 " text-align: center;\n"
                 "}\n"
                 "td {\n"
                 " border-width: 1px;\n"
                 " padding: 2px;\n"
                 " border-style: dotted;\n"
                 " border-color: gray;\n"
                 " background-color: white;\n"
                 " text-align: center;\n"
                 "}\n"
                 "</style>\n</head>\n", r);
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
                      "&nonce=", balancer->s->nonce,
                      "\">", NULL);
            ap_rvputs(r, balancer->s->name, "</a> [",balancer->s->sname, "]</h3>\n", NULL);
            ap_rputs("\n\n<table><tr>"
                "<th>MaxMembers</th><th>StickySession</th><th>DisableFailover</th><th>Timeout</th><th>FailoverAttempts</th><th>Method</th>"
                "<th>Path</th><th>Active</th></tr>\n<tr>", r);
            /* the below is a safe cast, since the number of slots total will
             * never be more than max_workers, which is restricted to int */
            ap_rprintf(r, "<td>%d [%d Used]</td>\n", balancer->max_workers,
                       balancer->max_workers - (int)storage->num_free_slots(balancer->wslot));
            if (*balancer->s->sticky) {
                if (strcmp(balancer->s->sticky, balancer->s->sticky_path)) {
                    ap_rvputs(r, "<td>", balancer->s->sticky, " | ",
                              balancer->s->sticky_path, NULL);
                }
                else {
                    ap_rvputs(r, "<td>", balancer->s->sticky, NULL);
                }
            }
            else {
                ap_rputs("<td> (None) ", r);
            }
            ap_rprintf(r, "<td>%s</td>\n",
                       balancer->s->sticky_force ? "On" : "Off");
            ap_rprintf(r, "</td><td>%" APR_TIME_T_FMT "</td>",
                apr_time_sec(balancer->s->timeout));
            ap_rprintf(r, "<td>%d</td>\n", balancer->s->max_attempts);
            ap_rprintf(r, "<td>%s</td>\n",
                       balancer->s->lbpname);
            ap_rputs("<td>", r);
            if (balancer->s->vhost && *(balancer->s->vhost)) {
                ap_rvputs(r, balancer->s->vhost, " -> ", NULL);
            }
            ap_rvputs(r, balancer->s->vpath, "</td>\n", NULL);
            ap_rprintf(r, "<td>%s</td>\n",
                       !balancer->s->inactive ? "Yes" : "No");
            ap_rputs("</table>\n<br />", r);
            ap_rputs("\n\n<table><tr>"
                "<th>Worker URL</th>"
                "<th>Route</th><th>RouteRedir</th>"
                "<th>Factor</th><th>Set</th><th>Status</th>"
                "<th>Elected</th><th>Busy</th><th>Load</th><th>To</th><th>From</th>"
                "</tr>\n", r);

            workers = (proxy_worker **)balancer->workers->elts;
            for (n = 0; n < balancer->workers->nelts; n++) {
                char fbuf[50];
                worker = *workers;
                ap_rvputs(r, "<tr>\n<td><a href=\"",
                          ap_escape_uri(r->pool, r->uri), "?b=",
                          balancer->s->name + sizeof(BALANCER_PREFIX) - 1, "&w=",
                          ap_escape_uri(r->pool, worker->s->name),
                          "&nonce=", balancer->s->nonce,
                          "\">", NULL);
                ap_rvputs(r, worker->s->name, "</a></td>", NULL);
                ap_rvputs(r, "<td>", ap_escape_html(r->pool, worker->s->route),
                          NULL);
                ap_rvputs(r, "</td><td>",
                          ap_escape_html(r->pool, worker->s->redirect), NULL);
                ap_rprintf(r, "</td><td>%d</td>", worker->s->lbfactor);
                ap_rprintf(r, "<td>%d</td><td>", worker->s->lbset);
                ap_rvputs(r, ap_proxy_parse_wstatus(r->pool, worker), NULL);
                ap_rputs("</td>", r);
                ap_rprintf(r, "<td>%" APR_SIZE_T_FMT "</td>", worker->s->elected);
                ap_rprintf(r, "<td>%" APR_SIZE_T_FMT "</td>", worker->s->busy);
                ap_rprintf(r, "<td>%d</td><td>", worker->s->lbstatus);
                ap_rputs(apr_strfsize(worker->s->transferred, fbuf), r);
                ap_rputs("</td><td>", r);
                ap_rputs(apr_strfsize(worker->s->read, fbuf), r);
                ap_rputs("</td></tr>\n", r);

                ++workers;
            }
            ap_rputs("</table>\n", r);
            ++balancer;
        }
        ap_rputs("<hr />\n", r);
        if (wsel && bsel) {
            ap_rputs("<h3>Edit worker settings for ", r);
            ap_rvputs(r, wsel->s->name, "</h3>\n", NULL);
            ap_rputs("<form method=\"POST\" enctype=\"application/x-www-form-urlencoded\" action=\"", r);
            ap_rvputs(r, ap_escape_uri(r->pool, action), "\">\n", NULL);
            ap_rputs("<dl>\n<table><tr><td>Load factor:</td><td><input name='w_lf' id='w_lf' type=text ", r);
            ap_rprintf(r, "value='%d'></td></tr>\n", wsel->s->lbfactor);
            ap_rputs("<tr><td>LB Set:</td><td><input name='w_ls' id='w_ls' type=text ", r);
            ap_rprintf(r, "value='%d'></td></tr>\n", wsel->s->lbset);
            ap_rputs("<tr><td>Route:</td><td><input name='w_wr' id='w_wr' type=text ", r);
            ap_rvputs(r, "value=\"", ap_escape_html(r->pool, wsel->s->route),
                      NULL);
            ap_rputs("\"></td></tr>\n", r);
            ap_rputs("<tr><td>Route Redirect:</td><td><input name='w_rr' id='w_rr' type=text ", r);
            ap_rvputs(r, "value=\"", ap_escape_html(r->pool, wsel->s->redirect),
                      NULL);
            ap_rputs("\"></td></tr>\n", r);
            ap_rputs("<tr><td>Status:</td>", r);
            ap_rputs("<td><table><tr>"
                     "<th>Ignore Errors</th>"
                     "<th>Draining Mode</th>"
                     "<th>Disabled</th>"
                     "<th>Hot Standby</th></tr>\n<tr>", r);
            create_radio("w_status_I", (PROXY_WORKER_IGNORE_ERRORS & wsel->s->status), r);
            create_radio("w_status_N", (PROXY_WORKER_DRAIN & wsel->s->status), r);
            create_radio("w_status_D", (PROXY_WORKER_DISABLED & wsel->s->status), r);
            create_radio("w_status_H", (PROXY_WORKER_HOT_STANDBY & wsel->s->status), r);
            ap_rputs("</tr></table>\n", r);
            ap_rputs("<tr><td colspan=2><input type=submit value='Submit'></td></tr>\n", r);
            ap_rvputs(r, "</table>\n<input type=hidden name='w' id='w' ",  NULL);
            ap_rvputs(r, "value='", ap_escape_uri(r->pool, wsel->s->name), "'>\n", NULL);
            ap_rvputs(r, "<input type=hidden name='b' id='b' ", NULL);
            ap_rvputs(r, "value='", bsel->s->name + sizeof(BALANCER_PREFIX) - 1,
                      "'>\n", NULL);
            ap_rvputs(r, "<input type=hidden name='nonce' id='nonce' value='",
                      bsel->s->nonce, "'>\n", NULL);
            ap_rputs("</form>\n", r);
            ap_rputs("<hr />\n", r);
        } else if (bsel) {
            const apr_array_header_t *provs;
            const ap_list_provider_names_t *pname;
            int i;
            ap_rputs("<h3>Edit balancer settings for ", r);
            ap_rvputs(r, bsel->s->name, "</h3>\n", NULL);
            ap_rputs("<form method='POST' enctype='application/x-www-form-urlencoded' action='", r);
            ap_rvputs(r, action, "'>\n", NULL);
            ap_rputs("<dl>\n<table>\n", r);
            provs = ap_list_provider_names(r->pool, PROXY_LBMETHOD, "0");
            if (provs) {
                ap_rputs("<tr><td>LBmethod:</td>", r);
                ap_rputs("<td>\n<select name='b_lbm' id='b_lbm'>", r);
                pname = (ap_list_provider_names_t *)provs->elts;
                for (i = 0; i < provs->nelts; i++, pname++) {
                    ap_rvputs(r,"<option value='", pname->provider_name, "'", NULL);
                    if (strcmp(pname->provider_name, bsel->s->lbpname) == 0)
                        ap_rputs(" selected ", r);
                    ap_rvputs(r, ">", pname->provider_name, "\n", NULL);
                }
                ap_rputs("</select>\n</td></tr>\n", r);
            }
            ap_rputs("<tr><td>Timeout:</td><td><input name='b_tmo' id='b_tmo' type=text ", r);
            ap_rprintf(r, "value='%" APR_TIME_T_FMT "'></td></tr>\n", apr_time_sec(bsel->s->timeout));
            ap_rputs("<tr><td>Failover Attempts:</td><td><input name='b_max' id='b_max' type=text ", r);
            ap_rprintf(r, "value='%d'></td></tr>\n", bsel->s->max_attempts);
            ap_rputs("<tr><td>Disable Failover:</td>", r);
            create_radio("b_sforce", bsel->s->sticky_force, r);
            ap_rputs("<tr><td>Sticky Session:</td><td><input name='b_ss' id='b_ss' size=64 type=text ", r);
            if (strcmp(bsel->s->sticky, bsel->s->sticky_path)) {
                ap_rvputs(r, "value ='", bsel->s->sticky, " | ",
                          bsel->s->sticky_path, NULL);
            }
            else {
                ap_rvputs(r, "value ='", bsel->s->sticky, NULL);
            }
            ap_rputs("'>&nbsp;&nbsp;&nbsp;&nbsp;(Use '-' to delete)</td></tr>\n", r);
            if (storage->num_free_slots(bsel->wslot) != 0) {
                ap_rputs("<tr><td>Add New Worker:</td><td><input name='b_nwrkr' id='b_nwrkr' size=32 type=text>"
                         "&nbsp;&nbsp;&nbsp;&nbsp;Are you sure? <input name='b_wyes' id='b_wyes' type=checkbox value='1'>"
                         "</td></tr>", r);
            }
            ap_rputs("<tr><td colspan=2><input type=submit value='Submit'></td></tr>\n", r);
            ap_rvputs(r, "</table>\n<input type=hidden name='b' id='b' ", NULL);
            ap_rvputs(r, "value='", bsel->s->name + sizeof(BALANCER_PREFIX) - 1,
                      "'>\n", NULL);
            ap_rvputs(r, "<input type=hidden name='nonce' id='nonce' value='",
                      bsel->s->nonce, "'>\n", NULL);
            ap_rputs("</form>\n", r);
            ap_rputs("<hr />\n", r);
        }
        ap_rputs(ap_psignature("",r), r);
        ap_rputs("</body></html>\n", r);
        ap_rflush(r);
    }
    return DONE;
}