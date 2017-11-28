static Comm::ConnectionPointer
borrowPinnedConnection(HttpRequest *request, Comm::ConnectionPointer &serverDestination)
{
    // pinned_connection may become nil after a pconn race
    if (ConnStateData *pinned_connection = request ? request->pinnedConnection() : nullptr) {
        Comm::ConnectionPointer serverConn = pinned_connection->borrowPinnedConnection(request, serverDestination->getPeer());
        return serverConn;
    }

    return nullptr;
}