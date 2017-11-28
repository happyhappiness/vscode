int
ClientInfo::quotaPeekFd() const
{
    assert(quotaQueue);
    return quotaQueue->front();
}