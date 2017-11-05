static int hb_list_servers(void *baton,
                           request_rec *r,
                           apr_table_t *params,
                           apr_array_header_t **out_servers)
{
    int i;
    hb_server_t *hbs;
    apr_status_t rv;
    apr_pool_t *tpool;
    apr_array_header_t *tmpservers;
    apr_array_header_t *servers;
    const char *path = apr_table_get(params, "path");

    apr_pool_create(&tpool, r->pool);

    path = ap_server_root_relative(tpool, path);

    tmpservers = apr_array_make(tpool, 32, sizeof(hb_server_t *));
    rv = read_heartbeats(path, tmpservers, tpool);

    if (rv) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                      "SerfCluster: Heartbeat unable to read '%s'", path);
        apr_pool_destroy(tpool);
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    
    qsort(tmpservers->elts, tmpservers->nelts, sizeof(hb_server_t *),
          hb_server_sort);

    servers = apr_array_make(r->pool, tmpservers->nelts, sizeof(ap_serf_server_t *));
    for (i = 0;
         i < tmpservers->nelts;
         i++)
    {
        ap_serf_server_t *x;

        hbs = APR_ARRAY_IDX(tmpservers, i, hb_server_t *);
        if (hbs->ready > 0) {
            x = apr_palloc(r->pool, sizeof(ap_serf_server_t));
            x->ip = apr_pstrdup(r->pool, hbs->ip);
            x->port = hbs->port;
            APR_ARRAY_PUSH(servers, ap_serf_server_t *) = x;
        }
    }

    *out_servers = servers;
    apr_pool_destroy(tpool);
    return OK;
}