void Adaptation::Icap::Xaction::cancelRead()
{
    if (reader != NULL) {
        comm_read_cancel(connection, reader);
        reader = NULL;
    }
}