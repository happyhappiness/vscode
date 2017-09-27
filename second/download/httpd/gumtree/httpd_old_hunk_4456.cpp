    /* In case anyone needs to know, this is a fake request that is really a
     * response.
     */
    backend->r->proxyreq = PROXYREQ_RESPONSE;
    apr_table_setn(r->notes, "proxy-source-port", apr_psprintf(r->pool, "%hu",
                   origin->local_addr->port));
    tmp_bb = apr_brigade_create(p, c->bucket_alloc);
    do {
        apr_status_t rc;

        apr_brigade_cleanup(bb);

        rc = ap_proxygetline(tmp_bb, buffer, sizeof(buffer), backend->r, 0, &len);
        if (len == 0) {
            /* handle one potential stray CRLF */
            rc = ap_proxygetline(tmp_bb, buffer, sizeof(buffer), backend->r, 0, &len);
        }
        if (len <= 0) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rc, r, APLOGNO(01102)
                          "error reading status line from remote "
                          "server %s:%d", backend->hostname, backend->port);
            if (APR_STATUS_IS_TIMEUP(rc)) {
