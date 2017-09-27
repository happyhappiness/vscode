    }
    ap_log_rerror(APLOG_MARK, APLOG_TRACE1, 0, r, "canonicalising URL %s", url);

    return OK;
}

/* CONNECT handler */
static int proxy_connect_handler(request_rec *r, proxy_worker *worker,
                                 proxy_server_conf *conf,
                                 char *url, const char *proxyname,
                                 apr_port_t proxyport)
{
