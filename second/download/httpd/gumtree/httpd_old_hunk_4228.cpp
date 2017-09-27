    /* slave connection? */
    if (r->connection->master) {
        h2_ctx *ctx = h2_ctx_rget(r);
        struct h2_task *task = h2_ctx_get_task(ctx);
        /* This hook will get called twice on internal redirects. Take care
         * that we manipulate filters only once. */
        /* our slave connection? */
        if (task && !task->filters_set) {
            ap_filter_t *f;
            
            /* setup the correct output filters to process the response
             * on the proper mod_http2 way. */
            ap_log_rerror(APLOG_MARK, APLOG_TRACE3, 0, r, "adding task output filter");
