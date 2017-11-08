static void socache_dc_status(ap_socache_instance_t *ctx, request_rec *r, int flags)
{
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
                  "distributed scache 'socache_dc_status'");
    ap_rprintf(r, "cache type: <b>DC (Distributed Cache)</b>, "
               " target: <b>%s</b><br>", ctx->target);
}