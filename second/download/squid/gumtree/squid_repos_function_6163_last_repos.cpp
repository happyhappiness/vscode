void
HierarchyLogEntry::note(const Comm::ConnectionPointer &server, const char *requestedHost)
{
    tcpServer = server;
    if (tcpServer == NULL) {
        code = HIER_NONE;
        xstrncpy(host, requestedHost, sizeof(host));
    } else {
        code = tcpServer->peerType;

        if (tcpServer->getPeer()) {
            // went to peer, log peer host name
            xstrncpy(host, tcpServer->getPeer()->name, sizeof(host));
        } else {
            xstrncpy(host, requestedHost, sizeof(host));
        }
    }
}