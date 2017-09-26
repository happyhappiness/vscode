 * us all the error-handling in one place.
 */
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
#if APR_HAS_THREADS
static apr_status_t dbd_destruct(void *sql, void *params, apr_pool_t *pool)
{
    ap_dbd_t *rec = sql;
    return apr_dbd_close(rec->driver, rec->handle);
}

static apr_status_t dbd_setup(apr_pool_t *pool, server_rec *s)
{
    svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
    apr_status_t rv = apr_reslist_create(&svr->dbpool, svr->nmin, svr->nkeep,
                                         svr->nmax, svr->exptime,
                                         dbd_construct, dbd_destruct,
                                         svr, pool);
    if (rv == APR_SUCCESS) {
        apr_pool_cleanup_register(pool, svr->dbpool,
                                  (void*)apr_reslist_destroy,
                                  apr_pool_cleanup_null);
    }
    else {
        ap_log_perror(APLOG_MARK, APLOG_CRIT, 0, pool,
                      "DBD Pool: failed to initialise");
    }
    return rv;
}

#endif


/* Functions we export for modules to use:
        - open acquires a connection from the pool (opens one if necessary)
        - close releases it back in to the pool
*/
AP_DECLARE(void) ap_dbd_close(server_rec *s, ap_dbd_t *sql)
{
    svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
    if (!svr->persist) {
        apr_dbd_close(sql->driver, sql->handle);
    }
#if APR_HAS_THREADS
    else {
        apr_reslist_release(svr->dbpool, sql);
    }
#endif
}
static apr_status_t dbd_close(void *CONN)
{
    ap_dbd_t *conn = CONN;
    return apr_dbd_close(conn->driver, conn->handle);
}
#define arec ((ap_dbd_t*)rec)
#if APR_HAS_THREADS
AP_DECLARE(ap_dbd_t*) ap_dbd_open(apr_pool_t *pool, server_rec *s)
{
    void *rec = NULL;
    svr_cfg *svr = ap_get_module_config(s->module_config, &dbd_module);
    apr_status_t rv = APR_SUCCESS;
    const char *errmsg;

