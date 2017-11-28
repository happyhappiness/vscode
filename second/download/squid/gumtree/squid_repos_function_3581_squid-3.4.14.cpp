bool
ConnStateData::concurrentRequestQueueFilled() const
{
    const int existingRequestCount = getConcurrentRequestCount();

    // default to the configured pipeline size.
    // add 1 because the head of pipeline is counted in concurrent requests and not prefetch queue
    const int concurrentRequestLimit = Config.pipeline_max_prefetch + 1;

    // when queue filled already we cant add more.
    if (existingRequestCount >= concurrentRequestLimit) {
        debugs(33, 3, clientConnection << " max concurrent requests reached (" << concurrentRequestLimit << ")");
        debugs(33, 5, clientConnection << " deferring new request until one is done");
        return true;
    }

    return false;
}