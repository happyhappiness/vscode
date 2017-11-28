void
TunnelStateData::writeServerDone(char *buf, size_t len, comm_err_t flag, int xerrno)
{
    debugs(26, 3, "tunnelWriteServer: FD " << server.fd() << ", " << len << " bytes written");

    /* Error? */
    if (flag != COMM_OK) {
        if (flag != COMM_ERR_CLOSING)
            server.error(xerrno); // may call comm_close
        return;
    }

    /* EOF? */
    if (len == 0) {
        comm_close(server.fd());
        return;
    }

    /* Valid data */
    kb_incr(&statCounter.server.all.kbytes_out, len);
    kb_incr(&statCounter.server.other.kbytes_out, len);
    client.dataSent(len);

    /* If the other end has closed, so should we */
    if (fd_closed(client.fd())) {
        comm_close(server.fd());
        return;
    }

    cbdataInternalLock(this);	/* ??? should be locked by the caller... */

    if (cbdataReferenceValid(this))
        copyRead(client, ReadClient);

    cbdataInternalUnlock(this);	/* ??? */
}