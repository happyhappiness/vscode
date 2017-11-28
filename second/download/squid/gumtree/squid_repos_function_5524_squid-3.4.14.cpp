void
Log::TcpLogger::endGracefully()
{
    // job call protection must end our job if we are done logging current bufs
    assert(inCall != NULL);
    quitOnEmpty = true;
    flush();
}