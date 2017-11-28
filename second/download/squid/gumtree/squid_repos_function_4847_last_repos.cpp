clientStreamNode *
Http::Stream::getClientReplyContext() const
{
    return static_cast<clientStreamNode *>(http->client_stream.tail->prev->data);
}