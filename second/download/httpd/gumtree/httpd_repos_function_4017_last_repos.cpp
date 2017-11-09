static const char *filesize_func(ap_expr_eval_ctx_t *ctx, const void *data,
                                  char *arg)
{
    apr_finfo_t sb;
    if (apr_stat(&sb, arg, APR_FINFO_MIN, ctx->p) == APR_SUCCESS
        && sb.filetype == APR_REG && sb.size > 0)
        return apr_psprintf(ctx->p, "%" APR_OFF_T_FMT, sb.size);
    else
        return "0";
}