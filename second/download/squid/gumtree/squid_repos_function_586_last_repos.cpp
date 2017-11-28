void
commStartTlsClose(const FdeCbParams &params)
{
    Security::SessionSendGoodbye(fd_table[params.fd].ssl);
}