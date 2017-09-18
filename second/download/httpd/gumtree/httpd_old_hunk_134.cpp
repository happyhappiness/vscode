            }
            ctx->bytes_parsed = 0;
        }
    }
    else if (ctx->state == PARSED) {         /* Invalid internal condition... */
        apr_bucket *content_head = NULL, *tmp_bkt;
        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                      "Invalid mod_include state during file %s", r->filename);
        CREATE_ERROR_BUCKET(ctx, tmp_bkt, APR_BRIGADE_FIRST(*bb), content_head);
    }
    else {                    /* Entire brigade is middle chunk of SSI tag... */
        if (!APR_BRIGADE_EMPTY(ctx->ssi_tag_brigade)) {
            APR_BRIGADE_CONCAT(ctx->ssi_tag_brigade, *bb);
