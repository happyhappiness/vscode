static apr_status_t dbd_close(void *CONN)
{
    ap_dbd_t *conn = CONN;
    return apr_dbd_close(conn->driver, conn->handle);
}