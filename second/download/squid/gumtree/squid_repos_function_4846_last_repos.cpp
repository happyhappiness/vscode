clientStreamNode *
Http::Stream::getTail() const
{
    if (http->client_stream.tail)
        return static_cast<clientStreamNode *>(http->client_stream.tail->data);

    return nullptr;
}