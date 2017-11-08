static void set_socket_vars(apr_socket_t *sock, int family, int type)
{
    sock->type = type;
    apr_sockaddr_vars_set(sock->local_addr, family, 0);
    apr_sockaddr_vars_set(sock->remote_addr, family, 0);
    sock->netmask = 0;
#if defined(BEOS) && !defined(BEOS_BONE)
    /* BeOS pre-BONE has TCP_NODELAY on by default and it can't be
     * switched off!
     */
    sock->netmask |= APR_TCP_NODELAY;
#endif
}