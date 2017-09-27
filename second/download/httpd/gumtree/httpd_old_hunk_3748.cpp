    }
    else {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02450) "declining URL %s", url);
        return DECLINED;
    }

    uri = apr_palloc(p, sizeof(*uri));
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(02451) "serving URL %s", url);

    /* create space for state information */
    status = ap_proxy_acquire_connection(scheme, &backend, worker,
                                         r->server);
