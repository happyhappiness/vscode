static int handle_if(include_ctx_t *ctx, apr_bucket_brigade **bb, 
                     request_rec *r, ap_filter_t *f, apr_bucket *head_ptr, 
                     apr_bucket **inserted_head)
{
    char *tag     = NULL;
    char *tag_val = NULL;
    char *expr    = NULL;
    int   expr_ret, was_error, was_unmatched;
    apr_bucket *tmp_buck;
    char debug_buf[MAX_DEBUG_SIZE];

    *inserted_head = NULL;
    if (!(ctx->flags & FLAG_PRINTING)) {
        ctx->if_nesting_level++;
    }
    else {
        while (1) {
            ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 0);
            if (tag == NULL) {
                if (expr == NULL) {
                    ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                                  "missing expr in if statement: %s", 
                                  r->filename);
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                    return 1;
                }
                expr_ret = parse_expr(r, ctx, expr, &was_error, 
                                      &was_unmatched, debug_buf);
                if (was_error) {
                    CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, 
                                        *inserted_head);
                    return 1;
                }
                if (was_unmatched) {
                    DUMP_PARSE_EXPR_DEBUG(tmp_buck, head_ptr, 
                                          "\nUnmatched '\n", *inserted_head);
                }
                DUMP_PARSE_EXPR_DEBUG(tmp_buck, head_ptr, debug_buf, 
                                      *inserted_head);
                
                if (expr_ret) {
                    ctx->flags |= (FLAG_PRINTING | FLAG_COND_TRUE);
                }
                else {
                    ctx->flags &= FLAG_CLEAR_PRINT_COND;
                }
                LOG_COND_STATUS(ctx, tmp_buck, head_ptr, *inserted_head, 
                                "   if");
                ctx->if_nesting_level = 0;
                return 0;
            }
            else if (!strcmp(tag, "expr")) {
                expr = tag_val;
#ifdef DEBUG_INCLUDE
                if (1) {
                    apr_size_t d_len = 0;
                    d_len = sprintf(debug_buf, "**** if expr=\"%s\"\n", expr);
                    tmp_buck = apr_bucket_heap_create(debug_buf, d_len, NULL,
                                                  r->connection->bucket_alloc);
                    APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);

                    if (*inserted_head == NULL) {
                        *inserted_head = tmp_buck;
                    }
                }
#endif
            }
            else {
                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                            "unknown parameter \"%s\" to tag if in %s", tag, 
                            r->filename);
                CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
                return 1;
            }

        }
    }
    return 0;
}