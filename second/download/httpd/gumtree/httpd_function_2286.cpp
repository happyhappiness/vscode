static int balancer_handler(request_rec *r)
{
    void *sconf = r->server->module_config;
    proxy_server_conf *conf = (proxy_server_conf *)
        ap_get_module_config(sconf, &proxy_module);
    proxy_balancer *balancer, *bsel = NULL;
    proxy_worker *worker, *wsel = NULL;
    apr_table_t *params = apr_table_make(r->pool, 10);
    int access_status;
    int i, n;
    const char *name;

    /* is this for us? */
    if (strcmp(r->handler, "balancer-manager"))
        return DECLINED;
    r->allowed = (AP_METHOD_BIT << M_GET);
    if (r->method_number != M_GET)
        return DECLINED;

    if (r->args) {
        char *args = apr_pstrdup(r->pool, r->args);
        char *tok, *val;
        while (args && *args) {
            if ((val = ap_strchr(args, '='))) {
                *val++ = '\0';
                if ((tok = ap_strchr(val, '&')))
                    *tok++ = '\0';
                /*
                 * Special case: workers are allowed path information
                 */
                if ((access_status = ap_unescape_url(val)) != OK)
                    if (strcmp(args, "w") || (access_status !=  HTTP_NOT_FOUND))
                        return access_status;
                apr_table_setn(params, args, val);
                args = tok;
            }
            else
                return HTTP_BAD_REQUEST;
        }
    }
    if ((name = apr_table_get(params, "b")))
        bsel = ap_proxy_get_balancer(r->pool, conf,
            apr_pstrcat(r->pool, "balancer://", name, NULL));
    if ((name = apr_table_get(params, "w"))) {
        proxy_worker *ws;

        ws = ap_proxy_get_worker(r->pool, conf, name);
        if (ws) {
            worker = (proxy_worker *)bsel->workers->elts;
            for (n = 0; n < bsel->workers->nelts; n++) {
                if (strcasecmp(worker->name, ws->name) == 0) {
                    wsel = worker;
                    break;
                }
                ++worker;
            }
        }
    }
    /* First set the params */
    if (bsel) {
        const char *val;
        if ((val = apr_table_get(params, "ss"))) {
            if (strlen(val))
                bsel->sticky = apr_pstrdup(conf->pool, val);
            else
                bsel->sticky = NULL;
        }
        if ((val = apr_table_get(params, "tm"))) {
            int ival = atoi(val);
            if (ival >= 0)
                bsel->timeout = apr_time_from_sec(ival);
        }
        if ((val = apr_table_get(params, "fa"))) {
            int ival = atoi(val);
            if (ival >= 0)
                bsel->max_attempts = ival;
            bsel->max_attempts_set = 1;
        }
        if ((val = apr_table_get(params, "lm"))) {
            proxy_balancer_method *provider;
            provider = ap_lookup_provider(PROXY_LBMETHOD, val, "0");
            if (provider) {
                bsel->lbmethod = provider;
            }
        }
    }
    if (wsel) {
        const char *val;
        if ((val = apr_table_get(params, "lf"))) {
            int ival = atoi(val);
            if (ival >= 1 && ival <= 100) {
                wsel->s->lbfactor = ival;
                if (bsel)
                    recalc_factors(bsel);
            }
        }
        if ((val = apr_table_get(params, "wr"))) {
            if (strlen(val) && strlen(val) < PROXY_WORKER_MAX_ROUTE_SIZ)
                strcpy(wsel->s->route, val);
            else
                *wsel->s->route = '\0';
        }
        if ((val = apr_table_get(params, "rr"))) {
            if (strlen(val) && strlen(val) < PROXY_WORKER_MAX_ROUTE_SIZ)
                strcpy(wsel->s->redirect, val);
            else
                *wsel->s->redirect = '\0';
        }
        if ((val = apr_table_get(params, "dw"))) {
            if (!strcasecmp(val, "Disable"))
                wsel->s->status |= PROXY_WORKER_DISABLED;
            else if (!strcasecmp(val, "Enable"))
                wsel->s->status &= ~PROXY_WORKER_DISABLED;
        }
        if ((val = apr_table_get(params, "ls"))) {
            int ival = atoi(val);
            if (ival >= 0 && ival <= 99) {
                wsel->s->lbset = ival;
             }
        }

    }
    if (apr_table_get(params, "xml")) {
        ap_set_content_type(r, "text/xml");
        ap_rputs("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n", r);
        ap_rputs("<httpd:manager xmlns:httpd=\"http://httpd.apache.org\">\n", r);
        ap_rputs("  <httpd:balancers>\n", r);
        balancer = (proxy_balancer *)conf->balancers->elts;
        for (i = 0; i < conf->balancers->nelts; i++) {
            ap_rputs("    <httpd:balancer>\n", r);
            ap_rvputs(r, "      <httpd:name>", balancer->name, "</httpd:name>\n", NULL);
            ap_rputs("      <httpd:workers>\n", r);
            worker = (proxy_worker *)balancer->workers->elts;
            for (n = 0; n < balancer->workers->nelts; n++) {
                ap_rputs("        <httpd:worker>\n", r);
                ap_rvputs(r, "          <httpd:scheme>", worker->scheme,
                          "</httpd:scheme>\n", NULL);
                ap_rvputs(r, "          <httpd:hostname>", worker->hostname,
                          "</httpd:hostname>\n", NULL);
               ap_rprintf(r, "          <httpd:loadfactor>%d</httpd:loadfactor>\n",
                          worker->s->lbfactor);
                ap_rputs("        </httpd:worker>\n", r);
                ++worker;
            }
            ap_rputs("      </httpd:workers>\n", r);
            ap_rputs("    </httpd:balancer>\n", r);
            ++balancer;
        }
        ap_rputs("  </httpd:balancers>\n", r);
        ap_rputs("</httpd:manager>", r);
    }
    else {
        ap_set_content_type(r, "text/html");
        ap_rputs(DOCTYPE_HTML_3_2
                 "<html><head><title>Balancer Manager</title></head>\n", r);
        ap_rputs("<body><h1>Load Balancer Manager for ", r);
        ap_rvputs(r, ap_get_server_name(r), "</h1>\n\n", NULL);
        ap_rvputs(r, "<dl><dt>Server Version: ",
                  ap_get_server_description(), "</dt>\n", NULL);
        ap_rvputs(r, "<dt>Server Built: ",
                  ap_get_server_built(), "\n</dt></dl>\n", NULL);
        balancer = (proxy_balancer *)conf->balancers->elts;
        for (i = 0; i < conf->balancers->nelts; i++) {

            ap_rputs("<hr />\n<h3>LoadBalancer Status for ", r);
            ap_rvputs(r, "<a href=\"", r->uri, "?b=",
                      balancer->name + sizeof("balancer://") - 1,
                      "\">", NULL);
            ap_rvputs(r, balancer->name, "</a></h3>\n\n", NULL);
            ap_rputs("\n\n<table border=\"0\" style=\"text-align: left;\"><tr>"
                "<th>StickySession</th><th>Timeout</th><th>FailoverAttempts</th><th>Method</th>"
                "</tr>\n<tr>", r);
            ap_rvputs(r, "<td>", balancer->sticky, NULL);
            ap_rprintf(r, "</td><td>%" APR_TIME_T_FMT "</td>",
                apr_time_sec(balancer->timeout));
            ap_rprintf(r, "<td>%d</td>\n", balancer->max_attempts);
            ap_rprintf(r, "<td>%s</td>\n",
                       balancer->lbmethod->name);
            ap_rputs("</table>\n<br />", r);
            ap_rputs("\n\n<table border=\"0\" style=\"text-align: left;\"><tr>"
                "<th>Worker URL</th>"
                "<th>Route</th><th>RouteRedir</th>"
                "<th>Factor</th><th>Set</th><th>Status</th>"
                "<th>Elected</th><th>To</th><th>From</th>"
                "</tr>\n", r);

            worker = (proxy_worker *)balancer->workers->elts;
            for (n = 0; n < balancer->workers->nelts; n++) {
                char fbuf[50];
                ap_rvputs(r, "<tr>\n<td><a href=\"", r->uri, "?b=",
                          balancer->name + sizeof("balancer://") - 1, "&w=",
                          ap_escape_uri(r->pool, worker->name),
                          "\">", NULL);
                ap_rvputs(r, worker->name, "</a></td>", NULL);
                ap_rvputs(r, "<td>", worker->s->route, NULL);
                ap_rvputs(r, "</td><td>", worker->s->redirect, NULL);
                ap_rprintf(r, "</td><td>%d</td>", worker->s->lbfactor);
                ap_rprintf(r, "<td>%d</td><td>", worker->s->lbset);
                if (worker->s->status & PROXY_WORKER_DISABLED)
                   ap_rputs("Dis ", r);
                if (worker->s->status & PROXY_WORKER_IN_ERROR)
                   ap_rputs("Err ", r);
                if (worker->s->status & PROXY_WORKER_STOPPED)
                   ap_rputs("Stop ", r);
                if (worker->s->status & PROXY_WORKER_HOT_STANDBY)
                   ap_rputs("Stby ", r);
                if (PROXY_WORKER_IS_USABLE(worker))
                    ap_rputs("Ok", r);
                if (!PROXY_WORKER_IS_INITIALIZED(worker))
                    ap_rputs("-", r);
                ap_rputs("</td>", r);
                ap_rprintf(r, "<td>%" APR_SIZE_T_FMT "</td><td>", worker->s->elected);
                ap_rputs(apr_strfsize(worker->s->transferred, fbuf), r);
                ap_rputs("</td><td>", r);
                ap_rputs(apr_strfsize(worker->s->read, fbuf), r);
                ap_rputs("</td></tr>\n", r);

                ++worker;
            }
            ap_rputs("</table>\n", r);
            ++balancer;
        }
        ap_rputs("<hr />\n", r);
        if (wsel && bsel) {
            ap_rputs("<h3>Edit worker settings for ", r);
            ap_rvputs(r, wsel->name, "</h3>\n", NULL);
            ap_rvputs(r, "<form method=\"GET\" action=\"", NULL);
            ap_rvputs(r, r->uri, "\">\n<dl>", NULL);
            ap_rputs("<table><tr><td>Load factor:</td><td><input name=\"lf\" type=text ", r);
            ap_rprintf(r, "value=\"%d\"></td></tr>\n", wsel->s->lbfactor);
            ap_rputs("<tr><td>LB Set:</td><td><input name=\"ls\" type=text ", r);
            ap_rprintf(r, "value=\"%d\"></td></tr>\n", wsel->s->lbset);
            ap_rputs("<tr><td>Route:</td><td><input name=\"wr\" type=text ", r);
            ap_rvputs(r, "value=\"", wsel->route, NULL);
            ap_rputs("\"></td></tr>\n", r);
            ap_rputs("<tr><td>Route Redirect:</td><td><input name=\"rr\" type=text ", r);
            ap_rvputs(r, "value=\"", wsel->redirect, NULL);
            ap_rputs("\"></td></tr>\n", r);
            ap_rputs("<tr><td>Status:</td><td>Disabled: <input name=\"dw\" value=\"Disable\" type=radio", r);
            if (wsel->s->status & PROXY_WORKER_DISABLED)
                ap_rputs(" checked", r);
            ap_rputs("> | Enabled: <input name=\"dw\" value=\"Enable\" type=radio", r);
            if (!(wsel->s->status & PROXY_WORKER_DISABLED))
                ap_rputs(" checked", r);
            ap_rputs("></td></tr>\n", r);
            ap_rputs("<tr><td colspan=2><input type=submit value=\"Submit\"></td></tr>\n", r);
            ap_rvputs(r, "</table>\n<input type=hidden name=\"w\" ",  NULL);
            ap_rvputs(r, "value=\"", ap_escape_uri(r->pool, wsel->name), "\">\n", NULL);
            ap_rvputs(r, "<input type=hidden name=\"b\" ", NULL);
            ap_rvputs(r, "value=\"", bsel->name + sizeof("balancer://") - 1,
                      "\">\n</form>\n", NULL);
            ap_rputs("<hr />\n", r);
        }
        else if (bsel) {
            ap_rputs("<h3>Edit balancer settings for ", r);
            ap_rvputs(r, bsel->name, "</h3>\n", NULL);
            ap_rvputs(r, "<form method=\"GET\" action=\"", NULL);
            ap_rvputs(r, r->uri, "\">\n<dl>", NULL);
            ap_rputs("<table><tr><td>StickySession Identifier:</td><td><input name=\"ss\" type=text ", r);
            if (bsel->sticky)
                ap_rvputs(r, "value=\"", bsel->sticky, "\"", NULL);
            ap_rputs("></td><tr>\n<tr><td>Timeout:</td><td><input name=\"tm\" type=text ", r);
            ap_rprintf(r, "value=\"%" APR_TIME_T_FMT "\"></td></tr>\n",
                       apr_time_sec(bsel->timeout));
            ap_rputs("<tr><td>Failover Attempts:</td><td><input name=\"fa\" type=text ", r);
            ap_rprintf(r, "value=\"%d\"></td></tr>\n",
                       bsel->max_attempts);
            ap_rputs("<tr><td>LB Method:</td><td><select name=\"lm\">", r);
            {
                apr_array_header_t *methods;
                ap_list_provider_names_t *method;
                int i;
                methods = ap_list_provider_names(r->pool, PROXY_LBMETHOD, "0");
                method = (ap_list_provider_names_t *)methods->elts;
                for (i = 0; i < methods->nelts; i++) {
                    ap_rprintf(r, "<option value=\"%s\" %s>%s</option>", method->provider_name,
                       (!strcasecmp(bsel->lbmethod->name, method->provider_name)) ? "selected" : "",
                       method->provider_name);
                    method++;
                }
            }
            ap_rputs("</select></td></tr>\n", r);
            ap_rputs("<tr><td colspan=2><input type=submit value=\"Submit\"></td></tr>\n", r);
            ap_rvputs(r, "</table>\n<input type=hidden name=\"b\" ", NULL);
            ap_rvputs(r, "value=\"", bsel->name + sizeof("balancer://") - 1,
                      "\">\n</form>\n", NULL);
            ap_rputs("<hr />\n", r);
        }
        ap_rputs(ap_psignature("",r), r);
        ap_rputs("</body></html>\n", r);
    }
    return OK;
}