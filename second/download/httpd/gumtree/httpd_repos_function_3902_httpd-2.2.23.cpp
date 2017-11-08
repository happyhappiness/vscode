static apr_status_t socket_cleanup(void *sock)
{
    apr_socket_t *thesocket = sock;
    int sd = thesocket->socketdes;

    /* Set socket descriptor to -1 before close(), so that there is no
     * chance of returning an already closed FD from apr_os_sock_get().
     */
    thesocket->socketdes = -1;

    if (close(sd) == 0) {
        return APR_SUCCESS;
    }
    else {
        /* Restore, close() was not successful. */
        thesocket->socketdes = sd;

        return errno;
    }
}