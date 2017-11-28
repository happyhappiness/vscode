void Adaptation::Icap::Xaction::cancelRead()
{
    if (reader != NULL) {
        Must(haveConnection());
        comm_read_cancel(connection->fd, reader);
        reader = NULL;
    }
}