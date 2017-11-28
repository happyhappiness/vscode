void
Log::TcpLogger::writeIfNeeded()
{
    // write if an earlier flush command forces us to write or
    // if we have filled at least one I/O buffer
    if (flushDebt > 0 || buffers.size() > 1)
        writeIfPossible();
}