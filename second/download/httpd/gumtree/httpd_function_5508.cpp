static const char *get_addresses(apr_pool_t *p, const char *w_,
                                 server_addr_rec ***paddr,
                                 apr_port_t default_port)
{
    apr_sockaddr_t *my_addr;
    server_addr_rec *sar;
    char *w, *host, *scope_id;
    int wild_port;
    apr_size_t wlen;
    apr_port_t port;
    apr_status_t rv;

    if (*w_ == '\0')
        return NULL;

    w = apr_pstrdup(p, w_);
    /* apr_parse_addr_port() doesn't understand ":*" so handle that first. */
    wlen = strlen(w);                    /* wlen must be > 0 at this point */
    wild_port = 0;
    if (w[wlen - 1] == '*') {
        if (wlen < 2) {
            wild_port = 1;
        }
        else if (w[wlen - 2] == ':') {
            w[wlen - 2] = '\0';
            wild_port = 1;
        }
    }
    rv = apr_parse_addr_port(&host, &scope_id, &port, w, p);
    /* If the string is "80", apr_parse_addr_port() will be happy and set
     * host to NULL and port to 80, so watch out for that.
     */
    if (rv != APR_SUCCESS) {
        return "The address or port is invalid";
    }
    if (!host) {
        return "Missing address for VirtualHost";
    }
    if (scope_id) {
        return "Scope ids are not supported";
    }
    if (!port && !wild_port) {
        port = default_port;
    }

    if (strcmp(host, "*") == 0) {
        rv = apr_sockaddr_info_get(&my_addr, "0.0.0.0", APR_INET, port, 0, p);
        if (rv) {
            return "Could not resolve address '0.0.0.0' -- "
                "check resolver configuration.";
        }
    }
    else if (strcasecmp(host, "_default_") == 0
        || strcmp(host, "255.255.255.255") == 0) {
        rv = apr_sockaddr_info_get(&my_addr, "255.255.255.255", APR_INET, port, 0, p);
        if (rv) {
            return "Could not resolve address '255.255.255.255' -- "
                "check resolver configuration.";
        }
    }
    else {
        rv = apr_sockaddr_info_get(&my_addr, host, APR_UNSPEC, port, 0, p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, NULL,
                "Could not resolve host name %s -- ignoring!", host);
            return NULL;
        }
    }

    /* Remember all addresses for the host */

    do {
        sar = apr_pcalloc(p, sizeof(server_addr_rec));
        **paddr = sar;
        *paddr = &sar->next;
        sar->host_addr = my_addr;
        sar->host_port = port;
        sar->virthost = host;
        my_addr = my_addr->next;
    } while (my_addr);

    return NULL;
}