static apr_status_t vt_sdbm_del(apr_dbm_t *dbm, apr_datum_t key)
{
    apr_status_t rv;
    apr_sdbm_datum_t kd;

    kd.dptr = key.dptr;
    kd.dsize = (int)key.dsize;

    rv = apr_sdbm_delete(dbm->file, kd);

    /* store any error info into DBM, and return a status code. */
    return set_error(dbm, rv);
}