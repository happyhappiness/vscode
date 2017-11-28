        fatal("Cannot open HTCP Socket");

    Comm::SetSelect(conn->fd, COMM_SELECT_READ, htcpRecv, NULL, 0);

    debugs(31, DBG_CRITICAL, "Accepting HTCP messages on " << conn->local);

    if (Config.Addrs.udp_outgoing.isNoAddr()) {
        htcpOutgoingConn = conn;
        debugs(31, DBG_IMPORTANT, "Sending HTCP messages from " << htcpOutgoingConn->local);
    }
}

int
