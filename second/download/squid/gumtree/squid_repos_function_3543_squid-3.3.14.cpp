int
ConnStateData::connFinishedWithConn(int size)
{
    if (size == 0) {
        if (getConcurrentRequestCount() == 0 && in.notYetUsed == 0) {
            /* no current or pending requests */
            debugs(33, 4, HERE << clientConnection << " closed");
            return 1;
        } else if (!Config.onoff.half_closed_clients) {
            /* admin doesn't want to support half-closed client sockets */
            debugs(33, 3, HERE << clientConnection << " aborted (half_closed_clients disabled)");
            notifyAllContexts(0); // no specific error implies abort
            return 1;
        }
    }

    return 0;
}