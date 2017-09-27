
        /* try to match end_seq at current pos. */
        case PARSE_TAIL:
        case PARSE_TAIL_SEQ:
            index = find_tail(ctx, data, len);

            switch (intern->state) {
            case PARSE_EXECUTE:  /* full match */
                apr_bucket_split(b, index);
                newb = APR_BUCKET_NEXT(b);
                apr_bucket_delete(b);
                b = newb;
                break;

            case PARSE_ARG:      /* no match */
                /* PARSE_ARG must reparse at the beginning */
                APR_BRIGADE_PREPEND(bb, intern->tmp_bb);
                b = APR_BRIGADE_FIRST(bb);
                break;

            default:             /* partial match */
                newb = APR_BUCKET_NEXT(b);
                APR_BUCKET_REMOVE(b);
                APR_BRIGADE_INSERT_TAIL(intern->tmp_bb, b);
                b = newb;
                break;
            }

            break;

        /* now execute the parsed directive, cleanup the space and
         * start again with PARSE_PRE_HEAD
         */
        case PARSE_EXECUTE:
            /* if there was an error, it was already logged; just stop here */
            if (intern->error) {
                if (ctx->flags & SSI_FLAG_PRINTING) {
                    SSI_CREATE_ERROR_BUCKET(ctx, f, pass_bb);
                    intern->error = 0;
                }
            }
            else {
                include_handler_fn_t *handle_func;

                handle_func =
                    (include_handler_fn_t *)apr_hash_get(include_handlers, intern->directive,
                                                         intern->directive_len);

                if (handle_func) {
                    DEBUG_INIT(ctx, f, pass_bb);
                    rv = handle_func(ctx, f, pass_bb);
                    if (rv != APR_SUCCESS) {
                        apr_brigade_destroy(pass_bb);
                        return rv;
                    }
                }
                else {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "unknown directive \"%s\" in parsed doc %s",
                                  apr_pstrmemdup(r->pool, intern->directive,
                                                 intern->directive_len),
                                                 r->filename);
                    if (ctx->flags & SSI_FLAG_PRINTING) {
                        SSI_CREATE_ERROR_BUCKET(ctx, f, pass_bb);
                    }
                }
            }

            /* cleanup */
            apr_pool_clear(ctx->dpool);
            apr_brigade_cleanup(intern->tmp_bb);

            /* Oooof. Done here, start next round */
            intern->state = PARSE_PRE_HEAD;
            break;

        } /* switch(ctx->state) */

    } /* while(brigade) */

    /* End of stream. Final cleanup */
    if (intern->seen_eos) {
        if (PARSE_HEAD == intern->state) {
            if (ctx->flags & SSI_FLAG_PRINTING) {
                char *to_release = apr_palloc(ctx->pool, intern->parse_pos);

                memcpy(to_release, intern->start_seq, intern->parse_pos);
                APR_BRIGADE_INSERT_TAIL(pass_bb,
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
        apr_pool_destroy(ctx->dpool);

        /* don't forget to finally insert the EOS bucket */
        APR_BRIGADE_INSERT_TAIL(pass_bb, b);
    }

    /* if something's left over, pass it along */
    if (!APR_BRIGADE_EMPTY(pass_bb)) {
        rv = ap_pass_brigade(f->next, pass_bb);
    }
    else {
        rv = APR_SUCCESS;
        apr_brigade_destroy(pass_bb);
    }
    return rv;
}


/*
 * +-------------------------------------------------------+
 * |                                                       |
 * |                     Runtime Hooks
 * |                                                       |
 * +-------------------------------------------------------+
 */

static int includes_setup(ap_filter_t *f)
{
    include_dir_config *conf = ap_get_module_config(f->r->per_dir_config,
                                                    &include_module);

    /* When our xbithack value isn't set to full or our platform isn't
     * providing group-level protection bits or our group-level bits do not
     * have group-execite on, we will set the no_local_copy value to 1 so
     * that we will not send 304s.
     */
    if ((conf->xbithack != XBITHACK_FULL)
        || !(f->r->finfo.valid & APR_FINFO_GPROT)
        || !(f->r->finfo.protection & APR_GEXECUTE)) {
        f->r->no_local_copy = 1;
    }

    /* Don't allow ETag headers to be generated - see RFC2616 - 13.3.4.
