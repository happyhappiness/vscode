        wshared = ap_malloc(sizeof(proxy_worker_shared));  /* will be freed ap_proxy_share_worker */
    else
        wshared = apr_palloc(p, sizeof(proxy_worker_shared));

    memset(wshared, 0, sizeof(proxy_worker_shared));

    ptr = apr_uri_unparse(p, &uri, APR_URI_UNP_REVEALPASSWORD);
    if (PROXY_STRNCPY(wshared->name, ptr) != APR_SUCCESS) {
        return apr_psprintf(p, "worker name (%s) too long", ptr);
    }
    if (PROXY_STRNCPY(wshared->scheme, uri.scheme) != APR_SUCCESS) {
        return apr_psprintf(p, "worker scheme (%s) too long", uri.scheme);
    }
    if (PROXY_STRNCPY(wshared->hostname, uri.hostname) != APR_SUCCESS) {
        return apr_psprintf(p, "worker hostname (%s) too long", uri.hostname);
