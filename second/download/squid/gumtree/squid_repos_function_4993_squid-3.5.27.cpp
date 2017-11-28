void
Ftp::Server::noteBodyConsumerAborted(BodyPipe::Pointer ptr)
{
    if (!isOpen()) // if we are closing, nothing to do
        return;

    ConnStateData::noteBodyConsumerAborted(ptr);
    closeDataConnection();
}