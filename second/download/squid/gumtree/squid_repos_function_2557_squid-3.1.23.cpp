void
FtpStateData::ftpPasvCallback(int fd, const DnsLookupDetails &dns, comm_err_t status, int xerrno, void *data)
{
    FtpStateData *ftpState = (FtpStateData *)data;
    debugs(9, 3, HERE);
    ftpState->request->recordLookup(dns);

    if (status != COMM_OK) {
        debugs(9, 2, HERE << "Failed to connect. Retrying without PASV.");
        ftpState->fwd->dontRetry(false);	/* this is a retryable error */
        ftpState->fwd->ftpPasvFailed(true);
        ftpState->failed(ERR_NONE, 0);
        /* failed closes ctrl.fd and frees ftpState */
        return;
    }

    ftpRestOrList(ftpState);
}