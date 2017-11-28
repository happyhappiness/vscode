void
Ftp::Server::handleEpsvReply(const HttpReply *reply, StoreIOBuffer)
{
    if (getCurrentContext()->http->request->errType != ERR_NONE) {
        writeCustomReply(502, "Cannot connect to server", reply);
        return;
    }

    const unsigned short localPort = listenForDataConnection();
    if (!localPort)
        return;

    // In interception setups, we use a local port number and hope that data
    // traffic will be redirected to us.
    MemBuf mb;
    mb.init();
    mb.Printf("229 Entering Extended Passive Mode (|||%u|)\r\n", localPort);

    debugs(9, 3, Raw("writing", mb.buf, mb.size));
    writeReply(mb);
}