                    ctx->flags &= FLAG_SIZE_ABBREV;
                }
            }
            else {
                apr_bucket *tmp_buck;

                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "unknown parameter \"%s\" to tag config in %s",
                              tag, r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
            }
        }
    }
