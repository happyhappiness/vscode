static apr_status_t odbc_close_cleanup(void *handle)
{
    return odbc_close((apr_dbd_t *)handle);
}