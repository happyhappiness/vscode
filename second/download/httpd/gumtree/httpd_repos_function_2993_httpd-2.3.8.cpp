static int
simple_open_logs(apr_pool_t * p,
                 apr_pool_t * plog, apr_pool_t * ptemp, server_rec * s)
{
    int nsock;

    nsock = ap_setup_listeners(s);

    if (nsock < 1) {
        ap_log_error(APLOG_MARK, APLOG_ALERT, 0,
                     s,
                     "simple_open_logs: no listening sockets available, shutting down");
        return DONE;
    }

    return OK;
}