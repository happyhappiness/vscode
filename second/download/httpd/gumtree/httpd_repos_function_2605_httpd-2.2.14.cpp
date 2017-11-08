static int vt_sdbm_exists(apr_dbm_t *dbm, apr_datum_t key)
{
    int exists;
    apr_sdbm_datum_t vd, kd;

    kd.dptr = key.dptr;
    kd.dsize = (int)key.dsize;

    if (apr_sdbm_fetch(dbm->file, &vd, kd) != APR_SUCCESS)
        exists = 0;
    else
        exists = vd.dptr != NULL;

    return exists;
}