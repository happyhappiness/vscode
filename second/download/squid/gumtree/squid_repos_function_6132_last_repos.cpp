const char *AsyncJob::status() const
{
    static MemBuf buf;
    buf.reset();

    buf.append(" [", 2);
    if (stopReason != NULL) {
        buf.appendf("Stopped, reason:%s", stopReason);
    }
    buf.appendf(" %s%u]", id.prefix(), id.value);
    buf.terminate();

    return buf.content();
}