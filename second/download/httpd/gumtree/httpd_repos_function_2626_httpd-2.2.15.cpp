static apr_status_t vt_sdbm_store(apr_dbm_t *dbm, apr_datum_t key,
                                  apr_datum_t value)
{
    apr_status_t rv;
    apr_sdbm_datum_t kd, vd;

    kd.dptr = key.dptr;
    kd.dsize = (int)key.dsize;

    vd.dptr = value.dptr;
    vd.dsize = (int)value.dsize;

    rv = apr_sdbm_store(dbm->file, kd, vd, APR_SDBM_REPLACE);

    /* store any error info into DBM, and return a status code. */
    return set_error(dbm, rv);
}