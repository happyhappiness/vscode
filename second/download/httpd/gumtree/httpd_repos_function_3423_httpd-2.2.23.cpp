static apr_status_t sendRecvBuffer(apr_time_t *t, const char *buf, 
                                   apr_size_t size, apr_pool_t *pool)
{
    apr_socket_t *sock;
    apr_status_t rv;
    apr_size_t len = size, thistime = size;
    char *recvBuf;
    apr_time_t testStart = apr_time_now(), testEnd;
    int i;

    if (! sockAddr) {
        rv = apr_sockaddr_info_get(&sockAddr, "127.0.0.1", APR_UNSPEC,
                                   testPort, 0, pool);
        if (rv != APR_SUCCESS) {
            reportError("Unable to get socket info", rv, pool);
            return rv;
        }

        /* make sure we can connect to daemon before we try tests */

        rv = apr_socket_create(&sock, APR_INET, SOCK_STREAM, APR_PROTO_TCP,
                           pool);
        if (rv != APR_SUCCESS)
            return rv;

        rv = apr_socket_connect(sock, sockAddr);
        if (rv != APR_SUCCESS) {
            reportError("Unable to connect to echod!", rv, pool);
            apr_socket_close(sock);
            return rv;
        }
        apr_socket_close(sock);

    }

    recvBuf = apr_palloc(pool, size);
    if (! recvBuf)
        return ENOMEM;
    *t = 0;

    /* START! */
    testStart = apr_time_now();
    rv = apr_socket_create(&sock, APR_INET, SOCK_STREAM, APR_PROTO_TCP,
                           pool);
    if (rv != APR_SUCCESS)
        return rv;

    rv = apr_socket_connect(sock, sockAddr);
    if (rv != APR_SUCCESS) {
        reportError("Unable to connect to echod!", rv, pool);
        apr_socket_close(sock);
        return rv;
    }

    for (i = 0; i < 3; i++) {

        len = size;
        thistime = size;

        rv = apr_socket_send(sock, buf, &len);
        if (rv != APR_SUCCESS || len != size) {
            reportError(apr_psprintf(pool, 
                         "Unable to send data correctly (iteration %d of 3)",
                         i) , rv, pool);
            closeConnection(sock);
            apr_socket_close(sock);
            return rv;
        }
    
        do {
            len = thistime;
            rv = apr_socket_recv(sock, &recvBuf[size - thistime], &len);
            if (rv != APR_SUCCESS)
                break;
            thistime -= len;
        } while (thistime);
    }

    closeConnection(sock);
    apr_socket_close(sock);
    testEnd = apr_time_now();
    /* STOP! */

    if (thistime) {
        reportError("Received less than we sent :-(", rv, pool);
        return rv;
    }        
    if (strncmp(recvBuf, buf, size) != 0) {
        reportError("Received corrupt data :-(", 0, pool);
        printf("We sent:\n%s\nWe received:\n%s\n", buf, recvBuf);
        return EINVAL;
    }
    *t = testEnd - testStart;
    return APR_SUCCESS;
}