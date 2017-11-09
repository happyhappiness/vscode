static int op_file_subr(ap_expr_eval_ctx_t *ctx, const void *data, const char *arg)
{
    int rc = FALSE;
    apr_finfo_t sb;
    request_rec *rsub, *r = ctx->r;
    if (!r)
        return FALSE;
    rsub = ap_sub_req_lookup_file(arg, r, NULL);
    if (rsub->status < 300 &&
        /* double-check that file exists since default result is 200 */
        apr_stat(&sb, rsub->filename, APR_FINFO_MIN, ctx->p) == APR_SUCCESS) {
        rc = TRUE;
    }
    ap_log_rerror(LOG_MARK(ctx->info), APLOG_TRACE5, 0, r,
                  "Subrequest for -F %s at %s:%d gave status: %d",
                  arg, ctx->info->filename, ctx->info->line_number,
                  rsub->status);
    ap_destroy_sub_req(rsub);
    return rc;
}