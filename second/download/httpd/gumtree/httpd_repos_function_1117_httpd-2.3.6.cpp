static apr_status_t socache_mc_remove(ap_socache_instance_t *ctx, server_rec *s, 
                                      const unsigned char *id, 
                                      unsigned int idlen, apr_pool_t *p)
{
    char buf[MC_KEY_LEN];
    apr_status_t rv;

    if (socache_mc_id2key(ctx, id, idlen, buf, sizeof buf)) {
        return APR_EINVAL;
    }

    rv = apr_memcache_delete(ctx->mc, buf, 0);

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, s,
                     "scache_mc: error deleting key '%s' ",
                     buf);
    }

    return rv;
}