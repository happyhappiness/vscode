static void vt_db_close(apr_dbm_t *dbm)
{
    (*GET_BDB(dbm->file)->close)(GET_BDB(dbm->file)
#if DB_VER != 1
                                 , 0
#endif
        );
}