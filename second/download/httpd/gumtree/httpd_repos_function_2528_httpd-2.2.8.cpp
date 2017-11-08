static apr_status_t vt_ndbm_store(apr_dbm_t *dbm, apr_datum_t key,
                                  apr_datum_t value)
{
    apr_status_t rv;
    datum *ckey;
    datum *cvalue;

    ckey =  (datum*)&key;
    cvalue = (datum*)&value;
    rv = ndbm2s( dbm_store( dbm->file, *ckey, *cvalue, DBM_REPLACE));

    /* store any error info into DBM, and return a status code. */
    return set_error(dbm, rv);
}