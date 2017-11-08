apr_status_t apr_socket_atmark(apr_socket_t *sock, int *atmark)
{
#ifndef BEOS_R5
    int oobmark;

    if (ioctl(sock->socketdes, SIOCATMARK, (void*) &oobmark) < 0)
        return apr_get_netos_error();

    *atmark = (oobmark != 0);

    return APR_SUCCESS;
#else /* BEOS_R5 */
    return APR_ENOTIMPL;
#endif
}