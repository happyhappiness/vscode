void
Log::TcpLogger::logRecord(const char *buf, const size_t len)
{
    appendRecord(buf, len);
    writeIfNeeded();
}