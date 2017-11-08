static apr_status_t dbd_sqlite3_close(apr_dbd_t *handle)
{
    sqlite3_close(handle->conn);
    apr_thread_mutex_destroy(handle->mutex);
    return APR_SUCCESS;
}