void
Ftp::Server::start()
{
    ConnStateData::start();

    if (transparent()) {
        char buf[MAX_IPSTRLEN];
        clientConnection->local.toUrl(buf, MAX_IPSTRLEN);
        host = buf;
        calcUri(NULL);
        debugs(33, 5, "FTP transparent URL: " << uri);
    }

    writeEarlyReply(220, "Service ready");
}