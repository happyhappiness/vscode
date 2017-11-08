static int vt_gdbm_exists(apr_dbm_t *dbm, apr_datum_t key)
{
    datum kd;

    kd.dptr = key.dptr;
    kd.dsize = key.dsize;

    return gdbm_exists(dbm->file, kd) != 0;
}