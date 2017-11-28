static void
wccpHereIam(void *voidnotused)
{
    debugs(80, 6, "wccpHereIam: Called");

    wccp_here_i_am.id = last_id;
    comm_udp_send(theWccpConnection,
                  &wccp_here_i_am,
                  sizeof(wccp_here_i_am),
                  0);

    if (!eventFind(wccpHereIam, NULL))
        eventAdd("wccpHereIam", wccpHereIam, NULL, 10.0, 1);
}