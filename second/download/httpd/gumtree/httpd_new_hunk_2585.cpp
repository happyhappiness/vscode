}

static int hm_post_config(apr_pool_t *p, apr_pool_t *plog,
                          apr_pool_t *ptemp, server_rec *s)
{
    apr_status_t rv;
    hm_ctx_t *ctx = ap_get_module_config(s->module_config,
                                         &heartmonitor_module);
    APR_OPTIONAL_FN_TYPE(ap_watchdog_get_instance) *hm_watchdog_get_instance;
    APR_OPTIONAL_FN_TYPE(ap_watchdog_register_callback) *hm_watchdog_register_callback;

    hm_watchdog_get_instance = APR_RETRIEVE_OPTIONAL_FN(ap_watchdog_get_instance);
    hm_watchdog_register_callback = APR_RETRIEVE_OPTIONAL_FN(ap_watchdog_register_callback);
    if (!hm_watchdog_get_instance || !hm_watchdog_register_callback) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, 0, s, APLOGNO(02093)
                     "mod_watchdog is required");
        return !OK;
    }

    /* Create the slotmem */
    if (ap_state_query(AP_SQ_MAIN_STATE) == AP_SQ_MS_CREATE_CONFIG) {
        /* this is the real thing */
        if (maxworkers) {
            storage = ap_lookup_provider(AP_SLOTMEM_PROVIDER_GROUP, "shm",
                                         AP_SLOTMEM_PROVIDER_VERSION);
            if (!storage) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02284)
                             "failed to lookup provider 'shm' for '%s', "
                             "maybe you need to load mod_slotmem_shm?",
                             AP_SLOTMEM_PROVIDER_GROUP);
                return !OK;
            }
            storage->create(&slotmem, "mod_heartmonitor", sizeof(hm_slot_server_t), maxworkers, AP_SLOTMEM_TYPE_PREGRAB, p);
            if (!slotmem) {
                ap_log_error(APLOG_MARK, APLOG_EMERG, 0, s, APLOGNO(02285)
                             "slotmem_create for status failed");
                return !OK;
            }
        }
    }

    if (!ctx->active) {
        return OK;
    }
    rv = hm_watchdog_get_instance(&ctx->watchdog,
                                  HM_WATHCHDOG_NAME,
                                  0, 1, p);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(02094)
                     "Failed to create watchdog instance (%s)",
                     HM_WATHCHDOG_NAME);
        return !OK;
    }
    /* Register a callback with zero interval. */
    rv = hm_watchdog_register_callback(ctx->watchdog,
                                       0,
                                       ctx,
                                       hm_watchdog_callback);
    if (rv) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(02095)
                     "Failed to register watchdog callback (%s)",
                     HM_WATHCHDOG_NAME);
        return !OK;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(02096)
                 "wd callback %s", HM_WATHCHDOG_NAME);
    return OK;
}

static int hm_handler(request_rec *r)
{
    apr_bucket_brigade *input_brigade;
    apr_size_t len;
    char *buf;
    apr_status_t status;
    apr_table_t *tbl;
    hm_server_t hmserver;
    char *ip;
    hm_ctx_t *ctx;

    if (strcmp(r->handler, "heartbeat")) {
        return DECLINED;
    }
    if (r->method_number != M_POST) {
        return HTTP_METHOD_NOT_ALLOWED;
    }

    len = MAX_MSG_LEN;
    ctx = ap_get_module_config(r->server->module_config,
            &heartmonitor_module);

    buf = apr_pcalloc(r->pool, MAX_MSG_LEN);
    input_brigade = apr_brigade_create(r->connection->pool, r->connection->bucket_alloc);
    status = ap_get_brigade(r->input_filters, input_brigade, AP_MODE_READBYTES, APR_BLOCK_READ, MAX_MSG_LEN);
    if (status != APR_SUCCESS) {
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    apr_brigade_flatten(input_brigade, buf, &len);

    /* we can't use hm_processmsg because it uses hm_get_server() */
    buf[len] = '\0';
    tbl = apr_table_make(r->pool, 10);
    qs_to_table(buf, tbl, r->pool);
    apr_sockaddr_ip_get(&ip, r->connection->client_addr);
    hmserver.ip = ip;
    hmserver.port = 80;
    if (apr_table_get(tbl, "port") != NULL)
        hmserver.port = atoi(apr_table_get(tbl, "port"));
    hmserver.busy = atoi(apr_table_get(tbl, "busy"));
    hmserver.ready = atoi(apr_table_get(tbl, "ready"));
    hmserver.seen = apr_time_now();
    hm_update_stat(ctx, &hmserver, r->pool);

    ap_set_content_type(r, "text/plain");
    ap_set_content_length(r, 2);
    ap_rputs("OK", r);
    ap_rflush(r);

    return OK;
}

static void hm_register_hooks(apr_pool_t *p)
