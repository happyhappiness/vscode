bool
ClientInfo::hasQueue(const CommQuotaQueue *q) const
{
    assert(quotaQueue);
    return quotaQueue == q;
}