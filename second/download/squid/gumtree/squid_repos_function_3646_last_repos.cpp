const char *Adaptation::Icap::Xaction::status() const
{
    static MemBuf buf;
    buf.reset();
    buf.append(" [", 2);
    fillPendingStatus(buf);
    buf.append("/", 1);
    fillDoneStatus(buf);
    buf.appendf(" %s%u]", id.prefix(), id.value);
    buf.terminate();

    return buf.content();
}