void
FtpStateData::ftpPasvCallback(const Comm::ConnectionPointer &conn, comm_err_t status, int xerrno, void *data)
{
    FtpStateData *ftpState = (FtpStateData *)data;
    debugs(9, 3, HERE);
    ftpState->data.opener = NULL;

    if (status != COMM_OK) {
        debugs(9, 2, HERE << "Failed to connect. Retrying via another method.");

        // ABORT on timeouts. server may be waiting on a broken TCP link.
        if (status == COMM_TIMEOUT)
            ftpState->writeCommand("ABOR");

        // try another connection attempt with some other method
        ftpSendPassive(ftpState);
        return;
    }

    ftpState->data.opened(conn, ftpState->dataCloser());
    ftpRestOrList(ftpState);
}