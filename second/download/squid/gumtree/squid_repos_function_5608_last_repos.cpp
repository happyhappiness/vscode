static void
logAcceptError(const Comm::ConnectionPointer &conn)
{
    AccessLogEntry::Pointer al = new AccessLogEntry;
    al->tcpClient = conn;
    al->url = "error:accept-client-connection";
    ACLFilledChecklist ch(nullptr, nullptr, nullptr);
    ch.src_addr = conn->remote;
    ch.my_addr = conn->local;
    accessLogLog(al, &ch);
}