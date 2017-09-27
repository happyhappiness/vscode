    }

    /* In APR-util - unclear what 'timeout' is, as it was not implemented */
    rv = apr_memcache_set(ctx->mc, buf, (char*)ucaData, nData, 0, 0);

    if (rv != APR_SUCCESS) {
        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s, APLOGNO(00790)
                     "scache_mc: error setting key '%s' "
                     "with %d bytes of data", buf, nData);
        return rv;
    }

    return APR_SUCCESS;
}

static apr_status_t socache_mc_retrieve(ap_socache_instance_t *ctx, server_rec *s,
                                        const unsigned char *id, unsigned int idlen,
                                        unsigned char *dest, unsigned int *destlen,
                                        apr_pool_t *p)
{
    apr_size_t data_len;
    char buf[MC_KEY_LEN], *data;
