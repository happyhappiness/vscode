unsigned int
ClientInfo::quotaPeekReserv() const
{
    assert(quotaQueue);
    return quotaQueue->outs + 1;
}