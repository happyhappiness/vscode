            return HTTP_BAD_REQUEST;
        }
        rv = apr_parse_addr_port(&host, &scope_id, &port, r->hostname, r->pool);
        if (rv != APR_SUCCESS || scope_id) {
            return HTTP_BAD_REQUEST;
        }
        if (strcmp(host, servername)) {
            ap_log_error(APLOG_MARK, APLOG_ERR, 0, r->server,
                        "Hostname %s provided via SNI and hostname %s provided"
                        " via HTTP are different", servername, host);
            return HTTP_BAD_REQUEST;
        }
    }
