    }
    stoppedSending_ = error;

    if (!stoppedReceiving()) {
        if (const int64_t expecting = mayNeedToReadMoreBody()) {
            debugs(33, 5, HERE << "must still read " << expecting <<
                   " request body bytes with " << in.notYetUsed << " unused");
            return; // wait for the request receiver to finish reading
        }
    }

    clientConnection->close();
}

void
ClientSocketContext::writeComplete(const Comm::ConnectionPointer &conn, char *bufnotused, size_t size, comm_err_t errflag)
{
    const StoreEntry *entry = http->storeEntry();
    http->out.size += size;
    debugs(33, 5, HERE << conn << ", sz " << size <<
           ", err " << errflag << ", off " << http->out.size << ", len " <<
           (entry ? entry->objectLen() : 0));
    clientUpdateSocketStats(http->logType, size);

    /* Bail out quickly on COMM_ERR_CLOSING - close handlers will tidy up */

    if (errflag == COMM_ERR_CLOSING || !Comm::IsConnOpen(conn))
        return;

    if (errflag || clientHttpRequestStatus(conn->fd, http)) {
        initiateClose("failure or true request status");
        /* Do we leak here ? */
        return;
