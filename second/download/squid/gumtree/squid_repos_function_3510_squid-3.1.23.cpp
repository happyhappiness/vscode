void
clientHttpConnectionsClose(void)
{
    int i;

    for (i = 0; i < NHttpSockets; i++) {
        if (HttpSockets[i] >= 0) {
            debugs(1, 1, "FD " << HttpSockets[i] <<
                   " Closing HTTP connection");
            comm_close(HttpSockets[i]);
            HttpSockets[i] = -1;
        }
    }

    NHttpSockets = 0;
}