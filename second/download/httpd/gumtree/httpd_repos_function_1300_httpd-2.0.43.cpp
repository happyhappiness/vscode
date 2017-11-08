static apr_bucket* found_start_sequence(apr_bucket *dptr,
                                        include_ctx_t *ctx, 
                                        apr_size_t tagStart,
                                        apr_size_t len)
{
    /* We want to split the bucket at the '<'. */
    ctx->state = PARSE_DIRECTIVE;
    ctx->tag_length = 0;
    ctx->parse_pos = 0;

    /* If tagStart indexes the end of the bucket, then tag_start_bucket
     * should be the next bucket
     */
    if (tagStart < len) {
        ctx->tag_start_bucket = dptr;
        ctx->tag_start_index = tagStart;
    }
    else {
        ctx->tag_start_bucket = APR_BUCKET_NEXT(dptr);
        ctx->tag_start_index = 0;
    }

    if (ctx->head_start_index > 0) {
        apr_bucket *tmp_bkt;

        /* Split the bucket with the start of the tag in it */
        apr_bucket_split(ctx->head_start_bucket, ctx->head_start_index);
        tmp_bkt = APR_BUCKET_NEXT(ctx->head_start_bucket);
        /* If it was a one bucket match */
        if ((tagStart < len) && (dptr == ctx->head_start_bucket)) {
            ctx->tag_start_bucket = tmp_bkt;
            ctx->tag_start_index = tagStart - ctx->head_start_index;
        }
        ctx->head_start_bucket = tmp_bkt;
        ctx->head_start_index = 0;
    }
    return ctx->head_start_bucket;
}