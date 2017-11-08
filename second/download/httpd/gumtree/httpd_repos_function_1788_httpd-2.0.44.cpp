static void find_default_family(apr_pool_t *p)
{
#if APR_HAVE_IPV6
    /* We know the platform supports IPv6, but this particular
     * system may not have IPv6 enabled.  See if we can get an
     * AF_INET6 socket and bind to an ephemeral port.  (On most
     * systems, getting an AF_INET6 socket is a sufficient test.
     * On certain levels of OpenUNIX, getting the socket is
     * successful but bind always returns ENETUNREACH.)
     */
    if (default_family == APR_UNSPEC) {
        apr_status_t sock_rv;
        apr_socket_t *tmp_sock;
        apr_sockaddr_t *sa;

        if ((sock_rv = apr_socket_create(&tmp_sock, APR_INET6, SOCK_STREAM, p)) 
            == APR_SUCCESS &&
            apr_sockaddr_info_get(&sa, NULL, APR_INET6, 0, 0, p) == APR_SUCCESS &&
            apr_bind(tmp_sock, sa) == APR_SUCCESS) { 
            default_family = APR_INET6;
        }
        else {
            default_family = APR_INET;
        }
        if (sock_rv == APR_SUCCESS) {
            apr_socket_close(tmp_sock);
        }
    }
#endif
}