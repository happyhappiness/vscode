    }

    apr_dbm_close(dbmfp);

    return value;
}
static char *lookup_map_dbd(request_rec *r, char *key, const char *label)
{
    apr_status_t rv;
    apr_dbd_prepared_t *stmt;
    const char *errmsg;
    apr_dbd_results_t *res = NULL;
    apr_dbd_row_t *row = NULL;
    const char *ret = NULL;
    int n = 0;
    ap_dbd_t *db = dbd_acquire(r);

    stmt = apr_hash_get(db->prepared, label, APR_HASH_KEY_STRING);

    rv = apr_dbd_pvselect(db->driver, r->pool, db->handle, &res,
                          stmt, 0, key, NULL);
    if (rv != 0) {
        errmsg = apr_dbd_error(db->driver, db->handle, rv);
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "rewritemap: error %s querying for %s", errmsg, key);
        return NULL;
    }
    while (rv = apr_dbd_get_row(db->driver, r->pool, res, &row, -1), rv == 0) {
        ++n;
        if (ret == NULL) {
            ret = apr_dbd_get_entry(db->driver, row, 0);
        }
        else {
            /* randomise crudely amongst multiple results */
            if ((double)rand() < (double)RAND_MAX/(double)n) {
                ret = apr_dbd_get_entry(db->driver, row, 0);
            }
        }
    }
    if (rv != -1) {
        errmsg = apr_dbd_error(db->driver, db->handle, rv);
        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
                      "rewritemap: error %s looking up %s", errmsg, key);
    }
    switch (n) {
    case 0:
        return NULL;
    case 1:
        return apr_pstrdup(r->pool, ret);
    default:
        /* what's a fair rewritelog level for this? */
        rewritelog((r, 3, NULL, "Multiple values found for %s", key));
        return apr_pstrdup(r->pool, ret);
    }
}

static char *lookup_map_program(request_rec *r, apr_file_t *fpin,
                                apr_file_t *fpout, char *key)
{
    char *buf;
    char c;
