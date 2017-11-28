const char *AsyncJob::status() const
{
    static MemBuf buf;
    buf.reset();

    buf.append(" [", 2);
    if (stopReason != NULL) {
        buf.Printf("Stopped, reason:");
        buf.Printf("%s",stopReason);
    }
    buf.Printf(" job%d]", id);
    buf.terminate();

    return buf.content();
}