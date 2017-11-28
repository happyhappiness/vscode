void Adaptation::Icap::ServiceRep::noteGoneWaiter()
{
    --theAllWaiters;

    // in case the notified transaction did not take the connection slot
    busyCheckpoint();
}