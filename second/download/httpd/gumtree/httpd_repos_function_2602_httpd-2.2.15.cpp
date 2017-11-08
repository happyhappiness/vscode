static apr_status_t vt_ndbm_del(apr_dbm_t *dbm, apr_datum_t key)
{
    int rc;
    datum kd;

    kd.dptr = key.dptr;
    kd.dsize = key.dsize;

    rc = dbm_delete(dbm->file, kd);

    /* store any error info into DBM, and return a status code. */
    return set_error(dbm, ndbm2s(rc));
}