static void
idnsInitVCConnected(int fd, const DnsLookupDetails &details, comm_err_t status, int xerrno, void *data)
{
    nsvc * vc = (nsvc *)data;

    if (status != COMM_OK) {
        char buf[MAX_IPSTRLEN] = "";
        if (vc->ns < nns)
            nameservers[vc->ns].S.NtoA(buf,MAX_IPSTRLEN);
        debugs(78, 1, HERE << "Failed to connect to nameserver " << buf << " using TCP: " << details);
        comm_close(fd);
        return;
    }

    comm_read(fd, (char *)&vc->msglen, 2 , idnsReadVCHeader, vc);
    vc->busy = 0;
    idnsDoSendQueryVC(vc);
}