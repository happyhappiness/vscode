const char *AsyncJob::status() const
{
    static MemBuf buf;
    buf.reset();

    buf.append(" [", 2);
    if (stopReason != NULL) {
        buf.Printf("Stopped, reason:");
        buf.Printf("%s",stopReason);
    }
    buf.Printf(" %s%u]", id.Prefix, id.value);
    buf.terminate();

    return buf.content();
}