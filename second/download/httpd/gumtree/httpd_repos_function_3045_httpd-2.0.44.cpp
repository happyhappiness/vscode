static apr_status_t socket_cleanup(void *sock)
{
    apr_socket_t *thesocket = sock;

    if (thesocket->socketdes != INVALID_SOCKET) {
        if (closesocket(thesocket->socketdes) == SOCKET_ERROR) {
            return apr_get_netos_error();
        }
        thesocket->socketdes = INVALID_SOCKET;
    }
    return APR_SUCCESS;
}