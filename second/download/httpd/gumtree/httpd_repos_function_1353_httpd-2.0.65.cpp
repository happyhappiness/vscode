static const char *get_include_var(request_rec *r, include_ctx_t *ctx, 
                                   const char *var)
{
    const char *val;
    if (apr_isdigit(*var) && !var[1]) {
        /* Handle $0 .. $9 from the last regex evaluated.
         * The choice of returning NULL strings on not-found,
         * v.s. empty strings on an empty match is deliberate.
         */
        if (!ctx->re_result || !ctx->re_string) {
            return NULL;
        }
        else {
            int idx = atoi(var);
            apr_size_t len = (*ctx->re_result)[idx].rm_eo
                           - (*ctx->re_result)[idx].rm_so;
            if (    (*ctx->re_result)[idx].rm_so < 0
                 || (*ctx->re_result)[idx].rm_eo < 0) {
                return NULL;
            }
            val = apr_pstrmemdup(r->pool, ctx->re_string 
                                        + (*ctx->re_result)[idx].rm_so, len);
        }
    }
    else {
        val = apr_table_get(r->subprocess_env, var);

        if (val == LAZY_VALUE)
            val = add_include_vars_lazy(r, var, ctx->time_str);
    }
    return val;
}