static server_rec *init_server_config(process_rec *process, apr_pool_t *p)
{
    apr_status_t rv;
    server_rec *s = (server_rec *) apr_pcalloc(p, sizeof(server_rec));

    apr_file_open_stderr(&s->error_log, p);
    s->process = process;
    s->port = 0;
    s->server_admin = DEFAULT_ADMIN;
    s->server_hostname = NULL;
    s->server_scheme = NULL;
    s->error_fname = DEFAULT_ERRORLOG;
    s->loglevel = DEFAULT_LOGLEVEL;
    s->limit_req_line = DEFAULT_LIMIT_REQUEST_LINE;
    s->limit_req_fieldsize = DEFAULT_LIMIT_REQUEST_FIELDSIZE;
    s->limit_req_fields = DEFAULT_LIMIT_REQUEST_FIELDS;
    s->timeout = apr_time_from_sec(DEFAULT_TIMEOUT);
    s->keep_alive_timeout = apr_time_from_sec(DEFAULT_KEEPALIVE_TIMEOUT);
    s->keep_alive_max = DEFAULT_KEEPALIVE;
    s->keep_alive = 1;
    s->next = NULL;
    s->addrs = apr_pcalloc(p, sizeof(server_addr_rec));

    /* NOT virtual host; don't match any real network interface */
    rv = apr_sockaddr_info_get(&s->addrs->host_addr,
                               NULL, APR_INET, 0, 0, p);
    ap_assert(rv == APR_SUCCESS); /* otherwise: bug or no storage */

    s->addrs->host_port = 0; /* matches any port */
    s->addrs->virthost = ""; /* must be non-NULL */
    s->names = s->wild_names = NULL;

    s->module_config = create_server_config(p, s);
    s->lookup_defaults = create_default_per_dir_config(p);

    return s;
}