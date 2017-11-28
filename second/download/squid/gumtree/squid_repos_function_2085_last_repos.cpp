void
releaseServerSockets(void)
{
    // Release the main ports as early as possible

    // clear http_port, https_port, and ftp_port lists
    clientConnectionsClose();

    // clear icp_port's
    icpClosePorts();

    // XXX: Why not the HTCP, SNMP, DNS ports as well?
    // XXX: why does this differ from main closeServerConnections() anyway ?
}