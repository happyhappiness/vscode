    if (f->c->aborted) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r, APLOGNO(01454) "rl: conn aborted");
        apr_brigade_cleanup(bb);
        return APR_ECONNABORTED;
    }

    if (ctx == NULL) {

        const char *rl = NULL;
        int ratelimit;

        /* no subrequests. */
        if (f->r->main != NULL) {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        rl = apr_table_get(f->r->subprocess_env, "rate-limit");

        if (rl == NULL) {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }
        
        /* rl is in kilo bytes / second  */
        ratelimit = atoi(rl) * 1024;
        if (ratelimit <= 0) {
            /* remove ourselves */
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        /* first run, init stuff */
        ctx = apr_palloc(f->r->pool, sizeof(rl_ctx_t));
        f->ctx = ctx;
        ctx->state = RATE_LIMIT;
        ctx->speed = ratelimit;

        /* calculate how many bytes / interval we want to send */
        /* speed is bytes / second, so, how many  (speed / 1000 % interval) */
        ctx->chunk_size = (ctx->speed / (1000 / RATE_INTERVAL_MS));
        ctx->tmpbb = apr_brigade_create(f->r->pool, ba);
        ctx->holdingbb = apr_brigade_create(f->r->pool, ba);
