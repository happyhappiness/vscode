static apr_status_t wait_for_connect(apr_socket_t *sock)
{
    int rc;
    struct timeval tv, *tvptr;
    fd_set wfdset, efdset;

    /* wait for the connect to complete or timeout */
    FD_ZERO(&wfdset);
    FD_SET(sock->socketdes, &wfdset);
    FD_ZERO(&efdset);
    FD_SET(sock->socketdes, &efdset);

    if (sock->timeout < 0) {
        tvptr = NULL;
    }
    else {
        /* casts for winsock/timeval definition */
        tv.tv_sec =  (long)apr_time_sec(sock->timeout);
        tv.tv_usec = (int)apr_time_usec(sock->timeout);
        tvptr = &tv;
    }
    rc = select(FD_SETSIZE+1, NULL, &wfdset, &efdset, tvptr);
    if (rc == SOCKET_ERROR) {
        return apr_get_netos_error();
    }
    else if (!rc) {
        return APR_FROM_OS_ERROR(WSAETIMEDOUT);
    }
    /* Evaluate the efdset */
    if (FD_ISSET(sock->socketdes, &efdset)) {
        /* The connect failed. */
        int rclen = sizeof(rc);
        if (getsockopt(sock->socketdes, SOL_SOCKET, SO_ERROR, (char*) &rc, &rclen)) {
            return apr_get_netos_error();
        }
        return APR_FROM_OS_ERROR(rc);
    }

    return APR_SUCCESS;
}