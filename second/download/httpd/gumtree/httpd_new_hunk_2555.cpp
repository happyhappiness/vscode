    /* ### this could do with a subpool, but _getp looks like it will
     * eat memory like it's going out of fashion anyway. */

    rv = apr_memcache_getp(ctx->mc, p, buf, &data, &data_len, NULL);
    if (rv) {
        if (rv != APR_NOTFOUND) {
            ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00791)
                         "scache_mc: 'retrieve' FAIL");
        }
        return rv;
    }
    else if (data_len > *destlen) {
        ap_log_error(APLOG_MARK, APLOG_ERR, rv, s, APLOGNO(00792)
                     "scache_mc: 'retrieve' OVERFLOW");
        return APR_ENOMEM;
    }

    memcpy(dest, data, data_len);
    *destlen = data_len;

    return APR_SUCCESS;
}

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
        ap_log_error(APLOG_MARK, APLOG_DEBUG, rv, s, APLOGNO(00793)
                     "scache_mc: error deleting key '%s' ",
                     buf);
    }

    return rv;
}
