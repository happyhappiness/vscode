const char *
Ssl::PeerConnector::status() const
{
    static MemBuf buf;
    buf.reset();

    // TODO: redesign AsyncJob::status() API to avoid this
    // id and stop reason reporting duplication.
    buf.append(" [", 2);
    if (stopReason != NULL) {
        buf.Printf("Stopped, reason:");
        buf.Printf("%s",stopReason);
    }
    if (serverConn != NULL)
        buf.Printf(" FD %d", serverConn->fd);
    buf.Printf(" %s%u]", id.prefix(), id.value);
    buf.terminate();

    return buf.content();
}