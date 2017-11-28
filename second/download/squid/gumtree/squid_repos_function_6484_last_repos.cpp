void
IpcIoRr::create()
{
    if (Config.cacheSwap.n_strands <= 0)
        return;

    Must(!owner);
    owner = Ipc::FewToFewBiQueue::Init(ShmLabel, Config.workers, 1,
                                       Config.cacheSwap.n_strands,
                                       1 + Config.workers, sizeof(IpcIoMsg),
                                       QueueCapacity);
}