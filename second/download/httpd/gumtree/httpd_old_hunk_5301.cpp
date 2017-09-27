        return ap_proxyerror(r, HTTP_BAD_GATEWAY,
                             apr_pstrcat(p, "DNS lookup failure for: ",
                                         conn->hostname, NULL));
    }

    /* Get the server port for the Via headers */
    {
        server_port = ap_get_server_port(r);
        if (ap_is_default_port(server_port, r)) {
            strcpy(server_portstr,"");
        }
        else {
            apr_snprintf(server_portstr, server_portstr_size, ":%d",
                         server_port);
        }
    }
    /* check if ProxyBlock directive on this host */
    if (OK != ap_proxy_checkproxyblock2(r, conf, uri->hostname, 
                                       proxyname ? NULL : conn->addr)) {
        return ap_proxyerror(r, HTTP_FORBIDDEN,
                             "Connect to remote machine blocked");
    }
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00947)
                 "connected %s to %s:%d", *url, conn->hostname, conn->port);
    return OK;
}

#define USE_ALTERNATE_IS_CONNECTED 1
