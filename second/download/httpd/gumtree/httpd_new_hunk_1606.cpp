     * content handlers that have the ability to grok HTTP and do their
     * own access checking, etc (e.g. servlet engines).
     *
     * Use this hook with extreme care and only if you know what you are
     * doing.
     */
    AP_PROCESS_REQUEST_ENTRY((uintptr_t)r, r->uri);
    if (ap_extended_status) {
        ap_time_process_request(r->connection->sbh, START_PREQUEST);
    }

#if APR_HAS_THREADS
    apr_thread_mutex_create(&r->invoke_mtx, APR_THREAD_MUTEX_DEFAULT, r->pool);
    apr_thread_mutex_lock(r->invoke_mtx);
#endif
    access_status = ap_run_quick_handler(r, 0);  /* Not a look-up request */
    if (access_status == DECLINED) {
        access_status = ap_process_request_internal(r);
        if (access_status == OK) {
            access_status = ap_invoke_handler(r);
        }
    }

    if (access_status == SUSPENDED) {
        /* TODO: Should move these steps into a generic function, so modules
         * working on a suspended request can also call _ENTRY again.
         */
        AP_PROCESS_REQUEST_RETURN((uintptr_t)r, r->uri, access_status);
        if (ap_extended_status) {
            ap_time_process_request(c->sbh, STOP_PREQUEST);
        }
        c->cs->state = CONN_STATE_SUSPENDED;
#if APR_HAS_THREADS
        apr_thread_mutex_unlock(r->invoke_mtx);
#endif
        return;
    }
#if APR_HAS_THREADS
    apr_thread_mutex_unlock(r->invoke_mtx);
#endif

    if (access_status == DONE) {
        /* e.g., something not in storage like TRACE */
        access_status = OK;
    }

    if (access_status == OK) {
        ap_finalize_request_protocol(r);
    }
    else {
        r->status = HTTP_OK;
        ap_die(access_status, r);
    }

    ap_process_request_after_handler(r);
}

void ap_process_request(request_rec *r)
{
    apr_bucket_brigade *bb;
    apr_bucket *b;
    conn_rec *c = r->connection;
    apr_status_t rv;

    ap_process_async_request(r);

    if (!c->data_in_input_filters) {
        bb = apr_brigade_create(c->pool, c->bucket_alloc);
        b = apr_bucket_flush_create(c->bucket_alloc);
        APR_BRIGADE_INSERT_HEAD(bb, b);
        rv = ap_pass_brigade(c->output_filters, bb);
        if (APR_STATUS_IS_TIMEUP(rv)) {
            /*
             * Notice a timeout as an error message. This might be
             * valuable for detecting clients with broken network
             * connections or possible DoS attacks.
             *
             * It is still save to use r / r->pool here as the eor bucket
             * could not have been destroyed in the event of a timeout.
             */
            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
                          "Timeout while writing data for URI %s to the"
                          " client", r->unparsed_uri);
        }
    }
    if (ap_extended_status) {
        ap_time_process_request(c->sbh, STOP_PREQUEST);
    }
}

static apr_table_t *rename_original_env(apr_pool_t *p, apr_table_t *t)
{
    const apr_array_header_t *env_arr = apr_table_elts(t);
    const apr_table_entry_t *elts = (const apr_table_entry_t *) env_arr->elts;
