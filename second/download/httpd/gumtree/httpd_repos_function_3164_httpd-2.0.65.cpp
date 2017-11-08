apr_status_t apr_socket_accept_filter(apr_socket_t *sock, char *name, 
                                      char *args)
{
    struct accept_filter_arg af;
    strncpy(af.af_name, name, 16);
    strncpy(af.af_arg, args, 256 - 16);

    if ((setsockopt(sock->socketdes, SOL_SOCKET, SO_ACCEPTFILTER,
          &af, sizeof(af))) < 0) {
        return errno;
    }
    return APR_SUCCESS;
}