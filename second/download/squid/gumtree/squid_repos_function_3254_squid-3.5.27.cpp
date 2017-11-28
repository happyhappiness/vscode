void CollapsedForwardingRr::create()
{
    Must(!owner);
    owner = Ipc::MultiQueue::Init(ShmLabel, Config.workers, 1,
                                  sizeof(CollapsedForwardingMsg),
                                  QueueCapacity);
}