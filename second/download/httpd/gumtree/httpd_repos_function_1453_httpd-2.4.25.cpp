static apr_status_t dbd_init_sql_init(apr_pool_t *pool, dbd_cfg_t *cfg,
                                      ap_dbd_t *rec)
{
    int i;
    apr_status_t rv = APR_SUCCESS;

    for (i = 0; i < cfg->init_queries->nelts; i++) {
        int nrows;
        char **query_p;

        query_p = (char **)cfg->init_queries->elts + i;

        if (apr_dbd_query(rec->driver, rec->handle, &nrows, *query_p)) {
            rv = APR_EGENERAL;
            break;
        }
    }

    return rv;
}