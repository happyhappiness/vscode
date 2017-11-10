static apr_status_t vt_db_store(apr_dbm_t *dbm, apr_datum_t key,
                                apr_datum_t value)
{
    apr_status_t rv;
    DBT ckey = { 0 };
    DBT cvalue = { 0 };

    ckey.data = key.dptr;
    ckey.size = key.dsize;

    cvalue.data = value.dptr;
    cvalue.size = value.dsize;

    rv = db2s((*GET_BDB(dbm->file)->put)(GET_BDB(dbm->file),
                                         TXN_ARG
                                         &ckey,
                                         &cvalue,
                                         0));

    /* store any error info into DBM, and return a status code. */
    return set_error(dbm, rv);
}