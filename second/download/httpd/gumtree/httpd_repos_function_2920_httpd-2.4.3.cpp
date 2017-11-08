static int op_file_link(ap_expr_eval_ctx_t *ctx, const void *data, const char *arg)
{
#if !defined(OS2)
    apr_finfo_t sb;
    if (apr_stat(&sb, arg, APR_FINFO_MIN | APR_FINFO_LINK, ctx->p) == APR_SUCCESS
        && sb.filetype == APR_LNK) {
        return TRUE;
    }
#endif
    return FALSE;
}