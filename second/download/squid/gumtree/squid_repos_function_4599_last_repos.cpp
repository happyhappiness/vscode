void
Ftp::Server::maybeReadUploadData()
{
    if (reader != NULL)
        return;

    const size_t availSpace = sizeof(uploadBuf) - uploadAvailSize;
    if (availSpace <= 0)
        return;

    debugs(33, 4, dataConn << ": reading FTP data...");

    typedef CommCbMemFunT<Server, CommIoCbParams> Dialer;
    reader = JobCallback(33, 5, Dialer, this, Ftp::Server::readUploadData);
    comm_read(dataConn, uploadBuf + uploadAvailSize, availSpace,
              reader);
}