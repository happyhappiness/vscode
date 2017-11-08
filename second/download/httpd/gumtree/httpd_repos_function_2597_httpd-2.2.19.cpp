static apr_status_t vt_gdbm_store(apr_dbm_t *dbm, apr_datum_t key,
                                  apr_datum_t value)
{
    int rc;
    datum kd, vd;

    kd.dptr = key.dptr;
    kd.dsize = key.dsize;

    vd.dptr = value.dptr;
    vd.dsize = value.dsize;

    rc = gdbm_store(dbm->file, kd, vd, GDBM_REPLACE);

    /* store any error info into DBM, and return a status code. */
    return set_error(dbm, g2s(rc));
}