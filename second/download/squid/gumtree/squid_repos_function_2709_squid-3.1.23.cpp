void
TunnelStateData::writeClientDone(char *buf, size_t len, comm_err_t flag, int xerrno)
{
    debugs(26, 3, "tunnelWriteClient: FD " << client.fd() << ", " << len << " bytes written");

    /* Error? */
    if (flag != COMM_OK) {
        if (flag != COMM_ERR_CLOSING)
            client.error(xerrno); // may call comm_close
        return;
    }

    /* EOF? */
    if (len == 0) {
        comm_close(client.fd());
        return;
    }

    /* Valid data */
    kb_incr(&statCounter.client_http.kbytes_out, len);
    server.dataSent(len);

    /* If the other end has closed, so should we */
    if (fd_closed(server.fd())) {
        comm_close(client.fd());
        return;
    }

    cbdataInternalLock(this);	/* ??? should be locked by the caller... */

    if (cbdataReferenceValid(this))
        copyRead(server, ReadServer);

    cbdataInternalUnlock(this);	/* ??? */
}