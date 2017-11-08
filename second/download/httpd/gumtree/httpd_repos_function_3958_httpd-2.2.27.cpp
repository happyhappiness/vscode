apr_status_t apr_socket_accept_filter(apr_socket_t *sock, char *nonconst_name, 
                                      char *nonconst_args)
{
    /* these should have been const; act like they are */
    const char *name = nonconst_name;
    const char *args = nonconst_args;

    struct accept_filter_arg af;
    socklen_t optlen = sizeof(af);

    /* FreeBSD returns an error if the filter is already set; ignore
     * this call if we previously set it to the same value.
     */
    if ((getsockopt(sock->socketdes, SOL_SOCKET, SO_ACCEPTFILTER,
                    &af, &optlen)) == 0) {
        if (!strcmp(name, af.af_name) && !strcmp(args, af.af_arg)) {
            return APR_SUCCESS;
        }
    }

    /* Uhh, at least in FreeBSD 9 the fields are declared as arrays of
     * these lengths; did sizeof not work in some ancient release?
     *
     * FreeBSD kernel sets the last byte to a '\0'.
     */
    apr_cpystrn(af.af_name, name, 16);
    apr_cpystrn(af.af_arg, args, 256 - 16);

    if ((setsockopt(sock->socketdes, SOL_SOCKET, SO_ACCEPTFILTER,
          &af, sizeof(af))) < 0) {
        return errno;
    }
    return APR_SUCCESS;
}