static apr_status_t socket_cleanup(void *sock)
{
    apr_socket_t *thesocket = sock;

    if (close(thesocket->socketdes) == 0) {
        thesocket->socketdes = -1;
        return APR_SUCCESS;
    }
    else {
        return errno;
    }
}