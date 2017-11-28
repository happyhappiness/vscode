void Adaptation::Icap::Xaction::updateTimeout()
{
    if (reader != NULL || writer != NULL) {
        // restart the timeout before each I/O
        // XXX: why does Config.Timeout lacks a write timeout?
        // TODO: service bypass status may differ from that of a transaction
        typedef CommCbMemFunT<Adaptation::Icap::Xaction, CommTimeoutCbParams> TimeoutDialer;
        AsyncCall::Pointer call = JobCallback(93,5,
                                              TimeoutDialer, this, Adaptation::Icap::Xaction::noteCommTimedout);

        commSetTimeout(connection,
                       TheConfig.io_timeout(service().cfg().bypass), call);
    } else {
        // clear timeout when there is no I/O
        // Do we need a lifetime timeout?
        AsyncCall::Pointer call = NULL;
        commSetTimeout(connection, -1, call);
    }
}