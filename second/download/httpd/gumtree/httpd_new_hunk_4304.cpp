        wshared = ap_malloc(sizeof(proxy_worker_shared));  /* will be freed ap_proxy_share_worker */
    else
        wshared = apr_palloc(p, sizeof(proxy_worker_shared));

    memset(wshared, 0, sizeof(proxy_worker_shared));

    wshared->port = (uri.port ? uri.port : ap_proxy_port_of_scheme(uri.scheme));
    if (uri.port && uri.port == ap_proxy_port_of_scheme(uri.scheme)) {
        uri.port = 0;
    }
    ptr = apr_uri_unparse(p, &uri, APR_URI_UNP_REVEALPASSWORD);
    if (PROXY_STRNCPY(wshared->name, ptr) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, ap_server_conf, APLOGNO(02808)
