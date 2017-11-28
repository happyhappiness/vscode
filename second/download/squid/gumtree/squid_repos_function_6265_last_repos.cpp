int
aioQueueSize(void)
{
    return squidaio_ctrl_t::UseCount();
}