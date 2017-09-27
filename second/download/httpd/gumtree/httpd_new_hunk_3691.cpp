}

static void socache_dc_status(ap_socache_instance_t *ctx, request_rec *r, int flags)
{
    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r, APLOGNO(00747)
                  "distributed scache 'socache_dc_status'");
    if (!(flags & AP_STATUS_SHORT)) {
        ap_rprintf(r, "cache type: <b>DC (Distributed Cache)</b>, "
                   " target: <b>%s</b><br>", ctx->target);
    }
    else {
        ap_rputs("CacheType: DC\n", r);
        ap_rvputs(r, "CacheTarget: ", ctx->target, "\n", NULL);
    }
}

static apr_status_t socache_dc_iterate(ap_socache_instance_t *instance,
                                       server_rec *s, void *userctx,
                                       ap_socache_iterator_t *iterator,
                                       apr_pool_t *pool)
