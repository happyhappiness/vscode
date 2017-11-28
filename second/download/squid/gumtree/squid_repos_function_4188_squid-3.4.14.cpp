void Adaptation::Icap::ServiceRep::busyCheckpoint()
{
    if (theNotificationWaiters.empty()) // nobody is waiting for a slot
        return;

    int freed = 0;
    int available = availableConnections();

    if (available < 0) {
        // It is possible to have waiters when no limit on connections exist in
        // case of reconfigure or because new Options received.
        // In this case, notify all waiting transactions.
        freed  = theNotificationWaiters.size();
    } else {
        // avoid notifying more waiters than there will be available slots
        const int notifiedWaiters = theAllWaiters - theNotificationWaiters.size();
        freed = available - notifiedWaiters;
    }

    debugs(93,7, HERE << "Available connections: " << available <<
           " freed slots: " << freed <<
           " waiting in queue: " << theNotificationWaiters.size());

    while (freed > 0 && !theNotificationWaiters.empty()) {
        Client i = theNotificationWaiters.front();
        theNotificationWaiters.pop_front();
        ScheduleCallHere(i.callback);
        i.callback = NULL;
        --freed;
    }
}