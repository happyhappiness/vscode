void Adaptation::Icap::ServiceRep::putConnection(const Comm::ConnectionPointer &conn, bool isReusable, bool sendReset, const char *comment)
{
    Must(Comm::IsConnOpen(conn));
    // do not pool an idle connection if we owe connections
    if (isReusable && excessConnections() == 0) {
        debugs(93, 3, HERE << "pushing pconn" << comment);
        commUnsetConnTimeout(conn);
        theIdleConns->push(conn);
    } else {
        debugs(93, 3, HERE << (sendReset ? "RST" : "FIN") << "-closing " <<
               comment);
        // comm_close called from Connection::close will clear timeout
        // TODO: add "bool sendReset = false" to Connection::close()?
        if (sendReset)
            comm_reset_close(conn);
        else
            conn->close();
    }

    Must(theBusyConns > 0);
    --theBusyConns;
    // a connection slot released. Check if there are waiters....
    busyCheckpoint();
}