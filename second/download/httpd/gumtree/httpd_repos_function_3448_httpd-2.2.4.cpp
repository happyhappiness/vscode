apr_status_t soblock(SOCKET sd)
{
    u_long zero = 0;

    if (ioctlsocket(sd, FIONBIO, &zero) == SOCKET_ERROR) {
        return apr_get_netos_error();
    }
    return APR_SUCCESS;
}