void
idnsShutdown(void)
{
    if (DnsSocketA < 0 && DnsSocketB < 0)
        return;

    if (DnsSocketA >= 0 ) {
        comm_close(DnsSocketA);
        DnsSocketA = -1;
    }

    if (DnsSocketB >= 0 ) {
        comm_close(DnsSocketB);
        DnsSocketB = -1;
    }

    for (int i = 0; i < nns; i++) {
        if (nsvc *vc = nameservers[i].vc) {
            if (vc->fd >= 0)
                comm_close(vc->fd);
        }
    }

    // XXX: vcs are not closed/freed yet and may try to access nameservers[]
    idnsFreeNameservers();
    idnsFreeSearchpath();
}