    apr_bucket  *tmp_buck;
    char parsed_string[MAX_STRING_LEN];

    *inserted_head = NULL;
    if (ctx->flags & FLAG_PRINTING) {
        if (ctx->flags & FLAG_NO_EXEC) {
            ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                      "exec used but not allowed in %s", r->filename);
            CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
        }
        else {
            while (1) {
                cgid_pfn_gtv(ctx, &tag, &tag_val, 1);
