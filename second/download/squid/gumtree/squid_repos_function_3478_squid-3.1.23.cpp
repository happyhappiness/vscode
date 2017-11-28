int
ConnStateData::connFinishedWithConn(int size)
{
    if (size == 0) {
        if (getConcurrentRequestCount() == 0 && in.notYetUsed == 0) {
            /* no current or pending requests */
            debugs(33, 4, "connFinishedWithConn: FD " << fd << " closed");
            return 1;
        } else if (!Config.onoff.half_closed_clients) {
            /* admin doesn't want to support half-closed client sockets */
            debugs(33, 3, "connFinishedWithConn: FD " << fd << " aborted (half_closed_clients disabled)");
            return 1;
        }
    }

    return 0;
}