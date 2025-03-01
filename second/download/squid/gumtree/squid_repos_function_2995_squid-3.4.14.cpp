static void
wccpHereIam(void *voidnotused)
{
    debugs(80, 6, "wccpHereIam: Called");

    wccp_here_i_am.id = last_id;
    double interval = 10.0; // TODO: make this configurable, possibly negotiate with the router.
    errno = 0;
    ssize_t sent = comm_udp_send(theWccpConnection, &wccp_here_i_am, sizeof(wccp_here_i_am), 0);

    // if we failed to send the whole lot, try again at a shorter interval (20%)
    if (sent != sizeof(wccp_here_i_am)) {
        debugs(80, 2, "ERROR: failed to send WCCP HERE_I_AM packet: " << xstrerror());
        interval = 2.0;
    }

    if (!eventFind(wccpHereIam, NULL))
        eventAdd("wccpHereIam", wccpHereIam, NULL, interval, 1);
}