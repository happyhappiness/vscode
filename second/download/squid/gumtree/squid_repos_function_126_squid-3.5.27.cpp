bool
Transport::Connect()
{
    Ip::Address iaddr;
    resolveDestination(iaddr);

    debugVerbose(2, "Connecting... " << Config.hostname << " (" << iaddr << ")");

    if (client_comm_connect(conn, iaddr) < 0) {
        char hostnameBuf[MAX_IPSTRLEN];
        iaddr.toUrl(hostnameBuf, MAX_IPSTRLEN);
        std::cerr << "ERROR: Cannot connect to " << hostnameBuf
                  << (!errno ?": Host unknown." : "") << std::endl;
        exit(1);
    }
    debugVerbose(2, "Connected to: " << Config.hostname << " (" << iaddr << ")");

    // do any TLS setup that might be needed
    if (!Transport::MaybeStartTls(Config.hostname))
        return false;

    return true;
}