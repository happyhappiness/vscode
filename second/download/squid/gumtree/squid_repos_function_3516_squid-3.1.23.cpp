void
ConnStateData::stopReading()
{
    if (reading()) {
        comm_read_cancel(fd, reader);
        reader = NULL;
    }
}