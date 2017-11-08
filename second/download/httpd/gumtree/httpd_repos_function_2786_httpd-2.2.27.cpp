static void *dbd_freetds_native(apr_dbd_t *handle)
{
    return handle->proc;
}