const char *Adaptation::Icap::Xaction::status() const
{
    static MemBuf buf;
    buf.reset();

    buf.append(" [", 2);

    fillPendingStatus(buf);
    buf.append("/", 1);
    fillDoneStatus(buf);

    buf.Printf(" %s%u]", id.Prefix, id.value);

    buf.terminate();

    return buf.content();
}