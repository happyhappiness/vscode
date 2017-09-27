
    return rv;
}

static void socache_mc_status(ap_socache_instance_t *ctx, request_rec *r, int flags)
{
    /* TODO: Make a mod_status handler. meh. */
}

static apr_status_t socache_mc_iterate(ap_socache_instance_t *instance,
                                       server_rec *s, void *userctx,
                                       ap_socache_iterator_t *iterator,
                                       apr_pool_t *pool)
