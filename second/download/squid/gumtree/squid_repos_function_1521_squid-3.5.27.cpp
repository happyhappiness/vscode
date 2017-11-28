static void
icpIncomingConnectionOpened(const Comm::ConnectionPointer &conn, int errNo)
{
    if (!Comm::IsConnOpen(conn))
        fatal("Cannot open ICP Port");

    Comm::SetSelect(conn->fd, COMM_SELECT_READ, icpHandleUdp, NULL, 0);

    for (const wordlist *s = Config.mcast_group_list; s; s = s->next)
        ipcache_nbgethostbyname(s->key, mcastJoinGroups, NULL); // XXX: pass the conn for mcastJoinGroups usage.

    debugs(12, DBG_IMPORTANT, "Accepting ICP messages on " << conn->local);

    fd_note(conn->fd, "Incoming ICP port");

    if (Config.Addrs.udp_outgoing.isNoAddr()) {
        icpOutgoingConn = conn;
        debugs(12, DBG_IMPORTANT, "Sending ICP messages from " << icpOutgoingConn->local);
    }
}