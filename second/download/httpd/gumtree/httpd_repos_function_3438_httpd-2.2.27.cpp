static void closeConnection(apr_socket_t *sock)
{
    apr_size_t len = 0;
    apr_socket_send(sock, NULL, &len);
}