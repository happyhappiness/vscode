                                        apr_bucket_pool_create(to_release,
                                        intern->parse_pos, ctx->pool,
                                        f->c->bucket_alloc));
            }
        }
        else if (PARSE_PRE_HEAD != intern->state) {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                          "SSI directive was not properly finished at the end "
                          "of parsed document %s", r->filename);
            if (ctx->flags & SSI_FLAG_PRINTING) {
                SSI_CREATE_ERROR_BUCKET(ctx, f, pass_bb);
            }
        }

        if (!(ctx->flags & SSI_FLAG_PRINTING)) {
            ap_log_rerror(APLOG_MARK, APLOG_WARNING, 0, r,
                          "missing closing endif directive in parsed document"
                          " %s", r->filename);
        }

        /* cleanup our temporary memory */
        apr_brigade_destroy(intern->tmp_bb);
