    host = ap_rxplus_pmatch(cmd->pool, fcgi_backend_regex, 1);
    if (host[0] == '[' && host[strlen(host) - 1] == ']') {
        host += 1;
        host[strlen(host) - 1] = '\0';
    }

    conf->port = atoi(ap_rxplus_pmatch(cmd->pool, fcgi_backend_regex, 2));
    if (conf->port > 65535) {
        return apr_pstrcat(cmd->pool,
                           dname, ": backend-address '",
                           argv[ca],
                           "' has invalid port",
                           NULL);
    }

    conf->backend = argv[ca];
    conf->host = host;
    ca++;

    rv = apr_sockaddr_info_get(&conf->backend_addrs, conf->host,
                               APR_UNSPEC, conf->port, 0, cmd->pool);
    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_STARTUP|APLOG_CRIT, rv, NULL,
