static apr_status_t
rate_limit_filter(ap_filter_t *f, apr_bucket_brigade *input_bb)
{
    apr_status_t rv = APR_SUCCESS;
    rl_ctx_t *ctx = f->ctx;
    apr_bucket *fb;
    int do_sleep = 0;
    apr_bucket_alloc_t *ba = f->r->connection->bucket_alloc;
    apr_bucket_brigade *bb = input_bb;

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
    }

    while (ctx->state != RATE_ERROR &&
           (!APR_BRIGADE_EMPTY(bb) || !APR_BRIGADE_EMPTY(ctx->holdingbb))) {
        apr_bucket *e;

        if (!APR_BRIGADE_EMPTY(ctx->holdingbb)) {
            APR_BRIGADE_CONCAT(bb, ctx->holdingbb);
            apr_brigade_cleanup(ctx->holdingbb);
        }

        while (ctx->state == RATE_FULLSPEED && !APR_BRIGADE_EMPTY(bb)) {
            /* Find where we 'stop' going full speed. */
            for (e = APR_BRIGADE_FIRST(bb);
                 e != APR_BRIGADE_SENTINEL(bb); e = APR_BUCKET_NEXT(e)) {
                if (AP_RL_BUCKET_IS_END(e)) {
                    apr_bucket *f;
                    f = APR_RING_LAST(&bb->list);
                    APR_RING_UNSPLICE(e, f, link);
                    APR_RING_SPLICE_TAIL(&ctx->holdingbb->list, e, f,
                                         apr_bucket, link);
                    ctx->state = RATE_LIMIT;
                    break;
                }
            }

            if (f->c->aborted) {
                apr_brigade_cleanup(bb);
                ctx->state = RATE_ERROR;
                break;
            }

            fb = apr_bucket_flush_create(ba);
            APR_BRIGADE_INSERT_TAIL(bb, fb);
            rv = ap_pass_brigade(f->next, bb);

            if (rv != APR_SUCCESS) {
                ctx->state = RATE_ERROR;
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, APLOGNO(01455)
                              "rl: full speed brigade pass failed.");
            }
        }

        while (ctx->state == RATE_LIMIT && !APR_BRIGADE_EMPTY(bb)) {
            for (e = APR_BRIGADE_FIRST(bb);
                 e != APR_BRIGADE_SENTINEL(bb); e = APR_BUCKET_NEXT(e)) {
                if (AP_RL_BUCKET_IS_START(e)) {
                    apr_bucket *f;
                    f = APR_RING_LAST(&bb->list);
                    APR_RING_UNSPLICE(e, f, link);
                    APR_RING_SPLICE_TAIL(&ctx->holdingbb->list, e, f,
                                         apr_bucket, link);
                    ctx->state = RATE_FULLSPEED;
                    break;
                }
            }

            while (!APR_BRIGADE_EMPTY(bb)) {
                apr_bucket *stop_point;
                apr_off_t len = 0;

                if (f->c->aborted) {
                    apr_brigade_cleanup(bb);
                    ctx->state = RATE_ERROR;
                    break;
               