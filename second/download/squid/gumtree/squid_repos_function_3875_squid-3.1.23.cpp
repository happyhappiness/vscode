void Adaptation::Icap::ModXact::start()
{
    Adaptation::Icap::Xaction::start();

    // reserve an adaptation history slot (attempts are known at this time)
    Adaptation::History::Pointer ah = virginRequest().adaptLogHistory();
    if (ah != NULL)
        adaptHistoryId = ah->recordXactStart(service().cfg().key, icap_tr_start, attempts > 1);

    estimateVirginBody(); // before virgin disappears!

    canStartBypass = service().cfg().bypass;

    // it is an ICAP violation to send request to a service w/o known OPTIONS

    if (service().up())
        startWriting();
    else
        waitForService();
}