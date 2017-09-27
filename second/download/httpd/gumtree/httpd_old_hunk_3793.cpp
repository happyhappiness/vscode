    const char *errmsg;
    apr_dbd_results_t *res = NULL;
    apr_dbd_row_t *row = NULL;
    char *ret = NULL;
    int n = 0;
    ap_dbd_t *db = dbd_acquire(r);

    stmt = apr_hash_get(db->prepared, label, APR_HASH_KEY_STRING);

    rv = apr_dbd_pvselect(db->driver, r->pool, db->handle, &res,
                          stmt, 0, key, NULL);
    if (rv != 0) {
