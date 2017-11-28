ClientSocketContext *
ClientSocketContextNew(const Comm::ConnectionPointer &client, ClientHttpRequest * http)
{
    ClientSocketContext *newContext;
    assert(http != NULL);
    newContext = new ClientSocketContext;
    newContext->http = http;
    newContext->clientConnection = client;
    return newContext;
}