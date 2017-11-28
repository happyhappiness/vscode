void
Ftp::Server::handleEprtReply(const HttpReply *reply, StoreIOBuffer)
{
    if (pipeline.front()->http->request->errType != ERR_NONE) {
        writeCustomReply(502, "Server does not support PASV (converted from EPRT)", reply);
        return;
    }

    writeCustomReply(200, "EPRT successfully converted to PASV.");

    // and wait for RETR
}