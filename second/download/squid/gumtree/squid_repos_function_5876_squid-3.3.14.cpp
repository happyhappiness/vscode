void
Snmp::Forwarder::handleTimeout()
{
    sendError(SNMP_ERR_RESOURCEUNAVAILABLE);
    Ipc::Forwarder::handleTimeout();
}