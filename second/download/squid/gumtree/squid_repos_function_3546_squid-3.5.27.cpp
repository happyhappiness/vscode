clientStreamNode *
ClientSocketContext::getTail() const
{
    if (http->client_stream.tail)
        return (clientStreamNode *)http->client_stream.tail->data;

    return NULL;
}