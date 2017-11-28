static void
helperStatefulServerDone(helper_stateful_server * srv)
{
    if (!srv->flags.shutdown) {
        helperStatefulKickQueue(srv->parent);
    } else if (!srv->flags.closing && !srv->flags.reserved && !srv->flags.busy) {
        int wfd = srv->wfd;
        srv->wfd = -1;
        if (srv->rfd == wfd)
            srv->rfd = -1;
        srv->flags.closing=1;
        comm_close(wfd);
        return;
    }
}