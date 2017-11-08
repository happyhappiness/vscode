static apr_status_t socket_cleanup(void *sock)
{
    apr_socket_t *thesocket = sock;

    if (thesocket->socketdes != INVALID_SOCKET) {
        if (closesocket(thesocket->socketdes) == SOCKET_ERROR) {
            return apr_get_netos_error();
        }
        thesocket->socketdes = INVALID_SOCKET;
    }
#if APR_HAS_SENDFILE
    if (thesocket->overlapped) {
        CloseHandle(thesocket->overlapped->hEvent);
        thesocket->overlapped = NULL;
    }
#endif
    return APR_SUCCESS;
}