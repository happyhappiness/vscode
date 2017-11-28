void
FtpStateData::sentRequestBody(const CommIoCbParams &io)
{
    if (io.size > 0)
        kb_incr(&(statCounter.server.ftp.kbytes_out), io.size);
    ServerStateData::sentRequestBody(io);
}