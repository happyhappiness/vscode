void
releaseServerSockets(void)
{
    // Release the main ports as early as possible

    // clear both http_port and https_port lists.
    clientHttpConnectionsClose();

    // clear icp_port's
    icpClosePorts();

    // XXX: Why not the HTCP, SNMP, DNS ports as well?
    // XXX: why does this differ from main closeServerConnections() anyway ?
}