void Adaptation::Icap::ServiceRep::noteTimeToNotify()
{
    Must(!notifying);
    notifying = true;
    debugs(93,7, HERE << "notifies " << theClients.size() << " clients " <<
           status());

    // note: we must notify even if we are invalidated

    Pointer us = NULL;

    while (!theClients.empty()) {
        Client i = theClients.back();
        theClients.pop_back();
        ScheduleCallHere(i.callback);
        i.callback = 0;
    }

    notifying = false;
}