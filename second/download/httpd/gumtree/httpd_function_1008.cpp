static apr_status_t beos_accept(void **accepted, ap_listen_rec *lr, apr_pool_t *ptrans)
{
    apr_socket_t *csd;
    apr_status_t status;
    int sockdes;

    *accepted = NULL;
    status = apr_socket_accept(&csd, lr->sd, ptrans);
    if (status == APR_SUCCESS) {
        *accepted = csd;
        apr_os_sock_get(&sockdes, csd);
        return status;
    }

    if (APR_STATUS_IS_EINTR(status)) {
        return status;
    }
        /* This switch statement provides us with better error details. */
    switch (status) {
#ifdef ECONNABORTED
        case ECONNABORTED:
#endif
#ifdef ETIMEDOUT
        case ETIMEDOUT:
#endif
#ifdef EHOSTUNREACH
        case EHOSTUNREACH:
#endif
#ifdef ENETUNREACH
        case ENETUNREACH:
#endif
            break;
#ifdef ENETDOWN
        case ENETDOWN:
            /*
             * When the network layer has been shut down, there
             * is not much use in simply exiting: the parent
             * would simply re-create us (and we'd fail again).
             * Use the CHILDFATAL code to tear the server down.
             * @@@ Martin's idea for possible improvement:
             * A different approach would be to define
             * a new APEXIT_NETDOWN exit code, the reception
             * of which would make the parent shutdown all
             * children, then idle-loop until it detected that
             * the network is up again, and restart the children.
             * Ben Hyde noted that temporary ENETDOWN situations
             * occur in mobile IP.
             */
            ap_log_error(APLOG_MARK, APLOG_EMERG, status, ap_server_conf,
                         "apr_socket_accept: giving up.");
            return APR_EGENERAL;
#endif /*ENETDOWN*/

        default:
            ap_log_error(APLOG_MARK, APLOG_ERR, status, ap_server_conf,
                         "apr_socket_accept: (client socket)");
            return APR_EGENERAL;
    }
    return status;
}