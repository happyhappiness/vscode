unsigned int
ClientInfo::quotaEnqueue(int fd)
{
    assert(quotaQueue);
    return quotaQueue->enqueue(fd);
}