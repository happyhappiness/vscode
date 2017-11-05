static apr_status_t handle_printenv(include_ctx_t *ctx, ap_filter_t *f,
                                    apr_bucket_brigade *bb)
{
    request_rec *r = f->r;
    const apr_array_header_t *arr;
    const apr_table_entry_t *elts;
    int i;

    if (ctx->argc) {
        ap_log_rerror(APLOG_MARK,
                      (ctx->flags & SSI_FLAG_PRINTING)
                          ? APLOG_ERR : APLOG_WARNING,
                      0, r, "printenv directive does not take tags in %s",
                      r->filename);
    }

    if (!(ctx->flags & SSI_FLAG_PRINTING)) {
        return APR_SUCCESS;
    }

    if (ctx->argc) {
        SSI_CREATE_ERROR_BUCKET(ctx, f, bb);
        return APR_SUCCESS;
    }

    arr = apr_table_elts(r->subprocess_env);
    elts = (apr_table_entry_t *)arr->elts;

    for (i = 0; i < arr->nelts; ++i) {
        const char *key_text, *val_text;
        char *key_val, *next;
        apr_size_t k_len, v_len, kv_length;

        /* get key */
        key_text = ap_escape_html(ctx->dpool, elts[i].key);
        k_len = strlen(key_text);

        /* get value */
        val_text = elts[i].val;
        if (val_text == LAZY_VALUE) {
            val_text = add_include_vars_lazy(r, elts[i].key, ctx->time_str);
        }
        val_text = ap_escape_html(ctx->dpool, val_text);
        v_len = strlen(val_text);

        /* assemble result */
        kv_length = k_len + v_len + sizeof("=\n");
        key_val = apr_palloc(ctx->pool, kv_length);
        next = key_val;

        memcpy(next, key_text, k_len);
        next += k_len;
        *next++ = '=';
        memcpy(next, val_text, v_len);
        next += v_len;
        *next++ = '\n';
        *next = 0;

        APR_BRIGADE_INSERT_TAIL(bb, apr_bucket_pool_create(key_val, kv_length-1,
                                ctx->pool, f->c->bucket_alloc));
    }

    ctx->flush_now = 1;
    return APR_SUCCESS;
}