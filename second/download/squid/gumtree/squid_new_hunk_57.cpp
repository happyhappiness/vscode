    buf.append(" [", 2);

    fillPendingStatus(buf);
    buf.append("/", 1);
    fillDoneStatus(buf);

    buf.Printf(" %s%u]", id.Prefix, id.value);

    buf.terminate();

    return buf.content();
}

void Adaptation::Icap::Xaction::fillPendingStatus(MemBuf &buf) const
{
    if (haveConnection()) {
        buf.Printf("FD %d", connection->fd);

        if (writer != NULL)
            buf.append("w", 1);

        if (reader != NULL)
            buf.append("r", 1);
