        char *host_str;
        char *scope_id;
        apr_port_t port;

        rv = apr_parse_addr_port(&host_str, &scope_id, &port, split, p);
        if (rv != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                         "socache: Failed to Parse memcache Server: '%s'", split);
            return rv;
        }

        if (host_str == NULL) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                         "socache: Failed to Parse Server, "
                         "no hostname specified: '%s'", split);
            return APR_EINVAL;
        }

        if (port == 0) {
            port = MC_DEFAULT_SERVER_PORT;
