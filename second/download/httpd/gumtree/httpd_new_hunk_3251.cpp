    s->keep_alive = 1;
    s->next = NULL;
    s->addrs = apr_pcalloc(p, sizeof(server_addr_rec));

    /* NOT virtual host; don't match any real network interface */
    rv = apr_sockaddr_info_get(&s->addrs->host_addr,
                               NULL, APR_UNSPEC, 0, 0, p);
    if (rv != APR_SUCCESS) {
        /* should we test here for rv being an EAIERR? */
        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, rv, NULL, APLOGNO(00530)
                     "initialisation: bug or getaddrinfo fail");
        return NULL;
    }

    s->addrs->host_port = 0; /* matches any port */
    s->addrs->virthost = ""; /* must be non-NULL */
    s->names = s->wild_names = NULL;

    s->module_config = create_server_config(p, s);
