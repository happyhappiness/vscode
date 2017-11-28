void
releaseServerSockets(void)
{
    int i;
    /* Release the main ports as early as possible */

    for (i = 0; i < NHttpSockets; i++) {
        if (HttpSockets[i] >= 0)
            close(HttpSockets[i]);
    }

    if (theInIcpConnection >= 0)
        close(theInIcpConnection);

    if (theOutIcpConnection >= 0 && theOutIcpConnection != theInIcpConnection)
        close(theOutIcpConnection);
}