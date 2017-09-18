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
