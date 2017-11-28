void
Ftp::Server::shovelUploadData()
{
    assert(bodyPipe != NULL);

    debugs(33, 5, "handling FTP request data for " << clientConnection);
    const size_t putSize = bodyPipe->putMoreData(uploadBuf,
                           uploadAvailSize);
    if (putSize > 0) {
        uploadAvailSize -= putSize;
        if (uploadAvailSize > 0)
            memmove(uploadBuf, uploadBuf + putSize, uploadAvailSize);
    }

    if (Comm::IsConnOpen(dataConn))
        maybeReadUploadData();
    else if (uploadAvailSize <= 0)
        finishDechunkingRequest(true);
}