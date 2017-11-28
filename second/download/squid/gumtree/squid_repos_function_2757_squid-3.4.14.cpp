void
TunnelStateData::writeClientDone(char *, size_t len, comm_err_t flag, int xerrno)
{
    debugs(26, 3, HERE << client.conn << ", " << len << " bytes written, flag=" << flag);

    /* Error? */
    if (flag != COMM_OK) {
        if (flag != COMM_ERR_CLOSING) {
            debugs(26, 4, HERE << "Closing client connection due to comm flags.");
            client.error(xerrno); // may call comm_close
        }
        return;
    }

    /* EOF? */
    if (len == 0) {
        debugs(26, 4, HERE << "Closing client connection due to 0 byte read.");
        client.conn->close();
        return;
    }

    /* Valid data */
    kb_incr(&(statCounter.client_http.kbytes_out), len);
    server.dataSent(len);

    /* If the other end has closed, so should we */
    if (!Comm::IsConnOpen(server.conn)) {
        debugs(26, 4, HERE << "Server has gone away. Terminating client connection.");
        client.conn->close();
        return;
    }

    CbcPointer<TunnelStateData> safetyLock(this);	/* ??? should be locked by the caller... */

    if (cbdataReferenceValid(this))
        copyRead(server, ReadServer);
}