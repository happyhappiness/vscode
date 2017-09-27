    }
    /* check if ProxyBlock directive on this host */
    if (OK != ap_proxy_checkproxyblock(r, conf, conn->addr)) {
        return ap_proxyerror(r, HTTP_FORBIDDEN,
                             "Connect to remote machine blocked");
    }
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00947)
                 "connected %s to %s:%d", *url, conn->hostname, conn->port);
    return OK;
}

#define USE_ALTERNATE_IS_CONNECTED 1

#if !defined(APR_MSG_PEEK) && defined(MSG_PEEK)
