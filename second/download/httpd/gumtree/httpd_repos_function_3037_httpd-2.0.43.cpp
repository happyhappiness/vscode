apr_status_t sononblock(SOCKET sd)
{
    u_long one = 1;

    if (ioctlsocket(sd, FIONBIO, &one) == SOCKET_ERROR) {
        return apr_get_netos_error();
    }
    return APR_SUCCESS;
}