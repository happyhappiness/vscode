apr_status_t apr_socket_shutdown(apr_socket_t *thesocket, 
                                 apr_shutdown_how_e how)
{
    return (shutdown(thesocket->socketdes, how) == -1) ? errno : APR_SUCCESS;
}