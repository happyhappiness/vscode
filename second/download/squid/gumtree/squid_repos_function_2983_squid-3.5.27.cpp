ConnStateData *
HttpRequest::pinnedConnection()
{
    if (clientConnectionManager.valid() && clientConnectionManager->pinning.pinned)
        return clientConnectionManager.get();
    return NULL;
}