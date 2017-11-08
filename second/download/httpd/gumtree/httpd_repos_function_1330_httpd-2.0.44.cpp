static apr_bucket *find_start_sequence(apr_bucket *dptr, include_ctx_t *ctx,
                                       apr_bucket_brigade *bb, int *do_cleanup)
{
    apr_size_t len;
    const char *c;
    const char *buf;
    const char *str = ctx->start_seq ;
    apr_size_t slen = ctx->start_seq_len;
    apr_size_t pos;

    *do_cleanup = 0;

    do {
        apr_status_t rv = 0;
        int read_done = 0;

        if (APR_BUCKET_IS_EOS(dptr)) {
            break;
        }

#if 0
        /* XXX the bucket flush support is commented out for now
         * because it was causing a segfault */
        if (APR_BUCKET_IS_FLUSH(dptr)) {
            apr_bucket *old = dptr; 
            dptr = APR_BUCKET_NEXT(old);
            APR_BUCKET_REMOVE(old);
            ctx->output_now = 1;
            ctx->output_flush = 1;
        }
        else
#endif /* 0 */
        if (ctx->bytes_parsed >= BYTE_COUNT_THRESHOLD) {
            ctx->output_now = 1;
        }
        else if (ctx->bytes_parsed > 0) {
            rv = apr_bucket_read(dptr, &buf, &len, APR_NONBLOCK_READ);
            read_done = 1;
            if (APR_STATUS_IS_EAGAIN(rv)) {
                ctx->output_now = 1;
            }
        }

        if (ctx->output_now) {
            apr_bucket *start_bucket;
            if (ctx->head_start_index > 0) {
                start_bucket = ctx->head_start_bucket;
                apr_bucket_split(start_bucket, ctx->head_start_index);
                start_bucket = APR_BUCKET_NEXT(start_bucket);
                ctx->head_start_index = 0;
                ctx->head_start_bucket = start_bucket;
                ctx->parse_pos = 0;
                ctx->state = PRE_HEAD;
            }
            else {
                start_bucket = dptr;
            }
            return start_bucket;
        }

        if (!read_done) {
            rv = apr_bucket_read(dptr, &buf, &len, APR_BLOCK_READ);
        }
        if (!APR_STATUS_IS_SUCCESS(rv)) {
            ctx->status = rv;
            return NULL;
        }

        if (len == 0) { /* end of pipe? */
            break;
        }

        /* Set our buffer to use. */
        c = buf;

        /* The last bucket had a left over partial match that we need to
         * complete. 
         */
        if (ctx->state == PARSE_HEAD)
        {
            apr_size_t tmpLen;
            tmpLen = (len < (slen - 1)) ? len : (slen - 1);

            while (c < buf + tmpLen && *c == str[ctx->parse_pos])
            {
                c++; 
                ctx->parse_pos++;
            }

            if (str[ctx->parse_pos] == '\0')
            {
                ctx->bytes_parsed += c - buf;
                return found_start_sequence(dptr, ctx, c - buf, len);
            }
            else if (c == buf + tmpLen) {
                dptr = APR_BUCKET_NEXT(dptr);
                continue;
            }

            /* False alarm... 
             */
            APR_BRIGADE_PREPEND(bb, ctx->ssi_tag_brigade);

            /* We know we are at the beginning of this bucket so
             *   we can just prepend the saved bytes from the
             *   ssi_tag_brigade (which empties the ssi_tag_brigade)
             *   and continue processing.
             * We do not need to set do_cleanup beacuse the
             *   prepend takes care of that.
             */
            ctx->state = PRE_HEAD;
            ctx->head_start_bucket = NULL;
            ctx->head_start_index = 0;
        }

        if (len)
        {
            pos = bndm(str, slen, c, len, ctx->start_seq_pat);
            if (pos != len)
            {
                ctx->head_start_bucket = dptr;
                ctx->head_start_index = pos;
                ctx->bytes_parsed += pos + slen;
                return found_start_sequence(dptr, ctx, pos + slen, len);
            }
        }
        
        /* Consider the case where we have <!-- at the end of the bucket. */
        if (len > slen) {
            ctx->bytes_parsed += (len - slen);
            c = buf + len - slen;
        }
        else {
            c = buf;
        }
        ctx->parse_pos = 0;

        while (c < buf + len)
        {
            if (*c == str[ctx->parse_pos]) {
                if (ctx->state == PRE_HEAD) {
                    ctx->state = PARSE_HEAD;
                    ctx->head_start_bucket = dptr;
                    ctx->head_start_index = c - buf;
                }
                ctx->parse_pos++;
                c++;
                ctx->bytes_parsed++;
            }
            else if (ctx->parse_pos != 0) 
            {
                /* DO NOT INCREMENT c IN THIS BLOCK!
                 * Don't increment bytes_parsed either.
                 * This block is just to reset the indexes and
                 *   pointers related to parsing the tag start_sequence.
                 * The value c needs to be checked again to handle
                 *   the case where we find "<<!--#". We are now
                 *   looking at the second "<" and need to restart
                 *   the start_sequence checking from parse_pos = 0.
                 * do_cleanup causes the stored bytes in ssi_tag_brigade
                 *   to be forwarded on and cleaned up. We may not be
                 *   able to just prepend the ssi_tag_brigade because
                 *   we may have advanced too far before we noticed this
                 *   case, so just flag it and clean it up later.
                 */
                *do_cleanup = 1;
                ctx->parse_pos = 0;
                ctx->state = PRE_HEAD;
                ctx->head_start_bucket = NULL;
                ctx->head_start_index = 0;
            }
            else {
               c++;
               ctx->bytes_parsed++;
            }
        }
        dptr = APR_BUCKET_NEXT(dptr);
    } while (dptr != APR_BRIGADE_SENTINEL(bb));
          
  
    return NULL;
}