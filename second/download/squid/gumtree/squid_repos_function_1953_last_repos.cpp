static void
idnsShutdownAndFreeState(const char *reason)
{
    if (DnsSocketA < 0 && DnsSocketB < 0)
        return;

    debugs(78, 2, reason << ": Closing DNS sockets");

    if (DnsSocketA >= 0 ) {
        comm_close(DnsSocketA);
        DnsSocketA = -1;
    }

    if (DnsSocketB >= 0 ) {
        comm_close(DnsSocketB);
        DnsSocketB = -1;
    }

    for (int i = 0; i < nns; ++i) {
        if (nsvc *vc = nameservers[i].vc) {
            if (Comm::IsConnOpen(vc->conn))
                vc->conn->close();
        }
    }

    // XXX: vcs are not closed/freed yet and may try to access nameservers[]
    idnsFreeNameservers();
    idnsFreeSearchpath();
}