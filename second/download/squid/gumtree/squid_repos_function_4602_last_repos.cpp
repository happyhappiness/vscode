void
Ftp::Server::readUploadData(const CommIoCbParams &io)
{
    debugs(33, 5, io.conn << " size " << io.size);
    Must(reader != NULL);
    reader = NULL;

    assert(Comm::IsConnOpen(dataConn));
    assert(io.conn->fd == dataConn->fd);

    if (io.flag == Comm::OK && bodyPipe != NULL) {
        if (io.size > 0) {
            statCounter.client_http.kbytes_in += io.size;

            char *const current_buf = uploadBuf + uploadAvailSize;
            if (io.buf != current_buf)
                memmove(current_buf, io.buf, io.size);
            uploadAvailSize += io.size;
            shovelUploadData();
        } else if (io.size == 0) {
            debugs(33, 5, io.conn << " closed");
            closeDataConnection();
            if (uploadAvailSize <= 0)
                finishDechunkingRequest(true);
        }
    } else { // not Comm::Flags::OK or unexpected read
        debugs(33, 5, io.conn << " closed");
        closeDataConnection();
        finishDechunkingRequest(false);
    }

}