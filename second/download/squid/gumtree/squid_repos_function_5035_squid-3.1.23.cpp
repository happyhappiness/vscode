int
aioQueueSize(void)
{
    return DiskThreadsIOStrategy::Instance.squidaio_ctrl_pool->inUseCount();
}