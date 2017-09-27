    if (DECLINED == access_status) {
        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, r->server,
                    "proxy: No protocol handler was valid for the URL %s. "
                    "If you are using a DSO version of mod_proxy, make sure "
                    "the proxy submodules are included in the configuration "
                    "using LoadModule.", r->uri);
        access_status = HTTP_INTERNAL_SERVER_ERROR;
        goto cleanup;
    }
cleanup:
    if (balancer) {
        int post_status = proxy_run_post_request(worker, balancer, r, conf);
        if (post_status == DECLINED) {
