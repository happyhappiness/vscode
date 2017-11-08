apr_status_t apr_connect(apr_socket_t *sock, apr_sockaddr_t *sa)
{
    return apr_socket_connect(sock, sa);
}