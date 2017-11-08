static int op_strmatch(ap_expr_eval_ctx_t *ctx, const void *data,
                       const char *arg1, const char *arg2)
{
    return (APR_SUCCESS == apr_fnmatch(arg2, arg1, 0));
}