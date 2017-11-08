static int vt_ndbm_exists(apr_dbm_t *dbm, apr_datum_t key)
{
    datum kd, rd;

    kd.dptr = key.dptr;
    kd.dsize = key.dsize;

    rd = dbm_fetch(dbm->file, kd);

    return rd.dptr != NULL;
}