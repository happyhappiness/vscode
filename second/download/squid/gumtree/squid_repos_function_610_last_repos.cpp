void
ClientInfo::quotaDequeue()
{
    assert(quotaQueue);
    quotaQueue->dequeue();
}