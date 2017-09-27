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

static char *lookup_map_program(request_rec *r, apr_file_t *fpin,
                                apr_file_t *fpout, char *key)
{
