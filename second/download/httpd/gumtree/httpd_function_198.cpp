static apr_status_t send_parsed_content(apr_bucket_brigade **bb, 
                                        request_rec *r, ap_filter_t *f)
{
    include_ctx_t *ctx = f->ctx;
    apr_bucket *dptr = APR_BRIGADE_FIRST(*bb);
    apr_bucket *tmp_dptr;
    apr_bucket_brigade *tag_and_after;
    apr_status_t rv = APR_SUCCESS;

    if (r->args) {               /* add QUERY stuff to env cause it ain't yet */
        char *arg_copy = apr_pstrdup(r->pool, r->args);

        apr_table_setn(r->subprocess_env, "QUERY_STRING", r->args);
        ap_unescape_url(arg_copy);
        apr_table_setn(r->subprocess_env, "QUERY_STRING_UNESCAPED",
                  ap_escape_shell_cmd(r->pool, arg_copy));
    }

    while (dptr != APR_BRIGADE_SENTINEL(*bb) && !APR_BUCKET_IS_EOS(dptr)) {
        /* State to check for the STARTING_SEQUENCE. */
        if ((ctx->state == PRE_HEAD) || (ctx->state == PARSE_HEAD)) {
            int do_cleanup = 0;
            apr_size_t cleanup_bytes = ctx->parse_pos;

            tmp_dptr = find_start_sequence(dptr, ctx, *bb, &do_cleanup);
            if (!APR_STATUS_IS_SUCCESS(ctx->status)) {
                return ctx->status;
            }

            /* The few bytes stored in the ssi_tag_brigade turned out not to
             * be a tag after all. This can only happen if the starting
             * tag actually spans brigades. This should be very rare.
             */
            if ((do_cleanup) && (!APR_BRIGADE_EMPTY(ctx->ssi_tag_brigade))) {
                apr_bucket *tmp_bkt;

                tmp_bkt = apr_bucket_immortal_create(ctx->start_seq,
                                                  cleanup_bytes,
                                                  r->connection->bucket_alloc);
                APR_BRIGADE_INSERT_HEAD(*bb, tmp_bkt);
                apr_brigade_cleanup(ctx->ssi_tag_brigade);
            }

            /* If I am inside a conditional (if, elif, else) that is false
             *   then I need to throw away anything contained in it.
             */
            if ((!(ctx->flags & FLAG_PRINTING)) && (tmp_dptr != NULL) &&
                (dptr != APR_BRIGADE_SENTINEL(*bb))) {
                while ((dptr != APR_BRIGADE_SENTINEL(*bb)) &&
                       (dptr != tmp_dptr)) {
                    apr_bucket *free_bucket = dptr;

                    dptr = APR_BUCKET_NEXT (dptr);
                    apr_bucket_delete(free_bucket);
                }
            }

            /* Adjust the current bucket position based on what was found... */
            if ((tmp_dptr != NULL) && (ctx->state == PARSE_DIRECTIVE)) {
                if (ctx->tag_start_bucket != NULL) {
                    dptr = ctx->tag_start_bucket;
                }
                else {
                    dptr = APR_BRIGADE_SENTINEL(*bb);
                }
            }
            else if ((tmp_dptr != NULL) &&
                     (ctx->output_now ||
                      (ctx->bytes_parsed >= BYTE_COUNT_THRESHOLD))) {
                /* Send the large chunk of pre-tag bytes...  */
                tag_and_after = apr_brigade_split(*bb, tmp_dptr);
                if (ctx->output_flush) {
                    APR_BRIGADE_INSERT_TAIL(*bb, apr_bucket_flush_create((*bb)->bucket_alloc));
                }

                rv = ap_pass_brigade(f->next, *bb);
                if (rv != APR_SUCCESS) {
                    return rv;
                }
                *bb  = tag_and_after;
                dptr = tmp_dptr;
                ctx->output_flush = 0;
                ctx->bytes_parsed = 0;
                ctx->output_now = 0;
            }
            else if (tmp_dptr == NULL) { 
                /* There was no possible SSI tag in the
                 * remainder of this brigade... */
                dptr = APR_BRIGADE_SENTINEL(*bb);  
            }
        }

        /* State to check for the ENDING_SEQUENCE. */
        if (((ctx->state == PARSE_DIRECTIVE) ||
             (ctx->state == PARSE_TAG)       ||
             (ctx->state == PARSE_TAIL))       &&
            (dptr != APR_BRIGADE_SENTINEL(*bb))) {
            tmp_dptr = find_end_sequence(dptr, ctx, *bb);
            if (!APR_STATUS_IS_SUCCESS(ctx->status)) {
                return ctx->status;
            }

            if (tmp_dptr != NULL) {
                dptr = tmp_dptr;  /* Adjust bucket pos... */
                
                /* If some of the tag has already been set aside then set
                 * aside remainder of tag. Now the full tag is in 
                 * ssi_tag_brigade.
                 * If none has yet been set aside, then leave it all where it 
                 * is.
                 * In any event after this the entire set of tag buckets will 
                 * be in one place or another.
                 */
                if (!APR_BRIGADE_EMPTY(ctx->ssi_tag_brigade)) {
                    tag_and_after = apr_brigade_split(*bb, dptr);
                    APR_BRIGADE_CONCAT(ctx->ssi_tag_brigade, *bb);
                    *bb = tag_and_after;
                }
                else if (ctx->output_now ||
                         (ctx->bytes_parsed >= BYTE_COUNT_THRESHOLD)) {
                    SPLIT_AND_PASS_PRETAG_BUCKETS(*bb, ctx, f->next, rv);
                    if (rv != APR_SUCCESS) {
                        return rv;
                    }
                    ctx->output_flush = 0;
                    ctx->output_now = 0;
                }
            }
            else {
                /* remainder of this brigade...    */
                dptr = APR_BRIGADE_SENTINEL(*bb);  
            }
        }

        /* State to processed the directive... */
        if (ctx->state == PARSED) {
            apr_bucket    *content_head = NULL, *tmp_bkt;
            apr_size_t    tmp_i;
            char          tmp_buf[TMP_BUF_SIZE];
            int (*handle_func)(include_ctx_t *, apr_bucket_brigade **,
                               request_rec *, ap_filter_t *, apr_bucket *,
                               apr_bucket **);

            /* By now the full tag (all buckets) should either be set aside into
             *  ssi_tag_brigade or contained within the current bb. All tag
             *  processing from here on can assume that.
             */

            /* At this point, everything between ctx->head_start_bucket and
             * ctx->tail_start_bucket is an SSI
             * directive, we just have to deal with it now.
             */
            if (get_combined_directive(ctx, r, *bb, tmp_buf,
                                        TMP_BUF_SIZE) != APR_SUCCESS) {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "mod_include: error copying directive in %s",
                            r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_bkt, dptr, content_head);

                /* DO CLEANUP HERE!!!!! */
                tmp_dptr = ctx->head_start_bucket;
                if (!APR_BRIGADE_EMPTY(ctx->ssi_tag_brigade)) {
                    apr_brigade_cleanup(ctx->ssi_tag_brigade);
                }
                else {
                    do {
                        tmp_bkt  = tmp_dptr;
                        tmp_dptr = APR_BUCKET_NEXT (tmp_dptr);
                        apr_bucket_delete(tmp_bkt);
                    } while ((tmp_dptr != dptr) &&
                             (tmp_dptr != APR_BRIGADE_SENTINEL(*bb)));
                }

                return APR_SUCCESS;
            }

            /* Can't destroy the tag buckets until I'm done processing
             * because the combined_tag might just be pointing to
             * the contents of a single bucket!
             */

            /* Retrieve the handler function to be called for this directive 
             * from the functions registered in the hash table.
             * Need to lower case the directive for proper matching. Also need 
             * to have it NULL terminated for proper hash matching.
             */
            for (tmp_i = 0; tmp_i < ctx->directive_length; tmp_i++) {
                ctx->combined_tag[tmp_i] = 
                                          apr_tolower(ctx->combined_tag[tmp_i]);
            }
            ctx->combined_tag[ctx->directive_length] = '\0';
            ctx->curr_tag_pos = &ctx->combined_tag[ctx->directive_length+1];

            handle_func = 
                (include_handler_fn_t *)apr_hash_get(include_hash, 
                                                     ctx->combined_tag, 
                                                     ctx->directive_length);
            if (handle_func != NULL) {
                rv = (*handle_func)(ctx, bb, r, f, dptr, &content_head);
                if ((rv != 0) && (rv != 1)) {
                    return (rv);
                }
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "unknown directive \"%s\" in parsed doc %s",
                              ctx->combined_tag, r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_bkt, dptr, content_head);
            }

            /* This chunk of code starts at the first bucket in the chain
             * of tag buckets (assuming that by this point the bucket for
             * the STARTING_SEQUENCE has been split) and loops through to
             * the end of the tag buckets freeing them all.
             *
             * Remember that some part of this may have been set aside
             * into the ssi_tag_brigade and the remainder (possibly as
             * little as one byte) will be in the current brigade.
             *
             * The value of dptr should have been set during the
             * PARSE_TAIL state to the first bucket after the
             * ENDING_SEQUENCE.
             *
             * The value of content_head may have been set during processing
             * of the directive. If so, the content was inserted in front
             * of the dptr bucket. The inserted buckets should not be thrown
             * away here, but they should also not be parsed later.
             */
            if (content_head == NULL) {
                content_head = dptr;
            }
            tmp_dptr = ctx->head_start_bucket;
            if (!APR_BRIGADE_EMPTY(ctx->ssi_tag_brigade)) {
                apr_brigade_cleanup(ctx->ssi_tag_brigade);
            }
            else {
                do {
                    tmp_bkt  = tmp_dptr;
                    tmp_dptr = APR_BUCKET_NEXT (tmp_dptr);
                    apr_bucket_delete(tmp_bkt);
                } while ((tmp_dptr != content_head) &&
                         (tmp_dptr != APR_BRIGADE_SENTINEL(*bb)));
            }
            if (ctx->combined_tag == tmp_buf) {
                ctx->combined_tag = NULL;
            }

            /* Don't reset the flags or the nesting level!!! */
            ctx->parse_pos         = 0;
            ctx->head_start_bucket = NULL;
            ctx->head_start_index  = 0;
            ctx->tag_start_bucket  = NULL;
            ctx->tag_start_index   = 0;
            ctx->tail_start_bucket = NULL;
            ctx->tail_start_index  = 0;
            ctx->curr_tag_pos      = NULL;
            ctx->tag_length        = 0;
            ctx->directive_length  = 0;

            if (!APR_BRIGADE_EMPTY(ctx->ssi_tag_brigade)) {
                apr_brigade_cleanup(ctx->ssi_tag_brigade);
            }

            ctx->state     = PRE_HEAD;
        }
    }

    /* We have nothing more to send, stop now. */
    if (dptr != APR_BRIGADE_SENTINEL(*bb) &&
        APR_BUCKET_IS_EOS(dptr)) {
        /* We might have something saved that we never completed, but send
         * down unparsed.  This allows for <!-- at the end of files to be
         * sent correctly. */
        if (!APR_BRIGADE_EMPTY(ctx->ssi_tag_brigade)) {
            APR_BRIGADE_CONCAT(ctx->ssi_tag_brigade, *bb);
            return ap_pass_brigade(f->next, ctx->ssi_tag_brigade);
        }
        return ap_pass_brigade(f->next, *bb);
    }

    /* If I am in the middle of parsing an SSI tag then I need to set aside
     *   the pertinent trailing buckets and pass on the initial part of the
     *   brigade. The pertinent parts of the next brigades will be added to
     *   these set aside buckets to form the whole tag and will be processed
     *   once the whole tag has been found.
     */
    if (ctx->state == PRE_HEAD) {
        /* Inside a false conditional (if, elif, else), so toss it all... */
        if ((dptr != APR_BRIGADE_SENTINEL(*bb)) &&
            (!(ctx->flags & FLAG_PRINTING))) {
            apr_bucket *free_bucket;
            do {
                free_bucket = dptr;
                dptr = APR_BUCKET_NEXT (dptr);
                apr_bucket_delete(free_bucket);
            } while (dptr != APR_BRIGADE_SENTINEL(*bb));
        }
        else { 
            /* Otherwise pass it along...
             * No SSI tags in this brigade... */
            rv = ap_pass_brigade(f->next, *bb);  
            if (rv != APR_SUCCESS) {
                return rv;
            }
            ctx->bytes_parsed = 0;
        }
    }
    else if (ctx->state == PARSED) {         /* Invalid internal condition... */
        apr_bucket *content_head = NULL, *tmp_bkt;
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "Invalid mod_include state during file %s", r->filename);
        CREATE_ERROR_BUCKET(ctx, tmp_bkt, APR_BRIGADE_FIRST(*bb), content_head);
    }
    else {                    /* Entire brigade is middle chunk of SSI tag... */
        if (!APR_BRIGADE_EMPTY(ctx->ssi_tag_brigade)) {
            APR_BRIGADE_CONCAT(ctx->ssi_tag_brigade, *bb);
        }
        else {                  /* End of brigade contains part of SSI tag... */
            apr_bucket *last;
            if (ctx->head_start_index > 0) {
                apr_bucket_split(ctx->head_start_bucket, ctx->head_start_index);
                ctx->head_start_bucket = 
                                        APR_BUCKET_NEXT(ctx->head_start_bucket);
                ctx->head_start_index = 0;
            }
                           /* Set aside tag, pass pre-tag... */
            tag_and_after = apr_brigade_split(*bb, ctx->head_start_bucket);
            rv = ap_pass_brigade(f->next, *bb);
            if (rv != APR_SUCCESS) {
                return rv;
            }
            
            /* Set aside the partial tag
             * Exception: if there's an EOS at the end of this brigade,
             * the tag will never be completed, so send an error and EOS
             */
            last = APR_BRIGADE_LAST(tag_and_after);
            if (APR_BUCKET_IS_EOS(last)) {
                /* Remove everything before the EOS (i.e., the partial tag)
                 * and replace it with an error msg */
                apr_bucket *b;
                apr_bucket *err_bucket = NULL;
                for (b = APR_BRIGADE_FIRST(tag_and_after);
                     !APR_BUCKET_IS_EOS(b);
                     b = APR_BRIGADE_FIRST(tag_and_after)) {
                    APR_BUCKET_REMOVE(b);
                    apr_bucket_destroy(b);
                }
                CREATE_ERROR_BUCKET(ctx, err_bucket, b, err_bucket);
                rv = ap_pass_brigade(f->next, tag_and_after);
            }
            else {
                ap_save_brigade(f, &ctx->ssi_tag_brigade,
                                &tag_and_after, r->pool);
            }
            if (rv != APR_SUCCESS) {
                return rv;
            }
            ctx->bytes_parsed = 0;
        }
    }
    return APR_SUCCESS;
}