void
CollapsedForwarding::Init()
{
    Must(!queue.get());
    if (UsingSmp() && IamWorkerProcess())
        queue.reset(new Queue(ShmLabel, KidIdentifier));
}