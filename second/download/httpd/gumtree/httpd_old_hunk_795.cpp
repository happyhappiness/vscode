
AP_DECLARE(apr_status_t) unixd_accept(void **accepted, ap_listen_rec *lr,
                                        apr_pool_t *ptrans)
{
    apr_socket_t *csd;
    apr_status_t status;

    *accepted = NULL;
    status = apr_accept(&csd, lr->sd, ptrans);
    if (status == APR_SUCCESS) { 
        *accepted = csd;
        return APR_SUCCESS;
    }

    if (APR_STATUS_IS_EINTR(status)) {
        return status;
    }
