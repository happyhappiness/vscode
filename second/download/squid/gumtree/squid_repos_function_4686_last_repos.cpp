void
Server::stopReading()
{
    if (reading()) {
        Comm::ReadCancel(clientConnection->fd, reader);
        reader = NULL;
    }
}