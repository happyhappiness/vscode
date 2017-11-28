void
TunnelStateData::writeServerDone(char *buf, size_t len, comm_err_t flag, int xerrno)
{
    debugs(26, 3, HERE  << server.conn << ", " << len << " bytes written, flag=" << flag);

    /* Error? */
    if (flag != COMM_OK) {
        if (flag != COMM_ERR_CLOSING) {
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
    kb_incr(&(statCounter.server.all.kbytes_out), len);
    kb_incr(&(statCounter.server.other.kbytes_out), len);
    client.dataSent(len);

    /* If the other end has closed, so should we */
    if (!Comm::IsConnOpen(client.conn)) {
        debugs(26, 4, HERE << "Client gone away. Shutting down server connection.");
        server.conn->close();
        return;
    }

    cbdataInternalLock(this);	/* ??? should be locked by the caller... */

    if (cbdataReferenceValid(this))
        copyRead(client, ReadClient);

    cbdataInternalUnlock(this);	/* ??? */
}