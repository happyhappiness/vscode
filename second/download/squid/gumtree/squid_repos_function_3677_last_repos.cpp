void Adaptation::Icap::ServiceRep::callWhenAvailable(AsyncCall::Pointer &cb, bool priority)
{
    debugs(93,8, "ICAPServiceRep::callWhenAvailable");
    Must(cb!=NULL);
    Must(up());
    Must(!theIdleConns->count()); // or we should not be waiting

    Client i;
    i.service = Pointer(this);
    i.callback = cb;
    if (priority)
        theNotificationWaiters.push_front(i);
    else
        theNotificationWaiters.push_back(i);

    busyCheckpoint();
}