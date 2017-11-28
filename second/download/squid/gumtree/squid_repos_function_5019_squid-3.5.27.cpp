void
Ftp::Server::handleUploadReply(const HttpReply *reply, StoreIOBuffer)
{
    writeForwardedReply(reply);
    // note that the client data connection may already be closed by now
}