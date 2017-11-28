void
Http::Stream::doClose()
{
    clientConnection->close();
}