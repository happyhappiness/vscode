void
Snmp::Forwarder::handleException(const std::exception& e)
{
    debugs(49, 3, HERE << e.what());
    if (fd >= 0)
        sendError(SNMP_ERR_GENERR);
    Ipc::Forwarder::handleException(e);
}