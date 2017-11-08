static apr_status_t dbd_sqlite3_close(apr_dbd_t *handle)
{
    apr_dbd_prepared_t *prep = handle->prep;

    /* finalize all prepared statements, or we'll get SQLITE_BUSY on close */
    while (prep) {
        sqlite3_finalize(prep->stmt);
        prep = prep->next;
    }

    sqlite3_close(handle->conn);
    return APR_SUCCESS;
}