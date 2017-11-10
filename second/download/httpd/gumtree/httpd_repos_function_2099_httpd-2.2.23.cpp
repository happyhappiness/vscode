const char *ap_parse_vhost_addrs(apr_pool_t *p,
                                 const char *hostname,
                                 server_rec *s)
{
    server_addr_rec **addrs;
    const char *err;

    /* start the list of addreses */
    addrs = &s->addrs;
    while (hostname[0]) {
        err = get_addresses(p, ap_getword_conf(p, &hostname), &addrs, s->port);
        if (err) {
            *addrs = NULL;
            return err;
        }
    }
    /* terminate the list */
    *addrs = NULL;
    if (s->addrs) {
        if (s->addrs->host_port) {
            /* override the default port which is inherited from main_server */
            s->port = s->addrs->host_port;
        }
    }
    return NULL;
}