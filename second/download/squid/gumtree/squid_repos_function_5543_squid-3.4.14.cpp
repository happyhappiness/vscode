void
Log::TcpLogger::EndLine(Logfile * lf)
{
    if (!Config.onoff.buffered_logs)
        Flush(lf);
}