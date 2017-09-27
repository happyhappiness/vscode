                                      unsigned int idlen, apr_pool_t *p)
{
    /* Remove any corresponding session from the distributed cache context */
    if (!DC_CTX_remove_session(ctx->dc, id, idlen)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00745) "distributed scache 'remove' MISS");
        return APR_NOTFOUND;
    } else {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00746) "distributed scache 'remove' HIT");
        return APR_SUCCESS;
    }
}

static void socache_dc_status(ap_socache_instance_t *ctx, request_rec *r, int flags)
