void Adaptation::Icap::ServiceRep::handleNewOptions(Adaptation::Icap::Options *newOptions)
{
    // new options may be NULL
    changeOptions(newOptions);

    debugs(93,3, HERE << "got new options and is now " << status());

    scheduleUpdate(optionsFetchTime());

    // XXX: this whole feature bases on the false assumption a service only has one IP
    setMaxConnections();
    const int excess = excessConnections();
    // if we owe connections and have idle pconns, close the latter
    if (excess && theIdleConns->count() > 0) {
        const int n = min(excess, theIdleConns->count());
        debugs(93,5, HERE << "closing " << n << " pconns to relief debt");
        theIdleConns->closeN(n);
    }

    scheduleNotification();
}