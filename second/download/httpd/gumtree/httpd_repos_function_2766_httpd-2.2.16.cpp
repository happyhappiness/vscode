static apr_status_t dbd_freetds_close(apr_dbd_t *handle)
{
    dbclose(handle->proc);
    return APR_SUCCESS;
}