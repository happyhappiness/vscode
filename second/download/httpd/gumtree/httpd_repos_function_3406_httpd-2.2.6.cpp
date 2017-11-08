static apr_status_t mcast_check_type(apr_socket_t *sock)
{
    int type;
    apr_status_t rv;

    rv = apr_socket_type_get(sock, &type);

    if (rv != APR_SUCCESS) {
        return rv;
    }
    else if (type == SOCK_DGRAM || type == SOCK_RAW) {
        return APR_SUCCESS;
    }
    else {
        return APR_ENOTIMPL;
    }
}