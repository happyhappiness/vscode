void
Http::Server::processParsedRequest(ClientSocketContext *context, const Http::ProtocolVersion &ver)
{
    clientProcessRequest(this, &parser_, context, method_, ver);
}