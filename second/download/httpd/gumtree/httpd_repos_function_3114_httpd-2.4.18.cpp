static int APR_THREAD_FUNC regfnReadClient(isapi_cid    *cid,
                                           void         *buf_data,
                                           apr_uint32_t *buf_size)
{
    request_rec *r = cid->r;
    apr_uint32_t read = 0;
    int res = 0;

    if (r->remaining < *buf_size) {
        *buf_size = (apr_size_t)r->remaining;
    }

    while (read < *buf_size &&
           ((res = ap_get_client_block(r, (char*)buf_data + read,
                                       *buf_size - read)) > 0)) {
        read += res;
    }

    *buf_size = read;
    if (res < 0) {
        apr_set_os_error(APR_FROM_OS_ERROR(ERROR_READ_FAULT));
    }
    return (res >= 0);
}