static void* odbc_native_handle(apr_dbd_t *handle)
{   return handle->dbc;
}