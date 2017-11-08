static apr_status_t get_combined_directive (include_ctx_t *ctx,
                                            request_rec *r,
                                            apr_bucket_brigade *bb,
                                            char *tmp_buf, 
                                            apr_size_t tmp_buf_size)
{
    int        done = 0;
    apr_bucket *dptr;
    const char *tmp_from;
    apr_size_t tmp_from_len;

    /* If the tag length is longer than the tmp buffer, allocate space. */
    if (ctx->tag_length > tmp_buf_size-1) {
        if ((ctx->combined_tag = apr_pcalloc(r->pool, 
             ctx->tag_length + 1)) == NULL) {
            return (APR_ENOMEM);
        }
    }     /* Else, just use the temp buffer. */
    else {
        ctx->combined_tag = tmp_buf;
    }

    /* Prime the pump. Start at the beginning of the tag... */
    dptr = ctx->tag_start_bucket;
    /* Read the bucket... */
    apr_bucket_read (dptr, &tmp_from, &tmp_from_len, 0);

    /* Adjust the pointer to start at the tag within the bucket... */
    if (dptr == ctx->tail_start_bucket) {
        tmp_from_len -= (tmp_from_len - ctx->tail_start_index);
    }
    tmp_from          = &tmp_from[ctx->tag_start_index];
    tmp_from_len     -= ctx->tag_start_index;
    ctx->curr_tag_pos = ctx->combined_tag;

    /* Loop through the buckets from the tag_start_bucket until before
     * the tail_start_bucket copying the contents into the buffer.
     */
    do {
        memcpy (ctx->curr_tag_pos, tmp_from, tmp_from_len);
        ctx->curr_tag_pos += tmp_from_len;

        if (dptr == ctx->tail_start_bucket) {
            done = 1;
        }
        else {
            dptr = APR_BUCKET_NEXT (dptr);
            apr_bucket_read (dptr, &tmp_from, &tmp_from_len, 0);
            /* Adjust the count to stop at the beginning of the tail. */
            if (dptr == ctx->tail_start_bucket) {
                tmp_from_len -= (tmp_from_len - ctx->tail_start_index);
            }
        }
    } while ((!done) &&
             (ctx->curr_tag_pos < ctx->combined_tag + ctx->tag_length));

    ctx->combined_tag[ctx->tag_length] = '\0';
    ctx->curr_tag_pos = ctx->combined_tag;

    return (APR_SUCCESS);
}