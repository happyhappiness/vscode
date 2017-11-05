apr_status_t simple_io_accept(simple_core_t * sc, simple_sb_t * sb)
{
    apr_status_t rv;
    apr_pool_t *ptrans;
    apr_socket_t *socket;
    ap_listen_rec *lr = (ap_listen_rec *) sb->baton;

    /* pqXXXXXX: Consider doing pool recycling like the event/worker MPMs do. */
    apr_pool_create(&ptrans, NULL);

    apr_pool_tag(ptrans, "transaction");

    rv = apr_socket_accept(&socket, lr->sd, ptrans);
    if (rv) {
        /* pqXXXXXX: unixd.c has _tons_ of custom handling on return values
         * from accept, but it seems really crazy, it either worked, or didn't, 
         * but taking this approach of swallowing the error it is possible we have a 
         * fatal error on our listening socket, but we don't notice.  
         * 
         * Need to discuss this on dev@
         */
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, NULL,
                     "simple_io_accept: apr_socket_accept failed");
        return APR_SUCCESS;
    }
    else {
        simple_conn_t *scon = apr_pcalloc(ptrans, sizeof(simple_conn_t));
        scon->pool = ptrans;
        scon->sock = socket;
        scon->sc = sc;

        return apr_thread_pool_push(sc->workers,
                                    simple_io_setup_conn,
                                    scon,
                                    APR_THREAD_TASK_PRIORITY_NORMAL, NULL);
    }

    return APR_SUCCESS;
}