static int op_file_xbit(ap_expr_eval_ctx_t *ctx, const void *data, const char *arg)
{
    apr_finfo_t sb;
    if (apr_stat(&sb, arg, APR_FINFO_PROT| APR_FINFO_LINK, ctx->p) == APR_SUCCESS
        && (sb.protection & (APR_UEXECUTE | APR_GEXECUTE | APR_WEXECUTE))) {
        return TRUE;
    }
    return FALSE;
}