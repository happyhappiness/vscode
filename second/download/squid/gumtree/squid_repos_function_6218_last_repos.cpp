void
Log::TcpLogger::appendRecord(const char *record, const size_t len)
{
    // they should not happen, but to be safe, let's protect drop start/stop
    // monitoring algorithm from empty records (which can never be dropped)
    if (!len)
        return;

    if (!canFit(len)) {
        ++drops;
        return;
    }

    drops = 0;
    // append without spliting buf, unless it exceeds IoBufSize
    for (size_t off = 0; off < len; off += IoBufSize)
        appendChunk(record + off, min(len - off, IoBufSize));
}