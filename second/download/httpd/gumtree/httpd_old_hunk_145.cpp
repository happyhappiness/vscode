     * because we can rely on the pool to close the pipe for us.
     */

    return 0;
}

static int handle_exec(include_ctx_t *ctx, apr_bucket_brigade **bb, request_rec *r,
                       ap_filter_t *f, apr_bucket *head_ptr, apr_bucket **inserted_head)
{
    char *tag     = NULL;
    char *tag_val = NULL;
    char *file = r->filename;
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
                cgi_pfn_gtv(ctx, &tag, &tag_val, 1);
                if (tag_val == NULL) {
                    if (tag == NULL) {
                        return (0);
                    }
                    else {
                        return 1;
                    }
                }
                if (!strcmp(tag, "cmd")) {
                    cgi_pfn_ps(r, ctx, tag_val, parsed_string, sizeof(parsed_string), 1);
                    if (include_cmd(ctx, bb, parsed_string, r, f) == -1) {
                        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                                    "execution failure for parameter \"%s\" "
                                    "to tag exec in file %s", tag, r->filename);
                        CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
                    }
                }
                else if (!strcmp(tag, "cgi")) {
                    apr_status_t retval = APR_SUCCESS;

                    cgi_pfn_ps(r, ctx, tag_val, parsed_string, sizeof(parsed_string), 0);
                    SPLIT_AND_PASS_PRETAG_BUCKETS(*bb, ctx, f->next, retval);
                    if (retval != APR_SUCCESS) {
                        return retval;
                    }

                    if (include_cgi(parsed_string, r, f->next, head_ptr, inserted_head) == -1) {
                        ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                                    "invalid CGI ref \"%s\" in %s", tag_val, file);
                        CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
                    }
                }
                else {
                    ap_log_rerror(APLOG_MARK, APLOG_NOERRNO|APLOG_ERR, 0, r,
                                "unknown parameter \"%s\" to tag exec in %s", tag, file);
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
                }
            }
        }
    }
    return 0;
}
