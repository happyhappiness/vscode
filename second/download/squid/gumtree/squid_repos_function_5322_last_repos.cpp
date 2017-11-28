void
Ftp::Client::sentRequestBody(const CommIoCbParams &io)
{
    if (io.size > 0)
        statCounter.server.ftp.kbytes_out += io.size;
    ::Client::sentRequestBody(io);
}