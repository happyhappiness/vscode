static apr_status_t xlate_out_filter(ap_filter_t *f, apr_bucket_brigade *bb)
{
    charset_req_t *reqinfo = ap_get_module_config(f->r->request_config,
                                                  &charset_lite_module);
    charset_dir_t *dc = ap_get_module_config(f->r->per_dir_config,
                                             &charset_lite_module);
    charset_filter_ctx_t *ctx = f->ctx;
    apr_bucket *dptr, *consumed_bucket;
    const char *cur_str;
    apr_size_t cur_len, cur_avail;
    char tmp[OUTPUT_XLATE_BUF_SIZE];
    apr_size_t space_avail;
    int done;
    apr_status_t rv = APR_SUCCESS;

    if (!ctx) {
        /* this is SetOutputFilter path; grab the preallocated context,
         * if any; note that if we decided not to do anything in an earlier
         * handler, we won't even have a reqinfo
         */
        if (reqinfo) {
            ctx = f->ctx = reqinfo->output_ctx;
            reqinfo->output_ctx = NULL; /* prevent SNAFU if user coded us twice
                                         * in the filter chain; we can't have two
                                         * instances using the same context
                                         */
        }
        if (!ctx) {                   /* no idea how to translate; don't do anything */
            ctx = f->ctx = apr_pcalloc(f->r->pool, sizeof(charset_filter_ctx_t));
            ctx->dc = dc;
            ctx->noop = 1;
        }
    }

    /* Check the mime type to see if translation should be performed.
     */
    if (!ctx->noop && ctx->xlate == NULL) {
        const char *mime_type = f->r->content_type;

        if (mime_type && (strncasecmp(mime_type, "text/", 5) == 0 ||
#if APR_CHARSET_EBCDIC
        /* On an EBCDIC machine, be willing to translate mod_autoindex-
         * generated output.  Otherwise, it doesn't look too cool.
         *
         * XXX This isn't a perfect fix because this doesn't trigger us
         * to convert from the charset of the source code to ASCII.  The
         * general solution seems to be to allow a generator to set an
         * indicator in the r specifying that the body is coded in the
         * implementation character set (i.e., the charset of the source
         * code).  This would get several different types of documents
         * translated properly: mod_autoindex output, mod_status output,
         * mod_info output, hard-coded error documents, etc.
         */
            strcmp(mime_type, DIR_MAGIC_TYPE) == 0 ||
#endif
            strncasecmp(mime_type, "message/", 8) == 0 || 
            dc->force_xlate == FX_FORCE)) {

            rv = apr_xlate_open(&ctx->xlate,
                                dc->charset_default, dc->charset_source, f->r->pool);
            if (rv != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r,
                              "can't open translation %s->%s",
                              dc->charset_source, dc->charset_default);
                ctx->noop = 1;
            }
            else {
                if (apr_xlate_sb_get(ctx->xlate, &ctx->is_sb) != APR_SUCCESS) {
                    ctx->is_sb = 0;
                }
            }
        }
        else {
            ctx->noop = 1;
            if (mime_type && dc->debug >= DBGLVL_GORY) {
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
                              "mime type is %s; no translation selected",
                              mime_type);
            }
        }
    }

    if (dc->debug >= DBGLVL_GORY) {
        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r,
                      "xlate_out_filter() - "
                      "charset_source: %s charset_default: %s",
                      dc && dc->charset_source ? dc->charset_source : "(none)",
                      dc && dc->charset_default ? dc->charset_default : "(none)");
    }

    if (!ctx->ran) {  /* filter never ran before */
        chk_filter_chain(f);
        ctx->ran = 1;
        if (!ctx->noop && !ctx->is_sb) {
            /* We're not converting between two single-byte charsets, so unset
             * Content-Length since it is unlikely to remain the same.
             */
            apr_table_unset(f->r->headers_out, "Content-Length");
        }
    }

    if (ctx->noop) {
        return ap_pass_brigade(f->next, bb);
    }

    dptr = APR_BRIGADE_FIRST(bb);
    done = 0;
    cur_len = 0;
    space_avail = sizeof(tmp);
    consumed_bucket = NULL;
    while (!done) {
        if (!cur_len) { /* no bytes left to process in the current bucket... */
            if (consumed_bucket) {
                apr_bucket_delete(consumed_bucket);
                consumed_bucket = NULL;
            }
            if (dptr == APR_BRIGADE_SENTINEL(bb)) {
                done = 1;
                break;
            }
            if (APR_BUCKET_IS_EOS(dptr)) {
                done = 1;
                cur_len = -1; /* XXX yuck, but that tells us to send
                                 * eos down; when we minimize our bb construction
                                 * we'll fix this crap */
                if (ctx->saved) {
                    /* Oops... we have a partial char from the previous bucket
                     * that won't be completed because there's no more data.
                     */
                    rv = APR_INCOMPLETE;
                    ctx->ees = EES_INCOMPLETE_CHAR;
                }
                break;
            }
            if (APR_BUCKET_IS_METADATA(dptr)) {
                apr_bucket *metadata_bucket;
                metadata_bucket = dptr;
                dptr = APR_BUCKET_NEXT(dptr);
                APR_BUCKET_REMOVE(metadata_bucket);
                rv = send_bucket_downstream(f, metadata_bucket);
                if (rv != APR_SUCCESS) {
                    done = 1;
                }
                continue;
            }
            rv = apr_bucket_read(dptr, &cur_str, &cur_len, APR_BLOCK_READ);
            if (rv != APR_SUCCESS) {
                done = 1;
                ctx->ees = EES_BUCKET_READ;
                break;
            }
            consumed_bucket = dptr; /* for axing when we're done reading it */
            dptr = APR_BUCKET_NEXT(dptr); /* get ready for when we access the
                                          * next bucket */
        }
        /* Try to fill up our tmp buffer with translated data. */
        cur_avail = cur_len;

        if (cur_len) { /* maybe we just hit the end of a pipe (len = 0) ? */
            if (ctx->saved) {
                /* Rats... we need to finish a partial character from the previous
                 * bucket.
                 */
                char *tmp_tmp;

                tmp_tmp = tmp + sizeof(tmp) - space_avail;
                rv = finish_partial_char(ctx,
                                         &cur_str, &cur_len,
                                         &tmp_tmp, &space_avail);
            }
            else {
                rv = apr_xlate_conv_buffer(ctx->xlate,
                                           cur_str, &cur_avail,
                                           tmp + sizeof(tmp) - space_avail, &space_avail);

                /* Update input ptr and len after consuming some bytes */
                cur_str += cur_len - cur_avail;
                cur_len = cur_avail;

                if (rv == APR_INCOMPLETE) { /* partial character at end of input */
                    /* We need to save the final byte(s) for next time; we can't
                     * convert it until we look at the next bucket.
                     */
                    rv = set_aside_partial_char(ctx, cur_str, cur_len);
                    cur_len = 0;
                }
            }
        }

        if (rv != APR_SUCCESS) {
            /* bad input byte or partial char too big to store */
            done = 1;
        }

        if (space_avail < XLATE_MIN_BUFF_LEFT) {
            /* It is time to flush, as there is not enough space left in the
             * current output buffer to bother with converting more data.
             */
            rv = send_downstream(f, tmp, sizeof(tmp) - space_avail);
            if (rv != APR_SUCCESS) {
                done = 1;
            }

            /* tmp is now empty */
            space_avail = sizeof(tmp);
        }
    }

    if (rv == APR_SUCCESS) {
        if (space_avail < sizeof(tmp)) { /* gotta write out what we converted */
            rv = send_downstream(f, tmp, sizeof(tmp) - space_avail);
        }
    }
    if (rv == APR_SUCCESS) {
        if (cur_len == -1) {
            rv = send_eos(f);
        }
    }
    else {
        log_xlate_error(f, rv);
    }

    return rv;
}