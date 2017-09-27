    int i;
    proxy_worker **workers;


    /* Recalculate lbfactors */
    workers = (proxy_worker **)balancer->workers->elts;
    /* Special case if there is only one worker it's
     * load factor will always be 1
     */
    if (balancer->workers->nelts == 1) {
        (*workers)->s->lbstatus = (*workers)->s->lbfactor = 1;
        return;
    }
    for (i = 0; i < balancer->workers->nelts; i++) {
        /* Update the status entries */
        workers[i]->s->lbstatus = workers[i]->s->lbfactor;
    }
}

/* post_config hook: */
static int balancer_init(apr_pool_t *p, apr_pool_t *plog,
                         apr_pool_t *ptemp, server_rec *s)
{
    apr_uuid_t uuid;
    void *data;
    const char *userdata_key = "mod_proxy_balancer_init";

    /* balancer_init() will be called twice during startup.  So, only
     * set up the static data the 1st time through. */
    apr_pool_userdata_get(&data, userdata_key, s->process->pool);
    if (!data) {
        /* Retrieve a UUID and store the nonce for the lifetime of
         * the process. */
        apr_uuid_get(&uuid);
        apr_uuid_format(balancer_nonce, &uuid);
        apr_pool_userdata_set((const void *)1, userdata_key,
                               apr_pool_cleanup_null, s->process->pool);
    }
    return OK;
}

/* Manages the loadfactors and member status
 */
static int balancer_handler(request_rec *r)
{
    void *sconf = r->server->module_config;
    proxy_server_conf *conf = (proxy_server_conf *)
        ap_get_module_config(sconf, &proxy_module);
    proxy_balancer *balancer, *bsel = NULL;
    proxy_worker *worker, *wsel = NULL;
    proxy_worker **workers = NULL;
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
    
    /* Check that the supplied nonce matches this server's nonce;
     * otherwise ignore all parameters, to prevent a CSRF attack. */
    if (*balancer_nonce &&
        ((name = apr_table_get(params, "nonce")) == NULL 
        || strcmp(balancer_nonce, name) != 0)) {
        apr_table_clear(params);
    }

    if ((name = apr_table_get(params, "b")))
        bsel = ap_proxy_get_balancer(r->pool, conf,
            apr_pstrcat(r->pool, "balancer://", name, NULL));
    if ((name = apr_table_get(params, "w"))) {
        proxy_worker *ws;

        ws = ap_proxy_get_worker(r->pool, conf, name);
        if (bsel && ws) {
            workers = (proxy_worker **)bsel->workers->elts;
            for (n = 0; n < bsel->workers->nelts; n++) {
                worker = *workers;
                if (strcasecmp(worker->name, ws->name) == 0) {
                    wsel = worker;
                    break;
                }
                ++workers;
            }
        }
    }
    /* First set the params */
    /*
     * Note that it is not possible set the proxy_balancer because it is not
     * in shared memory.
     */
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
            workers = (proxy_worker **)balancer->workers->elts;
            for (n = 0; n < balancer->workers->nelts; n++) {
                worker = *workers;
                ap_rputs("        <httpd:worker>\n", r);
                ap_rvputs(r, "          <httpd:scheme>", worker->scheme,
                          "</httpd:scheme>\n", NULL);
                ap_rvputs(r, "          <httpd:hostname>", worker->hostname,
                          "</httpd:hostname>\n", NULL);
               ap_rprintf(r, "          <httpd:loadfactor>%d</httpd:loadfactor>\n",
                          worker->s->lbfactor);
                ap_rputs("        </httpd:worker>\n", r);
                ++workers;
            }
            ap_rputs("      </httpd:workers>\n", r);
            ap_rputs("    </httpd:balancer>\n", r);
