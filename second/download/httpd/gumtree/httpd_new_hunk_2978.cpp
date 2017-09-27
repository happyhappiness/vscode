    int i;
    proxy_worker **workers;


    /* Recalculate lbfactors */
    workers = (proxy_worker **)balancer->workers->elts;
    /* Special case if there is only one worker its
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

static apr_status_t lock_remove(void *data)
{
    int i;
    proxy_balancer *balancer;
    server_rec *s = data;
    void *sconf = s->module_config;
    proxy_server_conf *conf = (proxy_server_conf *) ap_get_module_config(sconf, &proxy_module);

    balancer = (proxy_balancer *)conf->balancers->elts;
    for (i = 0; i < conf->balancers->nelts; i++, balancer++) {
        if (balancer->gmutex) {
            apr_global_mutex_destroy(balancer->gmutex);
            balancer->gmutex = NULL;
        }
    }
    return(0);
}

/* post_config hook: */
static int balancer_post_config(apr_pool_t *pconf, apr_pool_t *plog,
                         apr_pool_t *ptemp, server_rec *s)
{
    apr_status_t rv;
    void *sconf = s->module_config;
    proxy_server_conf *conf;
    ap_slotmem_instance_t *new = NULL;
    apr_time_t tstamp;

    /* balancer_post_config() will be called twice during startup.  So, don't
     * set up the static data the 1st time through. */
    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_PRE_CONFIG) {
        return OK;
    }

    if (!ap_proxy_retry_worker_fn) {
        ap_proxy_retry_worker_fn =
                APR_RETRIEVE_OPTIONAL_FN(ap_proxy_retry_worker);
        if (!ap_proxy_retry_worker_fn) {
            ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02230)
                         "mod_proxy must be loaded for mod_proxy_balancer");
            return !OK;
        }
    }

    /*
     * Get slotmem setups
     */
    storage = ap_lookup_provider(AP_SLOTMEM_PROVIDER_GROUP, "shm",
                                 AP_SLOTMEM_PROVIDER_VERSION);
    if (!storage) {
        ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(01177)
                     "Failed to lookup provider 'shm' for '%s': is "
                     "mod_slotmem_shm loaded??",
                     AP_SLOTMEM_PROVIDER_GROUP);
        return !OK;
    }

    tstamp = apr_time_now();
    /*
     * Go thru each Vhost and create the shared mem slotmem for
     * each balancer's workers
     */
    while (s) {
        int i,j;
        proxy_balancer *balancer;
        sconf = s->module_config;
        conf = (proxy_server_conf *)ap_get_module_config(sconf, &proxy_module);

        if (conf->bslot) {
            /* Shared memory already created for this proxy_server_conf.
             */
            s = s->next;
            continue;
        }

        if (conf->balancers->nelts) {
            conf->max_balancers = conf->balancers->nelts + conf->bgrowth;
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01178) "Doing balancers create: %d, %d (%d)",
                         (int)ALIGNED_PROXY_BALANCER_SHARED_SIZE,
                         (int)conf->balancers->nelts, conf->max_balancers);

            rv = storage->create(&new, conf->id,
                                 ALIGNED_PROXY_BALANCER_SHARED_SIZE,
                                 conf->max_balancers, AP_SLOTMEM_TYPE_PREGRAB, pconf);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01179) "balancer slotmem_create failed");
                return !OK;
            }
            conf->bslot = new;
        }
        conf->storage = storage;

        /* Initialize shared scoreboard data */
        balancer = (proxy_balancer *)conf->balancers->elts;
        for (i = 0; i < conf->balancers->nelts; i++, balancer++) {
            proxy_worker **workers;
            proxy_worker *worker;
            proxy_balancer_shared *bshm;
            unsigned int index;

            balancer->max_workers = balancer->workers->nelts + balancer->growth;

            /* Create global mutex */
            rv = ap_global_mutex_create(&(balancer->gmutex), NULL, balancer_mutex_type,
                                        balancer->s->sname, s, pconf, 0);
            if (rv != APR_SUCCESS || !balancer->gmutex) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01180)
                             "mutex creation of %s : %s failed", balancer_mutex_type,
                             balancer->s->sname);
                return HTTP_INTERNAL_SERVER_ERROR;
            }

            apr_pool_cleanup_register(pconf, (void *)s, lock_remove,
                                      apr_pool_cleanup_null);

            /* setup shm for balancers */
            if ((rv = storage->grab(conf->bslot, &index)) != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01181) "balancer slotmem_grab failed");
                return !OK;

            }
            if ((rv = storage->dptr(conf->bslot, index, (void *)&bshm)) != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01182) "balancer slotmem_dptr failed");
                return !OK;
            }
            if ((rv = ap_proxy_share_balancer(balancer, bshm, index)) != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01183) "Cannot share balancer");
                return !OK;
            }

            /* create slotmem slots for workers */
            ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(01184) "Doing workers create: %s (%s), %d, %d",
                         balancer->s->name, balancer->s->sname,
                         (int)ALIGNED_PROXY_WORKER_SHARED_SIZE,
                         (int)balancer->max_workers);

            rv = storage->create(&new, balancer->s->sname,
                                 ALIGNED_PROXY_WORKER_SHARED_SIZE,
                                 balancer->max_workers, AP_SLOTMEM_TYPE_PREGRAB, pconf);
            if (rv != APR_SUCCESS) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01185) "worker slotmem_create failed");
                return !OK;
            }
            balancer->wslot = new;
            balancer->storage = storage;

            /* sync all timestamps */
            balancer->wupdated = balancer->s->wupdated = tstamp;

            /* now go thru each worker */
            workers = (proxy_worker **)balancer->workers->elts;
            for (j = 0; j < balancer->workers->nelts; j++, workers++) {
                proxy_worker_shared *shm;

                worker = *workers;
                if ((rv = storage->grab(balancer->wslot, &index)) != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01186) "worker slotmem_grab failed");
                    return !OK;

                }
                if ((rv = storage->dptr(balancer->wslot, index, (void *)&shm)) != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01187) "worker slotmem_dptr failed");
                    return !OK;
                }
                if ((rv = ap_proxy_share_worker(worker, shm, index)) != APR_SUCCESS) {
                    ap_log_error(APLOG_MARK, APLOG_EMERG, rv, s, APLOGNO(01188) "Cannot share worker");
                    return !OK;
                }
                worker->s->updated = tstamp;
            }
        }
        s = s->next;
    }

    return OK;
}

