static apr_status_t dbd_close(void *data)
{
    ap_dbd_t *rec = data;

    return apr_dbd_close(rec->driver, rec->handle);
}