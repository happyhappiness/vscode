    if (f->c->aborted) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r, APLOGNO(01454) "rl: conn aborted");
        apr_brigade_cleanup(bb);
        return APR_ECONNABORTED;
    }

    /* Set up our rl_ctx_t on first use */
    if (ctx == NULL) {

        const char *rl = NULL;
        int ratelimit;
        int burst = 0;

        /* no subrequests. */
        if (f->r->main != NULL) {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        /* Configuration: rate limit */
        rl = apr_table_get(f->r->subprocess_env, "rate-limit");

        if (rl == NULL) {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }
        
        /* rl is in kilo bytes / second  */
        ratelimit = atoi(rl) * 1024;
        if (ratelimit <= 0) {
            /* remove ourselves */
            ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r,
                          APLOGNO(03488) "rl: disabling: rate-limit = %s (too high?)", rl);
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        /* Configuration: optional initial burst */
        rl = apr_table_get(f->r->subprocess_env, "rate-initial-burst");
        if (rl != NULL) {
            burst = atoi(rl) * 1024;
            if (burst <= 0) {
               ap_log_rerror(APLOG_MARK, APLOG_INFO, 0, f->r,
                             APLOGNO(03489) "rl: disabling burst: rate-initial-burst = %s (too high?)", rl);
               burst = 0;
            }
        }

        /* Set up our context */
        ctx = apr_palloc(f->r->pool, sizeof(rl_ctx_t));
        f->ctx = ctx;
        ctx->state = RATE_LIMIT;
        ctx->speed = ratelimit;
        ctx->burst = burst;

        /* calculate how many bytes / interval we want to send */
        /* speed is bytes / second, so, how many  (speed / 1000 % interval) */
        ctx->chunk_size = (ctx->speed / (1000 / RATE_INTERVAL_MS));
        ctx->tmpbb = apr_brigade_create(f->r->pool, ba);
        ctx->holdingbb = apr_brigade_create(f->r->pool, ba);
