void
Ssl::IcapPeerConnector::noteNegotiationDone(ErrorState *error)
{
    if (error)
        return;

    const int fd = serverConnection()->fd;
    Security::MaybeGetSessionResumeData(fd_table[fd].ssl, icapService->sslSession);
}