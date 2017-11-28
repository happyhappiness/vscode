static void
idnsVCClosed(int fd, void *data)
{
    nsvc * vc = (nsvc *)data;
    delete vc->queue;
    delete vc->msg;
    if (vc->ns < nns) // XXX: idnsShutdown may have freed nameservers[]
        nameservers[vc->ns].vc = NULL;
    cbdataFree(vc);
}