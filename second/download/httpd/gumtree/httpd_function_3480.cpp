apr_status_t socache_dc_retrieve(ap_socache_instance_t *ctx, server_rec *s, 
                                        const unsigned char *id, unsigned int idlen,
                                        unsigned char *dest, unsigned int *destlen,
                                        apr_pool_t *p)
{
    unsigned int data_len;

    /* Retrieve any corresponding session from the distributed cache context */
    if (!DC_CTX_get_session(ctx->dc, id, idlen, dest, *destlen, &data_len)) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "distributed scache 'retrieve' MISS");
        return APR_NOTFOUND;
    }
    if (data_len > *destlen) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, "distributed scache 'retrieve' OVERFLOW");
        return APR_ENOSPC;
    }
    *destlen = data_len;
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, "distributed scache 'retrieve' HIT");
    return APR_SUCCESS;
}