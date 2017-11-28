void
FtpStateData::ftpWriteCommandCallback(const CommIoCbParams &io)
{

    debugs(9, 5, "ftpWriteCommandCallback: wrote " << io.size << " bytes");

    if (io.size > 0) {
        fd_bytes(io.fd, io.size, FD_WRITE);
        kb_incr(&(statCounter.server.all.kbytes_out), io.size);
        kb_incr(&(statCounter.server.ftp.kbytes_out), io.size);
    }

    if (io.flag == COMM_ERR_CLOSING)
        return;

    if (io.flag) {
        debugs(9, DBG_IMPORTANT, "ftpWriteCommandCallback: " << io.conn << ": " << xstrerr(io.xerrno));
        failed(ERR_WRITE_ERROR, io.xerrno);
        /* failed closes ctrl.conn and frees ftpState */
        return;
    }
}