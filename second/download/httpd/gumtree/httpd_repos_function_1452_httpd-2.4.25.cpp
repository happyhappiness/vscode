static apr_status_t dbd_prepared_init(apr_pool_t *pool, dbd_cfg_t *cfg,
                                      ap_dbd_t *rec)
{
    apr_hash_index_t *hi;

    rec->prepared = apr_hash_make(pool);

    for (hi = apr_hash_first(pool, cfg->queries); hi;
         hi = apr_hash_next(hi)) {
        const char *label, *query;
        apr_dbd_prepared_t *stmt;

        apr_hash_this(hi, (void*) &label, NULL, (void*) &query);

        if (!strcmp(query, "")) {
            continue;
        }

        stmt = NULL;
        if (apr_dbd_prepare(rec->driver, pool, rec->handle, query,
                            label, &stmt)) {
            return APR_EGENERAL;
        }
        else {
            apr_hash_set(rec->prepared, label, APR_HASH_KEY_STRING, stmt);
        }
    }

    return APR_SUCCESS;
}