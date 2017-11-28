void
ConnStateData::stopReading()
{
    if (reading()) {
        comm_read_cancel(clientConnection->fd, reader);
        reader = NULL;
    }
}