apr_status_t apr_bind(apr_socket_t *sock, apr_sockaddr_t *sa)
{
    return apr_socket_bind(sock, sa);
}