void
ConnStateData::In::maybeMakeSpaceAvailable()
{
    // The hard-coded parameters are arbitrary but seem reasonable.
    // A careful study of Squid I/O and parsing patterns is needed to tune them.
    SBufReservationRequirements requirements;
    requirements.minSpace = 1024; // smaller I/Os are not worth their overhead
    requirements.idealSpace = CLIENT_REQ_BUF_SZ; // we expect few larger I/Os
    requirements.maxCapacity = Config.maxRequestBufferSize;
    requirements.allowShared = true; // allow because inBuf is used immediately
    buf.reserve(requirements);
    if (!buf.spaceSize())
        debugs(33, 4, "request buffer full: client_request_buffer_max_size=" << Config.maxRequestBufferSize);
}