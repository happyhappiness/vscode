static apr_status_t handle_config(include_ctx_t *ctx, ap_filter_t *f,
                                  apr_bucket_brigade *bb)
{
    request_rec *r = f->r;
    apr_table_t *env = r->subprocess_env;

    if (!ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, "missing argument for config element in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        return APR_SUCCESS;
    }

    if (!ctx->argc) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    while (1) {
        char *tag     = NULL;
        char *tag_val = NULL;

        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, SSI_VALUE_RAW);
        if (!tag || !tag_val) {
            break;
        }

        if (!strcmp(tag, "errmsg")) {
            ctx->error_str = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                                 SSI_EXPAND_DROP_NAME);
        }
        else if (!strcmp(tag, "echomsg")) {
            ctx->intern->undefined_echo =
                ap_ssi_parse_string(ctx, tag_val, NULL, 0,SSI_EXPAND_DROP_NAME);
            ctx->intern->undefined_echo_len=strlen(ctx->intern->undefined_echo);
        }
        else if (!strcmp(tag, "timefmt")) {
            apr_time_t date = r->request_time;

            ctx->time_str = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                                SSI_EXPAND_DROP_NAME);

            apr_table_setn(env, "DATE_LOCAL", ap_ht_time(r->pool, date,
                           ctx->time_str, 0));
            apr_table_setn(env, "DATE_GMT", ap_ht_time(r->pool, date,
                           ctx->time_str, 1));
            apr_table_setn(env, "LAST_MODIFIED",
                           ap_ht_time(r->pool, r->finfo.mtime,
                           ctx->time_str, 0));
        }
        else if (!strcmp(tag, "sizefmt")) {
            char *parsed_string;

            parsed_string = ap_ssi_parse_string(ctx, tag_val, NULL, 0,
                                                SSI_EXPAND_DROP_NAME);
            if (!strcmp(parsed_string, "bytes")) {
                ctx->flags |= SSI_FLAG_SIZE_IN_BYTES;
            }
            else if (!strcmp(parsed_string, "abbrev")) {
                ctx->flags &= SSI_FLAG_SIZE_ABBREV;
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown value "
                              "\"%s\" to parameter \"sizefmt\" of tag config "
                              "in %s", parsed_string, r->filename);
                SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
                break;
            }
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, "unknown parameter "
                          "\"%s\" to tag config in %s", tag, r->filename);
            SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
            break;
        }
    }

    return APR_SUCCESS;
}