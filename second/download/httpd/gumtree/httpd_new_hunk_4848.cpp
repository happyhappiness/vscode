    /* make the IOCTL call */
    rcode = WSAIoctl(sock, SO_TLS_SET_CLIENT, &sWS2Opts,
                     sizeof(struct tlsclientopts), NULL, 0, NULL,
                     NULL, NULL);

    /* make sure that it was successful */
    if (SOCKET_ERROR == rcode ) {
    ap_log_error(APLOG_MARK, APLOG_ERR, 0, c->base_server, APLOGNO(02125)
                 "Error: %d with WSAIoctl(SO_TLS_SET_CLIENT)",
                 WSAGetLastError());
    }
    return rcode;
}

static int SSLize_Socket(SOCKET socketHnd, char *key, request_rec *r)
{
    int rcode;
    struct tlsserveropts sWS2Opts;
