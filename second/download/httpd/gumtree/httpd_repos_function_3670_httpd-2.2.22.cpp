static apr_status_t create_socket_pipe(SOCKET *rd, SOCKET *wr)
{
    static int id = 0;
    FD_SET rs;
    SOCKET ls;
    struct timeval socktm;
    struct sockaddr_in pa;
    struct sockaddr_in la;
    struct sockaddr_in ca;
    int nrd;
    apr_status_t rv = APR_SUCCESS;
    int ll = sizeof(la);
    int lc = sizeof(ca);
    unsigned long bm = 1;
    int uid[2];
    int iid[2];

    *rd = INVALID_SOCKET;
    *wr = INVALID_SOCKET;

    /* Create the unique socket identifier
     * so that we know the connection originated
     * from us.
     */
    uid[0] = getpid();
    uid[1] = id++;
    if ((ls = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        return apr_get_netos_error();
    }

    pa.sin_family = AF_INET;
    pa.sin_port   = 0;
    pa.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(ls, (SOCKADDR *)&pa, sizeof(pa)) == SOCKET_ERROR) {
        rv =  apr_get_netos_error();
        goto cleanup;
    }
    if (getsockname(ls, (SOCKADDR *)&la, &ll) == SOCKET_ERROR) {
        rv =  apr_get_netos_error();
        goto cleanup;
    }
    if (listen(ls, 1) == SOCKET_ERROR) {
        rv =  apr_get_netos_error();
        goto cleanup;
    }
    if ((*wr = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET) {
        rv = apr_get_netos_error();
        goto cleanup;
    }
    if (connect(*wr, (SOCKADDR *)&la, sizeof(la)) == SOCKET_ERROR) {
        rv =  apr_get_netos_error();
        goto cleanup;
    }
    if (send(*wr, (char *)uid, sizeof(uid), 0) != sizeof(uid)) {
        if ((rv =  apr_get_netos_error()) == 0) {
            rv = APR_EINVAL;
        }
        goto cleanup;
    }
    if (ioctlsocket(ls, FIONBIO, &bm) == SOCKET_ERROR) {
        rv = apr_get_netos_error();
        goto cleanup;
    }
    for (;;) {
        int ns;
        int nc = 0;
        /* Listening socket is nonblocking by now.
         * The accept should create the socket
         * immediatelly because we are connected already.
         * However on buys systems this can take a while
         * until winsock gets a chance to handle the events.
         */
        FD_ZERO(&rs);
        FD_SET(ls, &rs);

        socktm.tv_sec  = 1;
        socktm.tv_usec = 0;
        if ((ns = select(0, &rs, NULL, NULL, &socktm)) == SOCKET_ERROR) {
            /* Accept still not signaled */
            Sleep(100);
            continue;
        }
        if (ns == 0) {
            /* No connections in the last second */
            continue;
        }
        if ((*rd = accept(ls, (SOCKADDR *)&ca, &lc)) == INVALID_SOCKET) {
            rv =  apr_get_netos_error();
            goto cleanup;
        }
        /* Verify the connection by reading the send identification.
         */
        do {
            if (nc++)
                Sleep(1);
            nrd = recv(*rd, (char *)iid, sizeof(iid), 0);
            rv = nrd == SOCKET_ERROR ? apr_get_netos_error() : APR_SUCCESS;
        } while (APR_STATUS_IS_EAGAIN(rv));

        if (nrd == sizeof(iid)) {
            if (memcmp(uid, iid, sizeof(uid)) == 0) {
                /* Wow, we recived what we send.
                 * Put read side of the pipe to the blocking
                 * mode and return.
                 */
                bm = 0;
                if (ioctlsocket(*rd, FIONBIO, &bm) == SOCKET_ERROR) {
                    rv = apr_get_netos_error();
                    goto cleanup;
                }
                break;
            }
        }
        else if (nrd == SOCKET_ERROR) {
            goto cleanup;
        }
        closesocket(*rd);
    }
    /* We don't need the listening socket any more */
    closesocket(ls);
    return 0;

cleanup:
    /* Don't leak resources */
    if (*rd != INVALID_SOCKET)
        closesocket(*rd);
    if (*wr != INVALID_SOCKET)
        closesocket(*wr);

    *rd = INVALID_SOCKET;
    *wr = INVALID_SOCKET;
    closesocket(ls);
    return rv;
}