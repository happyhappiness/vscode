bool
ConnStateData::concurrentRequestQueueFilled() const
{
    const int existingRequestCount = pipeline.count();

    // default to the configured pipeline size.
    // add 1 because the head of pipeline is counted in concurrent requests and not prefetch queue
#if USE_OPENSSL
    const int internalRequest = (transparent() && sslBumpMode == Ssl::bumpSplice) ? 1 : 0;
#else
    const int internalRequest = 0;
#endif
    const int concurrentRequestLimit = pipelinePrefetchMax() + 1 + internalRequest;

    // when queue filled already we cant add more.
    if (existingRequestCount >= concurrentRequestLimit) {
        debugs(33, 3, clientConnection << " max concurrent requests reached (" << concurrentRequestLimit << ")");
        debugs(33, 5, clientConnection << " deferring new request until one is done");
        return true;
    }

    return false;
}