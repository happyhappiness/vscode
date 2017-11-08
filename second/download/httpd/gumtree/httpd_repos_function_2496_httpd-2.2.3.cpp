static int vt_ndbm_exists(apr_dbm_t *dbm, apr_datum_t key)
{
    datum *ckey = (datum *)&key;
    datum value;

    value = dbm_fetch( dbm->file, *ckey);

    return value.dptr != NULL;
}