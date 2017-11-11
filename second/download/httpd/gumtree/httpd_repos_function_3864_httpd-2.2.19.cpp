apr_status_t apr_socket_listen(apr_socket_t *sock, apr_int32_t backlog)
{
    if (listen(sock->socketdes, backlog) == -1)
        return errno;
    else
        return APR_SUCCESS;
}