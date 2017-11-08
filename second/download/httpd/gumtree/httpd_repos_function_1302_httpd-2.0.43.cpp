static apr_bucket *find_end_sequence(apr_bucket *dptr, include_ctx_t *ctx, 
                                     apr_bucket_brigade *bb)
{
    apr_size_t len;
    const char *c;
    const char *buf;
    const char *str = ctx->end_seq;
    const char *start;

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
            if (ctx->state == PARSE_DIRECTIVE) {
                /* gonna start over parsing the directive next time through */
                ctx->directive_length = 0;
                ctx->tag_length       = 0;
            }
            return dptr;
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
        if (dptr == ctx->tag_start_bucket) {
            c = buf + ctx->tag_start_index;
        }
        else {
            c = buf;
        }
        start = c;
        while (c < buf + len) {
            if (*c == str[ctx->parse_pos]) {
                if (ctx->state != PARSE_TAIL) {
                    ctx->state             = PARSE_TAIL;
                    ctx->tail_start_bucket = dptr;
                    ctx->tail_start_index  = c - buf;
                }
                ctx->parse_pos++;
                if (str[ctx->parse_pos] == '\0') {
                        apr_bucket *tmp_buck = dptr;

                        /* We want to split the bucket at the '>'. The
                         * end of the END_SEQUENCE is in the current bucket.
                         * The beginning might be in a previous bucket.
                         */
                        c++;
                        ctx->bytes_parsed += (c - start);
                        ctx->state = PARSED;
                        apr_bucket_split(dptr, c - buf);
                        tmp_buck = APR_BUCKET_NEXT(dptr);
                        return (tmp_buck);
                    }           
            }
            else {
                if (ctx->state == PARSE_DIRECTIVE) {
                    if (ctx->tag_length == 0) {
                        if (!apr_isspace(*c)) {
                            const char *tmp = c;
                            ctx->tag_start_bucket = dptr;
                            ctx->tag_start_index  = c - buf;
                            do {
                                c++;
                            } while ((c < buf + len) && !apr_isspace(*c) &&
                                     *c != *str);
                            ctx->tag_length = ctx->directive_length = c - tmp;
                            continue;
                        }
                    }
                    else {
                        if (!apr_isspace(*c)) {
                            ctx->directive_length++;
                        }
                        else {
                            ctx->state = PARSE_TAG;
                        }
                        ctx->tag_length++;
                    }
                }
                else if (ctx->state == PARSE_TAG) {
                    const char *tmp = c;
                    do {
                        c++;
                    } while ((c < buf + len) && (*c != *str));
                    ctx->tag_length += (c - tmp);
                    continue;
                }
                else {
                    if (ctx->parse_pos != 0) {
                        /* The reason for this, is that we need to make sure 
                         * that we catch cases like --->.  This makes the 
                         * second check after the original check fails.
                         * If parse_pos was already 0 then we already checked 
                         * this.
                         */
                         ctx->tag_length += ctx->parse_pos;

                         if (*c == str[0]) {
                             ctx->state = PARSE_TAIL;
                             ctx->tail_start_bucket = dptr;
                             ctx->tail_start_index = c - buf;
                             ctx->parse_pos = 1;
                         }
                         else {
                             ctx->tag_length++;
                             if (ctx->tag_length > ctx->directive_length) {
                                 ctx->state = PARSE_TAG;
                             }
                             else {
                                 ctx->state = PARSE_DIRECTIVE;
                                 ctx->directive_length += ctx->parse_pos;
                             }
                             ctx->tail_start_bucket = NULL;
                             ctx->tail_start_index = 0;
                             ctx->parse_pos = 0;
                         }
                    }
                }
            }
            c++;
        }
        ctx->bytes_parsed += (c - start);
        dptr = APR_BUCKET_NEXT(dptr);
    } while (dptr != APR_BRIGADE_SENTINEL(bb));
    return NULL;
}