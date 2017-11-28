void Adaptation::Icap::Xaction::handleCommClosed()
{
    detailError(ERR_DETAIL_ICAP_XACT_CLOSE);
    mustStop("ICAP service connection externally closed");
}