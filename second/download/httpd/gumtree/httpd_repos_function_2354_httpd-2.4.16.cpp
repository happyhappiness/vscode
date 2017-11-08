static apr_status_t buffer_out_filter(ap_filter_t *f, apr_bucket_brigade *bb) {
    apr_bucket *e;
    request_rec *r = f->r;
    buffer_ctx *ctx = f->ctx;
    apr_status_t rv = APR_SUCCESS;
    int move = 0;

    /* first time in? create a context */
    if (!ctx) {

        /* buffering won't work on subrequests, it would be nice if
         * it did. Within subrequests, we have no EOS to check for,
         * so we don't know when to flush the buffer to the network
         */
        if (f->r->main) {
            ap_remove_output_filter(f);
            return ap_pass_brigade(f->next, bb);
        }

        ctx = f->ctx = apr_pcalloc(r->pool, sizeof(*ctx));
        ctx->bb = apr_brigade_create(r->pool, f->c->bucket_alloc);
        ctx->conf = ap_get_module_config(f->r->per_dir_config, &buffer_module);

    }

    /* Do nothing if asked to filter nothing. */
    if (APR_BRIGADE_EMPTY(bb)) {
        return ap_pass_brigade(f->next, bb);
    }

    /* Empty buffer means we can potentially optimise below */
    if (APR_BRIGADE_EMPTY(ctx->bb)) {
        move = 1;
    }

    while (APR_SUCCESS == rv && !APR_BRIGADE_EMPTY(bb)) {
        const char *data;
        apr_off_t len;
        apr_size_t size;

        e = APR_BRIGADE_FIRST(bb);

        /* EOS means we are done. */
        if (APR_BUCKET_IS_EOS(e)) {

            /* should we add an etag? */

            /* pass the EOS across */
            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, e);

            /* pass what we have down the chain */
            rv = ap_pass_brigade(f->next, ctx->bb);
            continue;
        }

        /* A flush takes precedence over buffering */
        if (APR_BUCKET_IS_FLUSH(e)) {

            /* pass the flush bucket across */
            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, e);

            /* pass what we have down the chain */
            rv = ap_pass_brigade(f->next, ctx->bb);
            continue;
        }

        /* metadata buckets are preserved as is */
        if (APR_BUCKET_IS_METADATA(e)) {
            /*
             * Remove meta data bucket from old brigade and insert into the
             * new.
             */
            APR_BUCKET_REMOVE(e);
            APR_BRIGADE_INSERT_TAIL(ctx->bb, e);
            continue;
        }

        /* is our buffer full?
         * If so, send what we have down the filter chain. If the buffer
         * gets full, we can no longer compute a content length.
         */
        apr_brigade_length(ctx->bb, 1, &len);
        if (len > ctx->conf->size) {

            /* pass what we have down the chain */
            rv = ap_pass_brigade(f->next, ctx->bb);
            if (rv) {
                /* should break out of the loop, since our write to the client
                 * failed in some way. */
                continue;
            }
        }

        /* at this point we are ready to buffer.
         * Buffering takes advantage of an optimisation in the handling of
         * bucket brigades. Heap buckets are always created at a fixed
         * size, regardless of the size of the data placed into them.
         * The apr_brigade_write() call will first try and pack the data
         * into any free space in the most recent heap bucket, before
         * allocating a new bucket if necessary.
         */
        if (APR_SUCCESS == (rv = apr_bucket_read(e, &data, &size,
                APR_BLOCK_READ))) {

            /* further optimisation: if the buckets are already heap
             * buckets, and the buckets stay exactly APR_BUCKET_BUFF_SIZE
             * long (as they would be if we were reading bits of a
             * large bucket), then move the buckets instead of copying
             * them.
             */
            if (move && APR_BUCKET_IS_HEAP(e)) {
                APR_BUCKET_REMOVE(e);
                APR_BRIGADE_INSERT_TAIL(ctx->bb, e);
                if (APR_BUCKET_BUFF_SIZE != size) {
                    move = 0;
                }
            } else {
                apr_brigade_write(ctx->bb, NULL, NULL, data,