static char *lookup_map_dbd(request_rec *r, char *key, const char *label)
{
    apr_status_t rv;
    apr_dbd_prepared_t *stmt;
    const char *errmsg;
    apr_dbd_results_t *res = NULL;
    apr_dbd_row_t *row = NULL;
    char *ret = NULL;
    int n = 0;
    ap_dbd_t *db = dbd_acquire(r);
    
    if (db == NULL) {
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(02963)
                      "rewritemap: No db handle available! "
                      "Check your database access");
        return NULL;
   }

    stmt = apr_hash_get(db->prepared, label, APR_HASH_KEY_STRING);

    rv = apr_dbd_pvselect(db->driver, r->pool, db->handle, &res,
                          stmt, 0, key, NULL);
    if (rv != 0) {
        errmsg = apr_dbd_error(db->driver, db->handle, rv);
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00657)
                      "rewritemap: error %s querying for %s", errmsg, key);
        return NULL;
    }
    while ((rv = apr_dbd_get_row(db->driver, r->pool, res, &row, -1)) == 0) {
        ++n;
        if (ret == NULL) {
            ret = apr_pstrdup(r->pool,
                              apr_dbd_get_entry(db->driver, row, 0));
        }
        else {
            /* randomise crudely amongst multiple results */
            if ((double)rand() < (double)RAND_MAX/(double)n) {
                ret = apr_pstrdup(r->pool,
                                  apr_dbd_get_entry(db->driver, row, 0));
            }
        }
    }
    if (rv != -1) {
        errmsg = apr_dbd_error(db->driver, db->handle, rv);
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r, APLOGNO(00658)
                      "rewritemap: error %s looking up %s", errmsg, key);
    }
    switch (n) {
    case 0:
        return NULL;
    case 1:
        return ret;
    default:
        /* what's a fair rewritelog level for this? */
        rewritelog((r, 3, NULL, "Multiple values found for %s", key));
        return ret;
    }
}