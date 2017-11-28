void
TunnelStateData::writeServerDone(char *, size_t len, Comm::Flag flag, int xerrno)
{
    debugs(26, 3, HERE  << server.conn << ", " << len << " bytes written, flag=" << flag);

    /* Error? */
    if (flag != Comm::OK) {
        if (flag != Comm::ERR_CLOSING) {
            debugs(26, 4, HERE << "calling TunnelStateData::server.error(" << xerrno <<")");
            server.error(xerrno); // may call comm_close
        }
        return;
    }

    /* EOF? */
    if (len == 0) {
        debugs(26, 4, HERE << "No read input. Closing server connection.");
        server.conn->close();
        return;
    }

    /* Valid data */
    statCounter.server.all.kbytes_out += len;
    statCounter.server.other.kbytes_out += len;
    client.dataSent(len);

    /* If the other end has closed, so should we */
    if (!Comm::IsConnOpen(client.conn)) {
        debugs(26, 4, HERE << "Client gone away. Shutting down server connection.");
        server.conn->close();
        return;
    }

    const CbcPointer<TunnelStateData> safetyLock(this); /* ??? should be locked by the caller... */

    if (cbdataReferenceValid(this))
        copyClientBytes();
}