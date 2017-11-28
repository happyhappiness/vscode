bool
Log::TcpLogger::doneAll() const
{
    debugs(MY_DEBUG_SECTION, 5, "quitOnEmpty: " << quitOnEmpty <<
           " buffered: " << bufferedSize <<
           " conn: " << conn << ' ' << connectFailures);

    // we do not quit unless we are told that we may
    if (!quitOnEmpty)
        return false;

    /* We were asked to quit after we are done writing buffers. Are we done? */

    // If we have records but are failing to connect, quit. Otherwise, we may
    // be trying to connect forever due to a [since fixed] misconfiguration!
    const bool failingToConnect = !conn && connectFailures;
    if (bufferedSize && !failingToConnect)
        return false;

    return AsyncJob::doneAll();
}