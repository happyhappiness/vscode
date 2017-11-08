static void odbc_init(apr_pool_t *pool)
{
    SQLRETURN rc;
    char *step;
    apr_version_t apuver;
    
    apu_version(&apuver);
    if (apuver.major != DRIVER_APU_VERSION_MAJOR 
        || apuver.minor != DRIVER_APU_VERSION_MINOR) {
            apr_file_t *se;

            apr_file_open_stderr(&se, pool);
            apr_file_printf(se, "Incorrect " ODBC_DRIVER_STRING " dbd driver version\n"
                "Attempt to load APU version %d.%d driver with APU version %d.%d\n",
                DRIVER_APU_VERSION_MAJOR, DRIVER_APU_VERSION_MINOR, 
                apuver.major, apuver.minor);
        abort();
    }

    if (henv) 
        return;

    step = "SQLAllocHandle (SQL_HANDLE_ENV)";
    rc = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &henv);
    apr_pool_cleanup_register(pool, henv, odbc_close_env, apr_pool_cleanup_null);
    if (SQL_SUCCEEDED(rc)) {
        step = "SQLSetEnvAttr";
        rc = SQLSetEnvAttr(henv,SQL_ATTR_ODBC_VERSION,
                          (SQLPOINTER)SQL_OV_ODBC3, 0);
    }
    else {
        apr_dbd_t tmp_dbc;
        SQLHANDLE err_h = henv;

        tmp_dbc.pool = pool;
        tmp_dbc.dbname = NULL;
        CHECK_ERROR(&tmp_dbc, step, rc, SQL_HANDLE_ENV, err_h);
    }
}