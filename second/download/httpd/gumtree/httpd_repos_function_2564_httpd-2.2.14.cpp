static void vt_gdbm_close(apr_dbm_t *dbm)
{
    gdbm_close(dbm->file);
}