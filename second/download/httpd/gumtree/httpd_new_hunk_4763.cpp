                      "pre_connection setup failed (%d)", rc);
        return HTTP_INTERNAL_SERVER_ERROR;
    }

    ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r,
                  "connection complete to %pI (%s)",
                  nexthop, connectname);
    apr_table_setn(r->notes, "proxy-source-port", apr_psprintf(r->pool, "%hu",
                   backconn->local_addr->port));

    /* If we are connecting through a remote proxy, we need to pass
     * the CONNECT request on to it.
     */
