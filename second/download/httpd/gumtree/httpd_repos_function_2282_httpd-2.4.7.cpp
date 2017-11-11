static apr_status_t xml2enc_ffunc(ap_filter_t* f, apr_bucket_brigade* bb)
{
    xml2ctx* ctx = f->ctx;
    apr_status_t rv;
    apr_bucket* b;
    apr_bucket* bstart;
    apr_size_t insz = 0;
    char *ctype;
    char *p;

    if (!ctx || !f->r->content_type) {
        /* log error about configuring this */
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, bb) ;
    }

    ctype = apr_pstrdup(f->r->pool, f->r->content_type);
    for (p = ctype; *p; ++p)
        if (isupper(*p))
            *p = tolower(*p);

    /* only act if starts-with "text/" or contains "xml" */
    if (strncmp(ctype, "text/", 5) && !strstr(ctype, "xml"))  {
        ap_remove_output_filter(f);
        return ap_pass_brigade(f->next, bb) ;
    }

    if (ctx->bbsave == NULL) {
        ctx->bbsave = apr_brigade_create(f->r->pool,
                                         f->r->connection->bucket_alloc);
    }
    /* append to any data left over from last time */
    APR_BRIGADE_CONCAT(ctx->bbsave, bb);

    if (!(ctx->flags & ENC_INITIALISED)) {
        /* some kind of initialisation required */
        /* Turn all this off when post-processing */

        /* if we don't have enough data to sniff but more's to come, wait */
        apr_brigade_length(ctx->bbsave, 0, &ctx->bblen);
        if ((ctx->bblen < BUF_MIN) && (ctx->bblen != -1)) {
            APR_BRIGADE_DO(b, ctx->bbsave) {
                if (APR_BUCKET_IS_EOS(b)) {
                    ctx->flags |= ENC_SEEN_EOS;
                    break;
                }
            }
            if (!(ctx->flags & ENC_SEEN_EOS)) {
                /* not enough data to sniff.  Wait for more */
                APR_BRIGADE_DO(b, ctx->bbsave) {
                    rv = apr_bucket_setaside(b, f->r->pool);
                    ap_assert(rv == APR_SUCCESS);
                }
                return APR_SUCCESS;
            }
        }
        if (ctx->bblen == -1) {
            ctx->bblen = BUFLEN-1;
        }

        /* flatten it into a NULL-terminated string */
        ctx->buf = apr_palloc(f->r->pool, (apr_size_t)(ctx->bblen+1));
        ctx->bytes = (apr_size_t)ctx->bblen;
        rv = apr_brigade_flatten(ctx->bbsave, ctx->buf, &ctx->bytes);
        ap_assert(rv == APR_SUCCESS);
        ctx->buf[ctx->bytes] = 0;
        sniff_encoding(f->r, ctx);

        /* FIXME: hook here for rewriting start-of-data? */
        /* nah, we only have one action here - call it inline */
        fix_skipto(f->r, ctx);

        /* we might change the Content-Length, so let's force its re-calculation */
        apr_table_unset(f->r->headers_out, "Content-Length");

        /* consume the data we just sniffed */
        /* we need to omit any <meta> we just invalidated */
        ctx->flags |= ENC_INITIALISED;
        ap_set_module_config(f->r->request_config, &xml2enc_module, ctx);
    }
    if (ctx->bbnext == NULL) {
        ctx->bbnext = apr_brigade_create(f->r->pool,
                                         f->r->connection->bucket_alloc);
    }

    if (!ctx->convset) {
        rv = ap_pass_brigade(f->next, ctx->bbsave);
        apr_brigade_cleanup(ctx->bbsave);
        ap_remove_output_filter(f);
        return rv;
    }
    /* move the data back to bb */
    APR_BRIGADE_CONCAT(bb, ctx->bbsave);

    while (b = APR_BRIGADE_FIRST(bb), b != APR_BRIGADE_SENTINEL(bb)) {
        ctx->bytes = 0;
        if (APR_BUCKET_IS_METADATA(b)) {
            APR_BUCKET_REMOVE(b);
            if (APR_BUCKET_IS_EOS(b)) {
                /* send remaining data */
                APR_BRIGADE_INSERT_TAIL(ctx->bbnext, b);
                return ap_fflush(f->next, ctx->bbnext);
            } else if (APR_BUCKET_IS_FLUSH(b)) {
                ap_fflush(f->next, ctx->bbnext);
            }
            apr_bucket_destroy(b);
        }
        else {        /* data bucket */
            char* buf;
            apr_size_t bytes = 0;
            char fixbuf[BUFLEN];
            apr_bucket* bdestroy = NULL;
            if (insz > 0) { /* we have dangling data.  Flatten it. */
                buf = fixbuf;
                bytes = BUFLEN;
                rv = apr_brigade_flatten(bb, buf, &bytes);
                ap_assert(rv == APR_SUCCESS);
                if (bytes == insz) {
                    /* this is only what we've already tried to convert.
                     * The brigade is exhausted.
                     * Save remaining data for next time round
                     */
          
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r, APLOGNO(01437)
                                  "xml2enc: Setting aside %" APR_SIZE_T_FMT
                                  " unconverted bytes", bytes);
                    rv = ap_fflush(f->next, ctx->bbnext);
                    APR_BRIGADE_CONCAT(ctx->bbsave, bb);
                    APR_BRIGADE_DO(b, ctx->bbsave) {
                        ap_assert(apr_bucket_setaside(b, f->r->pool)
                                  == APR_SUCCESS);
                    }
                    return rv;
                }
                /* remove the data we've just read */
                rv = apr_brigade_partition(bb, bytes, &bstart);
                while (b = APR_BRIGADE_FIRST(bb), b != bstart) {
                    APR_BUCKET_REMOVE(b);
                    apr_bucket_destroy(b);
                }
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r, APLOGNO(01438)
                              "xml2enc: consuming %" APR_SIZE_T_FMT
                              " bytes flattened", bytes);
            }
            else {
                rv = apr_bucket_read(b, (const char**)&buf, &bytes,
                                     APR_BLOCK_READ);
                APR_BUCKET_REMOVE(b);
                bdestroy = b;  /* can't destroy until finished with the data */
                ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r, APLOGNO(01439)
                              "xml2enc: consuming %" APR_SIZE_T_FMT
                              " bytes from bucket", bytes);
            }
            /* OK, we've got some input we can use in [buf,bytes] */
            if (rv == APR_SUCCESS) {
                apr_size_t consumed;
                xml2enc_run_preprocess(f, &buf, &bytes);
                consumed = insz = bytes;
                while (insz > 0) {
                    apr_status_t rv2;
                    if (ctx->bytes == ctx->bblen) {
                        /* nothing was converted last time!
                         * break out of this loop! 
                         */
                        b = apr_bucket_transient_create(buf+(bytes - insz), insz,
                                                        bb->bucket_alloc);
                        APR_BRIGADE_INSERT_HEAD(bb, b);
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r, APLOGNO(01440)
                                      "xml2enc: reinserting %" APR_SIZE_T_FMT
                                      " unconsumed bytes from bucket", insz);
                        break;
                    }
                    ctx->bytes = (apr_size_t)ctx->bblen;
                    rv = apr_xlate_conv_buffer(ctx->convset, buf+(bytes - insz),
                                               &insz, ctx->buf, &ctx->bytes);
                    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, f->r, APLOGNO(01441)
                                  "xml2enc: converted %" APR_SIZE_T_FMT
                                  "/%" APR_OFF_T_FMT " bytes", consumed - insz,
                                  ctx->bblen - ctx->bytes);
                    consumed = insz;
                    rv2 = ap_fwrite(f->next, ctx->bbnext, ctx->buf,
                                    (apr_size_t)ctx->bblen - ctx->bytes);
                    if (rv2 != APR_SUCCESS) {
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv2, f->r, APLOGNO(01442)
                                      "ap_fwrite failed");
                        return rv2;
                    }
                    switch (rv) {
                    case APR_SUCCESS:
                        continue;
                    case APR_EINCOMPLETE:
                        ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, f->r, APLOGNO(01443)
                                      "INCOMPLETE");
                        continue;     /* If outbuf too small, go round again.
                                       * If it was inbuf, we'll break out when
                                       * we test ctx->bytes == ctx->bblen
                                       */
                    case APR_EINVAL: /* try skipping one bad byte */
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, f->r, APLOGNO(01444)
                                   "Skipping invalid byte(s) in input stream!");
                        --insz;
                        continue;
                    default:
                        /* Erk!  What's this?
                         * Bail out, flush, and hope to eat the buf raw
                         */
                        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, APLOGNO(01445)
                                      "Failed to convert input; trying it raw") ;
                        ctx->convset = NULL;
                        rv = ap_fflush(f->next, ctx->bbnext);
                        if (rv != APR_SUCCESS)
                            ap_log_rerror(APLOG_MARK, APLOG_DEBUG, rv, f->r, APLOGNO(01446)
                                          "ap_fflush failed");
                        else
                            rv = ap_pass_brigade(f->next, ctx->bbnext);
                    }
                }
            } else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, f->r, APLOGNO(01447)
                              "xml2enc: error reading data") ;
            }
            if (bdestroy)
                apr_bucket_destroy(bdestroy);
            if (rv != APR_SUCCESS)
                return rv;
        }
    }
    return APR_SUCCESS;
}