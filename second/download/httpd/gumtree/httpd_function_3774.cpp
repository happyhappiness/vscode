static apr_status_t substitute_filter(ap_filter_t *f, apr_bucket_brigade *bb)
{
    apr_size_t bytes;
    apr_size_t len;
    apr_size_t fbytes;
    const char *buff;
    const char *nl = NULL;
    char *bflat;
    apr_bucket *b;
    apr_bucket *tmp_b;
    apr_bucket_brigade *tmp_bb = NULL;
    apr_status_t rv;

    substitute_module_ctx *ctx = f->ctx;

    /*
     * First time around? Create the saved bb that we used for each pass
     * through. Note that we can also get here when we explicitly clear ctx,
     * for error handling
     */
    if (!ctx) {
        f->ctx = ctx = apr_pcalloc(f->r->pool, sizeof(*ctx));
        /*
         * Create all the temporary brigades we need and reuse them to avoid
         * creating them over and over again from r->pool which would cost a
         * lot of memory in some cases.
         */
        ctx->linebb = apr_brigade_create(f->r->pool, f->c->bucket_alloc);
        ctx->linesbb = apr_brigade_create(f->r->pool, f->c->bucket_alloc);
        ctx->pattbb = apr_brigade_create(f->r->pool, f->c->bucket_alloc);
        /*
         * Everything to be passed to the next filter goes in
         * here, our pass brigade.
         */
        ctx->passbb = apr_brigade_create(f->r->pool, f->c->bucket_alloc);
        /* Create our temporary pool only once */
        apr_pool_create(&(ctx->tpool), f->r->pool);
        apr_table_unset(f->r->headers_out, "Content-Length");
    }

    /*
     * Shortcircuit processing
     */
    if (APR_BRIGADE_EMPTY(bb))
        return APR_SUCCESS;

    /*
     * Here's the concept:
     *  Read in the data and look for newlines. Once we
     *  find a full "line", add it to our working brigade.
     *  If we've finished reading the brigade and we have
     *  any left over data (not a "full" line), store that
     *  for the next pass.
     *
     * Note: anything stored in ctx->linebb for sure does not have
     * a newline char, so we don't concat that bb with the
     * new bb, since we would spending time searching for the newline
     * in data we know it doesn't exist. So instead, we simply scan
     * our current bb and, if we see a newline, prepend ctx->linebb
     * to the front of it. This makes the code much less straight-
     * forward (otherwise we could APR_BRIGADE_CONCAT(ctx->linebb, bb)
     * and just scan for newlines and not bother with needing to know
     * when ctx->linebb needs to be reset) but also faster. We'll take
     * the speed.
     *
     * Note: apr_brigade_split_line would be nice here, but we
     * really can't use it since we need more control and we want
     * to re-use already read bucket data.
     *
     * See mod_include if still confused :)
     */

    while ((b = APR_BRIGADE_FIRST(bb)) && (b != APR_BRIGADE_SENTINEL(bb))) {
        if (APR_BUCKET_IS_EOS(b)) {
            /*
             * if we see the EOS, then we need to pass along everything we
             * have. But if the ctx->linebb isn't empty, then we need to add
             * that to the end of what we'll be passing.
             */
            if (!APR_BRIGADE_EMPTY(ctx->linebb)) {
                rv = apr_brigade_pflatten(ctx->linebb, &bflat,
                                          &fbytes, ctx->tpool);
                if (rv != APR_SUCCESS)
                    goto err;
                if (fbytes > AP_SUBST_MAX_LINE_LENGTH) {
                    rv = APR_ENOMEM;
                    goto err;
                }
                tmp_b = apr_bucket_transient_create(bflat, fbytes,
                                                f->r->connection->bucket_alloc);
                rv = do_pattmatch(f, tmp_b, ctx->pattbb, ctx->tpool);
                if (rv != APR_SUCCESS)
                    goto err;
                APR_BRIGADE_CONCAT(ctx->passbb, ctx->pattbb);
            }
            apr_brigade_cleanup(ctx->linebb);
            APR_BUCKET_REMOVE(b);
            APR_BRIGADE_INSERT_TAIL(ctx->passbb, b);
        }
        /*
         * No need to handle FLUSH buckets separately as we call
         * ap_pass_brigade anyway at the end of the loop.
         */
        else if (APR_BUCKET_IS_METADATA(b)) {
            APR_BUCKET_REMOVE(b);
            APR_BRIGADE_INSERT_TAIL(ctx->passbb, b);
        }
        else {
            /*
             * We have actual "data" so read in as much as we can and start
             * scanning and splitting from our read buffer
             */
            rv = apr_bucket_read(b, &buff, &bytes, APR_BLOCK_READ);
            if (rv != APR_SUCCESS || bytes == 0) {
                apr_bucket_delete(b);
            }
            else {
                int num = 0;
                while (bytes > 0) {
                    nl = memchr(buff, APR_ASCII_LF, bytes);
                    if (nl) {
                        len = (apr_size_t) (nl - buff) + 1;
                        /* split *after* the newline */
                        apr_bucket_split(b, len);
                        /*
                         * We've likely read more data, so bypass rereading
                         * bucket data and continue scanning through this
                         * buffer
                         */
                        bytes -= len;
                        buff += len;
                        /*
                         * we need b to be updated for future potential
                         * splitting
                         */
                        tmp_b = APR_BUCKET_NEXT(b);
                        APR_BUCKET_REMOVE(b);
                        /*
                         * Hey, we found a newline! Don't forget the old
                         * stuff that needs to be added to the front. So we
                         * add the split bucket to the end, flatten the whole
                         * bb, morph the whole shebang into a bucket which is
                         * then added to the tail of the newline bb.
                         */
                        if (!APR_BRIGADE_EMPTY(ctx->linebb)) {
                            APR_BRIGADE_INSERT_TAIL(ctx->linebb, b);
                            rv = apr_brigade_pflatten(ctx->linebb, &bflat,
                                                      &fbytes, ctx->tpool);
                            if (rv != APR_SUCCESS)
                                goto err;
                            if (fbytes > AP_SUBST_MAX_LINE_LENGTH) {
                                /* Avoid pflattening further lines, we will
                                 * abort later on anyway.
                                 */
                                rv = APR_ENOMEM;
                                goto err;
                            }
                            b = apr_bucket_transient_create(bflat, fbytes,
                                            f->r->connection->bucket_alloc);
                            apr_brigade_cleanup(ctx->linebb);
                        }
                        rv = do_pattmatch(f, b, ctx->pattbb, ctx->tpool);
                        if (rv != APR_SUCCESS)
                            goto err;
                        /*
                         * Count how many buckets we have in ctx->passbb
                         * so far. Yes, this is correct we count ctx->passbb
                         * and not ctx->pattbb as we do not reset num on every
                         * iteration.
                         */
                        for (b = APR_BRIGADE_FIRST(ctx->pattbb);
                             b != APR_BRIGADE_SENTINEL(ctx->pattbb);
                             b = APR_BUCKET_NEXT(b)) {
                            num++;
                        }
                        APR_BRIGADE_CONCAT(ctx->passbb, ctx->pattbb);
                        /*
                         * If the number of buckets in ctx->passbb reaches an
                         * "insane" level, we consume much memory for all the
                         * buckets as such. So lets flush them down the chain
                         * in this case and thus clear ctx->passbb. This frees
                         * the buckets memory for further processing.
                         * Usually this condition should not become true, but
                         * it is a safety measure for edge cases.
                         */
                        if (num > AP_MAX_BUCKETS) {
                            b = apr_bucket_flush_create(
                                                f->r->connection->bucket_alloc);
                            APR_BRIGADE_INSERT_TAIL(ctx->passbb, b);
                            rv = ap_pass_brigade(f->next, ctx->passbb);
                            apr_brigade_cleanup(ctx->passbb);
                            num = 0;
                            apr_pool_clear(ctx->tpool);
                            if (rv != APR_SUCCESS)
                                goto err;
                        }
                        b = tmp_b;
                    }
                    else {
                        /*
                         * no newline in whatever is left of this buffer so
                         * tuck data away and get next bucket
                         */
                        APR_BUCKET_REMOVE(b);
                        APR_BRIGADE_INSERT_TAIL(ctx->linebb, b);
                        bytes = 0;
                    }
                }
            }
        }
        if (!APR_BRIGADE_EMPTY(ctx->passbb)) {
            rv = ap_pass_brigade(f->next, ctx->passbb);
            apr_brigade_cleanup(ctx->passbb);
            if (rv != APR_SUCCESS)
                goto err;
        }
        apr_pool_clear(ctx->tpool);
    }

    /* Anything left we want to save/setaside for the next go-around */
    if (!APR_BRIGADE_EMPTY(ctx->linebb)) {
        /*
         * Provide ap_save_brigade with an existing empty brigade
         * (ctx->linesbb) to avoid creating a new one.
         */
        ap_save_brigade(f, &(ctx->linesbb), &(ctx->linebb), f->r->pool);
        tmp_bb = ctx->linebb;
        ctx->linebb = ctx->linesbb;
        ctx->linesbb = tmp_bb;
    }

    return APR_SUCCESS;
err:
    if (rv == APR_ENOMEM)
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r, APLOGNO(01328) "Line too long, URI %s",
                      f->r->uri);
    apr_pool_clear(ctx->tpool);
    return rv;
}