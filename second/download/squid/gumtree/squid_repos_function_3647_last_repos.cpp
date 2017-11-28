void Adaptation::Icap::Xaction::fillPendingStatus(MemBuf &buf) const
{
    if (haveConnection()) {
        buf.appendf("FD %d", connection->fd);

        if (writer != NULL)
            buf.append("w", 1);

        if (reader != NULL)
            buf.append("r", 1);

        buf.append(";", 1);
    }
}