void
Log::TcpLogger::handleClosure(const CommCloseCbParams &)
{
    assert(inCall != NULL);
    closer = NULL;
    conn = NULL;
    // in all current use cases, we should not try to reconnect
    mustStop("Log::TcpLogger::handleClosure");
}