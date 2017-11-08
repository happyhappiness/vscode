static int op_url_subr(ap_expr_eval_ctx_t *ctx, const void *data, const char *arg)
{
    int rc = FALSE;
    request_rec  *rsub, *r = ctx->r;
    if (!r)
        return FALSE;
    /* avoid some infinite recursions */
    if (r->main && r->main->uri && r->uri && strcmp(r->main->uri, r->uri) == 0)
        return FALSE;

    rsub = ap_sub_req_lookup_uri(arg, r, NULL);
    if (rsub->status < 400) {
            rc = TRUE;
    }
    ap_log_rerror(LOG_MARK(ctx->info), APLOG_TRACE5, 0, r,
                  "Subrequest for -U %s at %s:%d gave status: %d",
                  arg, ctx->info->filename, ctx->info->line_number,
                  rsub->status);
    ap_destroy_sub_req(rsub);
    return rc;
}