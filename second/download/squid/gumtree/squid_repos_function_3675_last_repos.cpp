void Adaptation::Icap::ServiceRep::noteTimeToUpdate()
{
    if (!detached())
        updateScheduled = false;

    if (detached() || theOptionsFetcher.set()) {
        debugs(93,5, HERE << "ignores options update " << status());
        return;
    }

    debugs(93,5, HERE << "performs a regular options update " << status());
    startGettingOptions();
}