static int handle_printenv(include_ctx_t *ctx, apr_bucket_brigade **bb, 
                           request_rec *r, ap_filter_t *f, 
                           apr_bucket *head_ptr, apr_bucket **inserted_head)
{
    char *tag     = NULL;
    char *tag_val = NULL;
    apr_bucket *tmp_buck;

    if (ctx->flags & FLAG_PRINTING) {
        ap_ssi_get_tag_and_value(ctx, &tag, &tag_val, 1);
        if ((tag == NULL) && (tag_val == NULL)) {
            const apr_array_header_t *arr = apr_table_elts(r->subprocess_env);
            const apr_table_entry_t *elts = (const apr_table_entry_t *)arr->elts;
            int i;
            const char *key_text, *val_text;
            char *key_val, *next;
            apr_size_t   k_len, v_len, kv_length;

            *inserted_head = NULL;
            for (i = 0; i < arr->nelts; ++i) {
                key_text = ap_escape_html(r->pool, elts[i].key);
                val_text = elts[i].val;
                if (val_text == LAZY_VALUE) {
                    val_text = add_include_vars_lazy(r, elts[i].key, ctx->time_str);
                }
                val_text = ap_escape_html(r->pool, elts[i].val);
                k_len = strlen(key_text);
                v_len = strlen(val_text);
                kv_length = k_len + v_len + sizeof("=\n");
                key_val = apr_palloc(r->pool, kv_length);
                next = key_val;
                memcpy(next, key_text, k_len);
                next += k_len;
                *next++ = '=';
                memcpy(next, val_text, v_len);
                next += v_len;
                *next++ = '\n';
                *next = 0;
                tmp_buck = apr_bucket_pool_create(key_val, kv_length - 1,
                                                  r->pool,
                                                  r->connection->bucket_alloc);
                APR_BUCKET_INSERT_BEFORE(head_ptr, tmp_buck);
                if (*inserted_head == NULL) {
                    *inserted_head = tmp_buck;
                }
            }
            return 0;
        }
        else {
            ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                        "printenv directive does not take tags in %s", 
                        r->filename);
            CREATE_ERROR_BUCKET(ctx, tmp_buck, head_ptr, *inserted_head);
            return -1;
        }
    }
    return 0;
}