
#if APR_TCP_NODELAY_INHERITED
    ap_sock_disable_nagle(s);
#endif

#if defined(SO_REUSEPORT)
    if (ap_have_so_reuseport && ap_listencbratio > 0) {
        int thesock;
        apr_os_sock_get(&thesock, s);
        if (setsockopt(thesock, SOL_SOCKET, SO_REUSEPORT,
                       (void *)&one, sizeof(int)) < 0) {
            stat = apr_get_netos_error();
            ap_log_perror(APLOG_MARK, APLOG_CRIT, stat, p, APLOGNO(02638)
