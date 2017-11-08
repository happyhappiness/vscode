static apr_status_t simple_setup_listeners(simple_core_t * sc)
{
    ap_listen_rec *lr;
    apr_status_t rv;

    for (lr = ap_listeners; lr != NULL; lr = lr->next) {
        apr_pollfd_t *pfd = apr_palloc(sc->pool, sizeof(apr_pollfd_t));
        simple_sb_t *sb = apr_pcalloc(sc->pool, sizeof(simple_sb_t));

        pfd->p = sc->pool;
        pfd->desc_type = APR_POLL_SOCKET;
        pfd->desc.s = lr->sd;
        pfd->reqevents = APR_POLLIN;

        sb->type = SIMPLE_PT_CORE_ACCEPT;
        sb->baton = lr;

        pfd->client_data = sb;

        rv = apr_socket_opt_set(pfd->desc.s, APR_SO_NONBLOCK, 1);
        if (rv) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                         "simple_setup_workers: apr_socket_opt_set(APR_SO_NONBLOCK = 1) failed on %pI",
                         lr->bind_addr);
            return rv;
        }

        rv = apr_pollcb_add(sc->pollcb, pfd);
        if (rv) {
            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                         "simple_setup_workers: apr_pollcb_add failed on %pI",
                         lr->bind_addr);
            return rv;
        }
    }

    return APR_SUCCESS;
}