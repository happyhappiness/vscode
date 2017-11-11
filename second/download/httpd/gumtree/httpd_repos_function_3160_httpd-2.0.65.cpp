apr_status_t apr_socket_atmark(apr_socket_t *sock, int *atmark)
{
/* In 1.0 we rely on compile failure to assure all platforms grabbed
 * the correct header file support for SIOCATMARK, but we don't want 
 * to fail the build of 0.9.  Keep things good for the released branch.
 */
#ifdef SIOCATMARK
    int oobmark;

    if (ioctl(sock->socketdes, SIOCATMARK, (void*) &oobmark) < 0)
        return apr_get_netos_error();

    *atmark = (oobmark != 0);

    return APR_SUCCESS;
#else
    return APR_ENOTIMPL;
#endif
}