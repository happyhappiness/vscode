void
Log::TcpLogger::Flush(Logfile * lf)
{
    if (TcpLogger *logger = StillLogging(lf))
        logger->flush();
}