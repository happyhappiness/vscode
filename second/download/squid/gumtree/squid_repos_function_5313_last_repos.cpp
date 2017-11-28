void
Ftp::Client::writeCommandCallback(const CommIoCbParams &io)
{

    debugs(9, 5, "wrote " << io.size << " bytes");

    if (io.size > 0) {
        fd_bytes(io.fd, io.size, FD_WRITE);
        statCounter.server.all.kbytes_out += io.size;
        statCounter.server.ftp.kbytes_out += io.size;
    }

    if (io.flag == Comm::ERR_CLOSING)
        return;

    if (io.flag) {
        debugs(9, DBG_IMPORTANT, "FTP command write error: " << io.conn << ": " << xstrerr(io.xerrno));
        failed(ERR_WRITE_ERROR, io.xerrno);
        /* failed closes ctrl.conn and frees ftpState */
        return;
    }
}