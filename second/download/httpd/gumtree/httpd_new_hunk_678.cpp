    if (APR_SUCCESS != err) {
        return ap_proxyerror(r, HTTP_BAD_GATEWAY, apr_pstrcat(p,
                                                 "DNS lookup failure for: ",
                                                        connectname, NULL));
    }

    /*
     * At this point we have a list of one or more IP addresses of the
     * machine to connect to. If configured, reorder this list so that the
     * "best candidate" is first try. "best candidate" could mean the least
     * loaded server, the fastest responding server, whatever.
     *
