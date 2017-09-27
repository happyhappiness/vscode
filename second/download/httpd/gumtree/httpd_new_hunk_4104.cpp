    for (direct_connect = i = 0; i < conf->dirconn->nelts &&
                                        !direct_connect; i++) {
        direct_connect = list[i].matcher(&list[i], r);
    }
#if DEBUGGING
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                (direct_connect) ? APLOGNO(03231) "NoProxy for %s" : APLOGNO(03232) "UseProxy for %s",
                r->uri);
#endif

    do {
        char *url = uri;
        /* Try to obtain the most suitable worker */
