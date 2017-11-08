static int static_list_servers(void *baton,
                               request_rec *r,
                               apr_table_t *params,
                               apr_array_header_t **out_servers)
{
    apr_status_t rv;
    char *ip;
    char *strtok_state;
    apr_array_header_t *servers;
    const char *hosts = apr_table_get(params, "hosts");
    const char *order = apr_table_get(params, "order");

    servers = apr_array_make(r->pool, 10, sizeof(ap_serf_server_t *));
    
    ip = apr_strtok(apr_pstrdup(r->pool, hosts), ",", &strtok_state);
    while (ip) {
        char *host_str;
        char *scope_id;
        apr_port_t port = 0;
        
        rv = apr_parse_addr_port(&host_str, &scope_id, &port, ip, r->pool);
        if (!rv) {
            ap_serf_server_t *s = apr_palloc(r->pool, sizeof(ap_serf_server_t));
            s->ip = host_str;
            s->port = port ? port : 80;
            APR_ARRAY_PUSH(servers, ap_serf_server_t *) = s;
        }
        ip = apr_strtok(NULL, ",", &strtok_state);
    }

    if (strcmp(order, "random") == 0) {
        /* TODO: support order=random */
    }

    *out_servers = servers;

    return OK;
}