static void create_radio(const char *name, unsigned int flag, request_rec *r)
{
    ap_rvputs(r, "<td>On <input name='", name, "' id='", name, "' value='1' type=radio", NULL);
    if (flag)
        ap_rputs(" checked", r);
    ap_rvputs(r, "> <br/> Off <input name='", name, "' id='", name, "' value='0' type=radio", NULL);
    if (!flag)
        ap_rputs(" checked", r);
    ap_rputs("></td>\n", r);
}

static void push2table(const char *input, apr_table_t *params,
                       const char *allowed[], apr_pool_t *p)
{
    char *args;
    char *tok, *val;
    char *key;

    if (input == NULL) {
        return;
    }
    args = apr_pstrdup(p, input);

    key = apr_strtok(args, "&", &tok);
    while (key) {
        val = strchr(key, '=');
        if (val) {
            *val++ = '\0';
        }
        else {
            val = "";
        }
        ap_unescape_url(key);
        ap_unescape_url(val);
        if (allowed == NULL) { /* allow all */
            apr_table_set(params, key, val);
        }
        else {
            const char **ok = allowed;
            while (*ok) {
                if (strcmp(*ok, key) == 0) {
                    apr_table_set(params, key, val);
                    break;
                }
                ok++;
            }
        }
        key = apr_strtok(NULL, "&", &tok);
    }
}

/* Manages the loadfactors and member status
 *   The balancer, worker and nonce are obtained from
 *   the request args (?b=...&w=...&nonce=....).
 *   All other params are pulled from any POST
 *   data that exists.
 * TODO:
 *   /.../<whatever>/balancer/worker/nonce
 */
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
        const char *allowed[] = { "w", "b", "nonce", NULL };
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
            nworker = ap_proxy_get_worker(conf->pool, bsel, conf, val);
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
        ap_set_content_type(r, "text/xml");
        ap_rputs("<?xml version='1.0' encoding='UTF-8' ?>\n", r);
        ap_rputs("<httpd:manager xmlns:httpd='http://httpd.apache.org'>\n", r);
        ap_rputs("  <httpd:balancers>\n", r);
        balancer = (proxy_balancer *)conf->balancers->elts;
        for (i = 0; i < conf->balancers->nelts; i++) {
            ap_rputs("    <httpd:balancer>\n", r);
            ap_rvputs(r, "      <httpd:name>", balancer->s->name, "</httpd:name>\n", NULL);
            ap_rputs("      <httpd:workers>\n", r);
            workers = (proxy_worker **)balancer->workers->elts;
            for (n = 0; n < balancer->workers->nelts; n++) {
                worker = *workers;
                ap_rputs("        <httpd:worker>\n", r);
                ap_rvputs(r, "          <httpd:scheme>", worker->s->scheme,
                          "</httpd:scheme>\n", NULL);
                ap_rvputs(r, "          <httpd:hostname>", worker->s->hostname,
                          "</httpd:hostname>\n", NULL);
                ap_rprintf(r, "          <httpd:loadfactor>%d</httpd:loadfactor>\n",
                          worker->s->lbfactor);
                ap_rputs("        </httpd:worker>\n", r);
                ++workers;
            }
            ap_rputs("      </httpd:workers>\n", r);
            ap_rputs("    </httpd:balancer>\n", r);
