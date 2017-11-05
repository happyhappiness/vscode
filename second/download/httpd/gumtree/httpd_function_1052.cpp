static apr_status_t dbd_construct(void **db, void *params, apr_pool_t *pool)
{
    svr_cfg *svr = (svr_cfg*) params;
    ap_dbd_t *rec = apr_pcalloc(pool, sizeof(ap_dbd_t));
    apr_status_t rv = apr_dbd_get_driver(pool, svr->name, &rec->driver);

/* Error-checking get_driver isn't necessary now (because it's done at
 * config-time).  But in case that changes in future ...
 */
    switch (rv) {
    case APR_ENOTIMPL:
        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, pool,
                      "DBD: driver for %s not available", svr->name);
        return rv;
    case APR_EDSOOPEN:
        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, pool,
                      "DBD: can't find driver for %s", svr->name);
        return rv;
    case APR_ESYMNOTFOUND:
        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, pool,
                      "DBD: driver for %s is invalid or corrupted", svr->name);
        return rv;
    default:
        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, pool,
                      "DBD: mod_dbd not compatible with apr in get_driver");
        return rv;
    case APR_SUCCESS:
        break;
    }

    rv = apr_dbd_open(rec->driver, pool, svr->params, &rec->handle);
    switch (rv) {
    case APR_EGENERAL:
        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, pool,
                      "DBD: Can't connect to %s[%s]", svr->name, svr->params);
        return rv;
    default:
        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, pool,
                      "DBD: mod_dbd not compatible with apr in open");
        return rv;
    case APR_SUCCESS:
        break;
    }
    *db = rec;
    rv = dbd_prepared_init(pool, svr, rec);
    return rv;
}