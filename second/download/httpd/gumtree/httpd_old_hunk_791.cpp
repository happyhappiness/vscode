                                      apr_pool_t *ptrans)
{
    apr_socket_t *csd;
    apr_status_t status;
    int sockdes;

    status = apr_accept(&csd, lr->sd, ptrans);
    if (status == APR_SUCCESS) { 
        *accepted = csd;
        apr_os_sock_get(&sockdes, csd);
        if (sockdes >= FD_SETSIZE) {
            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, NULL,
                         "new file descriptor %d is too large; you probably need "
                         "to rebuild Apache with a larger FD_SETSIZE "
                         "(currently %d)",
                         sockdes, FD_SETSIZE);
            apr_socket_close(csd);
            return APR_EINTR;
        } 
        return status;
    }

    if (APR_STATUS_IS_EINTR(status)) {
        return status;
    }
