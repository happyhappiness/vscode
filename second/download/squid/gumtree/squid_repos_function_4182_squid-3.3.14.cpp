void Adaptation::Icap::ServiceRep::callWhenReady(AsyncCall::Pointer &cb)
{
    Must(cb!=NULL);

    debugs(93,5, HERE << "Adaptation::Icap::Service is asked to call " << *cb <<
           " when ready " << status());

    Must(!broken()); // we do not wait for a broken service

    Client i;
    i.service = Pointer(this); // TODO: is this really needed?
    i.callback = cb;
    theClients.push_back(i);

    if (theOptionsFetcher.set() || notifying)
        return; // do nothing, we will be picked up in noteTimeToNotify()

    if (needNewOptions())
        startGettingOptions();
    else
        scheduleNotification();
}