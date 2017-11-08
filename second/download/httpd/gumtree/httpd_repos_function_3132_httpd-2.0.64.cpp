apr_status_t apr_shutdown(apr_socket_t *thesocket, apr_shutdown_how_e how)
{
    return apr_socket_shutdown(thesocket, how);
}