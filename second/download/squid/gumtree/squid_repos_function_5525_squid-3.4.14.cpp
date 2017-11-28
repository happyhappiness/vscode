void
Log::TcpLogger::flush()
{
    flushDebt = bufferedSize;
    writeIfNeeded();
}