void Adaptation::Icap::Xaction::fillPendingStatus(MemBuf &buf) const
{
    if (connection >= 0) {
        buf.Printf("FD %d", connection);

        if (writer != NULL)
            buf.append("w", 1);

        if (reader != NULL)
            buf.append("r", 1);

        buf.append(";", 1);
    }
}