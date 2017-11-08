static int vt_gdbm_exists(apr_dbm_t *dbm, apr_datum_t key)
{
    datum *ckey = (datum *)&key;

    return gdbm_exists(dbm->file, *ckey) != 0;
}