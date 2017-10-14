static apr_status_t socache_mc_store(ap_socache_instance_t *ctx, server_rec *s, 
                                     const unsigned char *id, unsigned int idlen,
                                     apr_time_t expiry,
                                     unsigned char *ucaData, unsigned int nData,
                                     apr_pool_t *p)
{
    char buf[MC_KEY_LEN];
    apr_status_t rv;

    if (socache_mc_id2key(ctx, id, idlen, buf, sizeof buf)) {
        return APR_EINVAL;
    }

    /* In APR-util - unclear what 'timeout' is, as it was not implemented */
    rv = apr_memcache_set(ctx->mc, buf, (char*)ucaData, nData, 0, 0);

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
                     "scache_mc: error setting key '%s' "
                     "with %d bytes of data", buf, nData);
        return rv;
    }

    return APR_SUCCESS;
}