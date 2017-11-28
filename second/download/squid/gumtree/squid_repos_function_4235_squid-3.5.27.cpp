void Adaptation::Icap::Xaction::cancelRead()
{
    if (reader != NULL) {
        Must(haveConnection());
        Comm::ReadCancel(connection->fd, reader);
        reader = NULL;
    }
}