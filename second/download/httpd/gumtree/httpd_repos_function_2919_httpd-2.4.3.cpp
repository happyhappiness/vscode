static int op_file_min(ap_expr_eval_ctx_t *ctx, const void *data, const char *arg)
{
    apr_finfo_t sb;
    const char *name = (const char *)data;
    if (apr_stat(&sb, arg, APR_FINFO_MIN, ctx->p) != APR_SUCCESS)
        return FALSE;
    switch (name[0]) {
    case 'd':
        return (sb.filetype == APR_DIR);
    case 'e':
        return TRUE;
    case 'f':
        return (sb.filetype == APR_REG);
    case 's':
        return (sb.filetype == APR_REG && sb.size > 0);
    default:
        ap_assert(0);
    }
    return FALSE;
}