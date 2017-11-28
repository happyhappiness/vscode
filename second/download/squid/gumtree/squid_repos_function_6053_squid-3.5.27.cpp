void
Log::TcpLogger::WriteLine(Logfile * lf, const char *buf, size_t len)
{
    if (TcpLogger *logger = StillLogging(lf))
        logger->logRecord(buf, len);
}