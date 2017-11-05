static apr_status_t socache_dc_remove(ap_socache_instance_t *ctx, 
                                      server_rec *s, const unsigned char *id, 
                                      unsigned int idlen, apr_pool_t *p)
{
    /* Remove any corresponding session from the distributed cache context */
    if (!DC_CTX_remove_session(ctx->dc, id, idlen)) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "distributed scache 'remove' MISS");
        return APR_NOTFOUND;
    } else {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "distributed scache 'remove' HIT");
        return APR_SUCCESS;
    }
}