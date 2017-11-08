static int handle_config(include_ctx_t *ctx, apr_bucket_brigade **bb, 
                         request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
                         apr_bucket **inserted_head)
{
    char *tag     = NULL;
    char *tag_val = NULL;
    char *parsed_string;
    apr_table_t *env = r->subprocess_env;

    *inserted_head = NULL;
    if (ctx->flags & FLAG_PRINTING) {
        while (1) {
            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 0);
            if (tag_val == NULL) {
                if (tag == NULL) {
                    return 0;  /* Reached the end of the string. */
                }
                else {
                    return 1;  /* tags must have values. */
                }
            }
            if (!strcmp(tag, "errmsg")) {
                if (ctx->error_str_override == NULL) {
                    ctx->error_str_override = (char *)apr_palloc(ctx->pool,
                                                              MAX_STRING_LEN);
                    ctx->error_str = ctx->error_str_override;
                }
                ap_ssi_parse_string(r, ctx, tag_val, ctx->error_str_override,
                                    MAX_STRING_LEN, 0);
            }
            else if (!strcmp(tag, "timefmt")) {
                apr_time_t date = r->request_time;
                if (ctx->time_str_override == NULL) {
                    ctx->time_str_override = (char *)apr_palloc(ctx->pool,
                                                              MAX_STRING_LEN);
                    ctx->time_str = ctx->time_str_override;
                }
                ap_ssi_parse_string(r, ctx, tag_val, ctx->time_str_override,
                                    MAX_STRING_LEN, 0);
                apr_table_setn(env, "DATE_LOCAL", ap_ht_time(r->pool, date, 
                               ctx->time_str, 0));
                apr_table_setn(env, "DATE_GMT", ap_ht_time(r->pool, date, 
                               ctx->time_str, 1));
                apr_table_setn(env, "LAST_MODIFIED",
                               ap_ht_time(r->pool, r->finfo.mtime, 
                               ctx->time_str, 0));
            }
            else if (!strcmp(tag, "sizefmt")) {
                parsed_string = ap_ssi_parse_string(r, ctx, tag_val, NULL, 
                                                    MAX_STRING_LEN, 0);
                decodehtml(parsed_string);
                if (!strcmp(parsed_string, "bytes")) {
                    ctx->flags |= FLAG_SIZE_IN_BYTES;
                }
                else if (!strcmp(parsed_string, "abbrev")) {
                    ctx->flags &= FLAG_SIZE_ABBREV;
                }
            }
            else {
                apr_bucket *tmp_buck;

                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                              "unknown parameter \"%s\" to tag config in %s",
                              tag, r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
                return 1;
            }
        }
    }
    return 0;
}