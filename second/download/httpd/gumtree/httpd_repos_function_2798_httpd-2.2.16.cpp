static APR_INLINE int odbc_check_rollback(apr_dbd_t *handle)
{
    if (handle->can_commit == APR_DBD_TRANSACTION_ROLLBACK) {
        handle->lasterrorcode = SQL_ERROR;
        strcpy(handle->lastError, "[dbd_odbc] Rollback pending ");
        return 1;
    }
    return 0;
}