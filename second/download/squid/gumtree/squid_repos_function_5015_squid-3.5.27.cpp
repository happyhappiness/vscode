void
Ftp::Server::handleErrorReply(const HttpReply *reply, StoreIOBuffer)
{
    if (!pinning.pinned) // we failed to connect to server
        uri.clear();
    // 421: we will close due to fssError
    writeErrorReply(reply, 421);
}