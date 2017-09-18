    apr_bucket *tmp_buck;

    *inserted_head = NULL;
    if (!ctx->if_nesting_level) {
        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
        if ((tag != NULL) || (tag_val != NULL)) {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                        "else directive does not take tags in %s", r->filename);
            if (ctx->flags & FLAG_PRINTING) {
                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
            }
            return -1;
        }
