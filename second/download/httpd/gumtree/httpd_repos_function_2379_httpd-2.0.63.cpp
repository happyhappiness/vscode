static apr_status_t vt_ndbm_del(apr_dbm_t *dbm, apr_datum_t key)
{
    apr_status_t rv;
    datum *ckey;

    ckey = (datum*)&key;
    rv = ndbm2s( dbm_delete(dbm->file, *ckey));

    /* store any error info into DBM, and return a status code. */
    return set_error(dbm, rv);
}