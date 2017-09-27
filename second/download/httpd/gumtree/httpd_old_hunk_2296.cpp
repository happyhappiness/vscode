    ap_rprintf(r, "cache type: <b>DBM</b>, maximum size: <b>unlimited</b><br>");
    ap_rprintf(r, "current entries: <b>%d</b>, current size: <b>%ld</b> bytes<br>", elts, size);
    ap_rprintf(r, "average entry size: <b>%d</b> bytes<br>", avg);
    return;
}

static apr_status_t socache_dbm_iterate(ap_socache_instance_t *instance,
                                        server_rec *s,
                                        ap_socache_iterator_t *iterator,
                                        apr_pool_t *pool)
{
    return APR_ENOTIMPL;
}

static const ap_socache_provider_t socache_dbm = {
    "dbm",
    AP_SOCACHE_FLAG_NOTMPSAFE,
    socache_dbm_create,
