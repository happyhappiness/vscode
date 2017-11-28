void
Ftp::Server::handlePasvReply(const HttpReply *reply, StoreIOBuffer)
{
    ClientSocketContext::Pointer context = getCurrentContext();
    assert(context != NULL);

    if (context->http->request->errType != ERR_NONE) {
        writeCustomReply(502, "Server does not support PASV", reply);
        return;
    }

    const unsigned short localPort = listenForDataConnection();
    if (!localPort)
        return;

    char addr[MAX_IPSTRLEN];
    // remote server in interception setups and local address otherwise
    const Ip::Address &server = transparent() ?
                                clientConnection->local : dataListenConn->local;
    server.toStr(addr, MAX_IPSTRLEN, AF_INET);
    addr[MAX_IPSTRLEN - 1] = '\0';
    for (char *c = addr; *c != '\0'; ++c) {
        if (*c == '.')
            *c = ',';
    }

    // In interception setups, we combine remote server address with a
    // local port number and hope that traffic will be redirected to us.
    // Do not use "227 =a,b,c,d,p1,p2" format or omit parens: some nf_ct_ftp
    // versions block responses that use those alternative syntax rules!
    MemBuf mb;
    mb.init();
    mb.Printf("227 Entering Passive Mode (%s,%i,%i).\r\n",
              addr,
              static_cast<int>(localPort / 256),
              static_cast<int>(localPort % 256));
    debugs(9, 3, Raw("writing", mb.buf, mb.size));
    writeReply(mb);
}