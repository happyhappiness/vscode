                 SQLSMALLINT type, SQLHANDLE h, int line)
{
    SQLCHAR buffer[512];
    SQLCHAR sqlstate[128];
    SQLINTEGER native;
    SQLSMALLINT reslength;
    char *res, *p, *end, *logval = NULL;
    int i;

    /* set info about last error in dbc  - fast return for SQL_SUCCESS  */
    if (rc == SQL_SUCCESS) {
        char successMsg[] = "[dbd_odbc] SQL_SUCCESS ";
        apr_size_t successMsgLen = sizeof successMsg - 1;

        dbc->lasterrorcode = SQL_SUCCESS;
        apr_cpystrn(dbc->lastError, successMsg, sizeof dbc->lastError);
        apr_cpystrn(dbc->lastError + successMsgLen, step,
                    sizeof dbc->lastError - successMsgLen);
        return;
    }
    switch (rc) {
    case SQL_INVALID_HANDLE:
        res = "SQL_INVALID_HANDLE";
        break;
    case SQL_ERROR:
        res = "SQL_ERROR";
        break;
    case SQL_SUCCESS_WITH_INFO:
        res = "SQL_SUCCESS_WITH_INFO";
        break;
    case SQL_STILL_EXECUTING:
        res = "SQL_STILL_EXECUTING";
        break;
    case SQL_NEED_DATA:
        res = "SQL_NEED_DATA";
        break;
    case SQL_NO_DATA:
        res = "SQL_NO_DATA";
        break;
    default:
        res = "unrecognized SQL return code";
    }
    /* these two returns are expected during normal execution */
    if (rc != SQL_SUCCESS_WITH_INFO && rc != SQL_NO_DATA 
        && dbc->can_commit != APR_DBD_TRANSACTION_IGNORE_ERRORS) {
        dbc->can_commit = APR_DBD_TRANSACTION_ROLLBACK;
    }
    p = dbc->lastError;
    end = p + sizeof(dbc->lastError);
    dbc->lasterrorcode = rc;
    p += sprintf(p, "[dbd_odbc] %.64s returned %.30s (%d) at %.24s:%d ",
                 step, res, rc, SOURCE_FILE, line - 1);
    for (i = 1, rc = 0; rc == 0; i++) {
        rc = SQLGetDiagRec(type, h, i, sqlstate, &native, buffer, 
                            sizeof(buffer), &reslength);
        if (SQL_SUCCEEDED(rc) && (p < (end - 280))) 
            p += sprintf(p, "%.256s %.20s ", buffer, sqlstate);
    }
    apr_env_get(&logval, "apr_dbd_odbc_log", dbc->pool);
    /* if env var was set or call was init/open (no dbname) - log to stderr */
    if (logval || !dbc->dbname ) {
        char timestamp[APR_CTIME_LEN];

        apr_file_t *se;
        apr_ctime(timestamp, apr_time_now());
        apr_file_open_stderr(&se, dbc->pool);
        apr_file_printf(se, "[%s] %s\n", timestamp, dbc->lastError);
    }
}
