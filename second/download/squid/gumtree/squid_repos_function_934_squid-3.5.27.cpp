bool
ClientInfo::hasQueue() const
{
    assert(quotaQueue);
    return !quotaQueue->empty();
}