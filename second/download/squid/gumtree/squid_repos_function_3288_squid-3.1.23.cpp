static void
comm_select_http_incoming(void)
{
    int nfds = 0;
    int fds[MAXHTTPPORTS];
    int j;
    int nevents;
    http_io_events = 0;

    for (j = 0; j < NHttpSockets; j++) {
        if (HttpSockets[j] < 0)
            continue;

        fds[nfds++] = HttpSockets[j];
    }

    nevents = comm_check_incoming_select_handlers(nfds, fds);
    incoming_http_interval += Config.comm_incoming.http_average - nevents;

    if (incoming_http_interval < 0)
        incoming_http_interval = 0;

    if (incoming_http_interval > MAX_INCOMING_INTERVAL)
        incoming_http_interval = MAX_INCOMING_INTERVAL;

    if (nevents > INCOMING_HTTP_MAX)
        nevents = INCOMING_HTTP_MAX;

    statHistCount(&statCounter.comm_http_incoming, nevents);
}