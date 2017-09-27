     */
    AP_PROCESS_REQUEST_ENTRY((uintptr_t)r, r->uri);
    if (ap_extended_status) {
        ap_time_process_request(r->connection->sbh, START_PREQUEST);
    }

    if (APLOGrtrace4(r)) {
        int i;
        const apr_array_header_t *t_h = apr_table_elts(r->headers_in);
        const apr_table_entry_t *t_elt = (apr_table_entry_t *)t_h->elts;
        ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r,
                      "Headers received from client:");
        for (i = 0; i < t_h->nelts; i++, t_elt++) {
            ap_log_rerror(APLOG_MARK, APLOG_TRACE4, 0, r, "  %s: %s",
                          ap_escape_logitem(r->pool, t_elt->key),
                          ap_escape_logitem(r->pool, t_elt->val));
        }
    }

#if APR_HAS_THREADS
    apr_thread_mutex_create(&r->invoke_mtx, APR_THREAD_MUTEX_DEFAULT, r->pool);
    apr_thread_mutex_lock(r->invoke_mtx);
#endif
    access_status = ap_run_quick_handler(r, 0);  /* Not a look-up request */
    if (access_status == DECLINED) {
