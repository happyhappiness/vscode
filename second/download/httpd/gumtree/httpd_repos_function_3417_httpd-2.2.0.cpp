apr_status_t apr_gethostname(char *buf, apr_int32_t len, apr_pool_t *cont)
{
#ifdef BEOS_R5
    if (gethostname(buf, len) == 0) {
#else
    if (gethostname(buf, len) != 0) {
#endif  
        buf[0] = '\0';
        return errno;
    }
    else if (!memchr(buf, '\0', len)) { /* buffer too small */
        /* note... most platforms just truncate in this condition
         *         linux+glibc return an error
         */
        buf[0] = '\0';
        return APR_ENAMETOOLONG;
    }
    return APR_SUCCESS;
}

#if APR_HAS_SO_ACCEPTFILTER
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