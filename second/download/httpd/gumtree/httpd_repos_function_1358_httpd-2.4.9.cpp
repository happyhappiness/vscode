static apr_status_t socache_dc_store(ap_socache_instance_t *ctx, server_rec *s,
                                     const unsigned char *id, unsigned int idlen,
                                     apr_time_t expiry,
                                     unsigned char *der, unsigned int der_len,
                                     apr_pool_t *p)
{
    /* !@#$%^ - why do we deal with *absolute* time anyway???
     * Uhm - because most things expire things at a specific time?
     * Were the API were thought out expiry - r->request_time is a good approximation
     */
    expiry -= apr_time_now();
    /* Send the serialised session to the distributed cache context */
    if (!DC_CTX_add_session(ctx->dc, id, idlen, der, der_len,
                            apr_time_msec(expiry))) {
        ap_log_error(APLOG_MARK, APLOG_ERR, 0, s, APLOGNO(00740) "distributed scache 'store' failed");
        return APR_EGENERAL;
    }
    ap_log_error(APLOG_MARK, APLOG_DEBUG, 0, s, APLOGNO(00741) "distributed scache 'store' successful");
    return APR_SUCCESS;
}