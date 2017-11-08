static apr_status_t dbd_sqlite3_close(apr_dbd_t *handle)
{
    apr_dbd_prepared_t *prep = handle->prep;

    /* finalize all prepared statements, or we'll get SQLITE_BUSY on close */
    while (prep) {
        sqlite3_finalize(prep->stmt);
        prep = prep->next;
    }

    sqlite3_close(handle->conn);
#if APR_HAS_THREADS
    apr_thread_mutex_destroy(handle->mutex);
#endif
    return APR_SUCCESS;
}