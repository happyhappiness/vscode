                                       proxy_server_conf *conf)
{
    apr_status_t rv;

    if ((rv = PROXY_THREAD_LOCK(balancer)) != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, r->server,
            "proxy: BALANCER: lock");
        return HTTP_INTERNAL_SERVER_ERROR;
    }
    /* TODO: calculate the bytes transferred
     * This will enable to elect the worker that has
     * the lowest load.
     * The bytes transferred depends on the protocol
     * used, so each protocol handler should keep the
     * track on that.
     */

    PROXY_THREAD_UNLOCK(balancer);
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, r->server,
                 "proxy_balancer_post_request for (%s)", balancer->name);

    return OK;
}

