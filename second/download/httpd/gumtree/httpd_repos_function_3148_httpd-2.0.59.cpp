static apr_status_t socket_cleanup(void *sock)
{
    apr_socket_t *thesocket = sock;

    if (thesocket->socketdes < 0) {
        return APR_EINVALSOCK;
    }

    if (soclose(thesocket->socketdes) == 0) {
        thesocket->socketdes = -1;
        return APR_SUCCESS;
    }
    else {
        return APR_OS2_STATUS(sock_errno());
    }
}