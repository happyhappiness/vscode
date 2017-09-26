        conn->addr = worker->cp->addr;
        if ((uerr = PROXY_THREAD_UNLOCK(worker)) != APR_SUCCESS) {
            ap_log_error(APLOG_MARK, APLOG_ERR, uerr, r->server,
                         "proxy: unlock");
        }
    }
    else
        conn->addr = worker->cp->addr;

    if (err != APR_SUCCESS) {
        return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                             apr_pstrcat(p, "DNS lookup failure for: ",
                                         conn->hostname, NULL));
    }

    /* Get the server port for the Via headers */
    {
        server_port = ap_get_server_port(r);
        if (ap_is_default_port(server_port, r)) {
            strcpy(server_portstr,"");
        } else {
            apr_snprintf(server_portstr, server_portstr_size, ":%d",
                         server_port);
        }
    }
    /* check if ProxyBlock directive on this host */
    if (OK != ap_proxy_checkproxyblock(r, conf, conn->addr)) {
