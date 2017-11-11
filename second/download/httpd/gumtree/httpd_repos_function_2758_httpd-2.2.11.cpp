static const char* odbc_error(apr_dbd_t *handle, int errnum)
{   
    return (handle) ? handle->lastError : "[dbd_odbc]No error message available";
}