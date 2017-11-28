void
Ftp::Client::sentRequestBody(const CommIoCbParams &io)
{
    if (io.size > 0)
        kb_incr(&(statCounter.server.ftp.kbytes_out), io.size);
    ::Client::sentRequestBody(io);
}