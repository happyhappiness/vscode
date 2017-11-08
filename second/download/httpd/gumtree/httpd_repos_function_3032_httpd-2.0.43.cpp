static void set_socket_vars(apr_socket_t *sock, int family, int type)
{
    sock->type = type;
    apr_sockaddr_vars_set(sock->local_addr, family, 0);
    apr_sockaddr_vars_set(sock->remote_addr, family, 0);
}