static void
fwdConnectDoneWrapper(int server_fd, const DnsLookupDetails &dns, comm_err_t status, int xerrno, void *data)
{
    FwdState *fwd = (FwdState *) data;
    fwd->connectDone(server_fd, dns, status, xerrno);
}