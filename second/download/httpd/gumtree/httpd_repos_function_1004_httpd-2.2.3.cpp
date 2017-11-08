static apr_status_t dbd_prepared_init(apr_pool_t *pool, svr_cfg *svr,
                                      ap_dbd_t *dbd)
{
    dbd_prepared *p;
    apr_status_t ret = APR_SUCCESS;
    apr_dbd_prepared_t *stmt;
    dbd->prepared = apr_hash_make(pool);

    for (p = svr->prepared; p; p = p->next) {
        stmt = NULL;
        if (apr_dbd_prepare(dbd->driver, pool, dbd->handle, p->query,
                            p->label, &stmt) == 0) {
            apr_hash_set(dbd->prepared, p->label, APR_HASH_KEY_STRING, stmt);
        }
        else {
            ret = APR_EGENERAL;
        }
    }
    return ret;
}