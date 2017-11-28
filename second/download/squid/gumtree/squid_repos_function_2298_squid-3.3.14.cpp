static void
idnsVCClosed(const CommCloseCbParams &params)
{
    nsvc * vc = (nsvc *)params.data;
    delete vc->queue;
    delete vc->msg;
    vc->conn = NULL;
    if (vc->ns < nns) // XXX: dnsShutdown may have freed nameservers[]
        nameservers[vc->ns].vc = NULL;
    cbdataFree(vc);
}