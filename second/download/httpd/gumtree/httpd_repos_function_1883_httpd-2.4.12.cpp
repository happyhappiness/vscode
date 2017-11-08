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