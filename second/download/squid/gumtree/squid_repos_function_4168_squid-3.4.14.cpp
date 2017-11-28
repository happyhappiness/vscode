void Adaptation::Icap::Xaction::noteInitiatorAborted()
{

    if (theInitiator.set()) {
        debugs(93,4, HERE << "Initiator gone before ICAP transaction ended");
        clearInitiator();
        detailError(ERR_DETAIL_ICAP_INIT_GONE);
        setOutcome(xoGone);
        mustStop("initiator aborted");
    }

}