void Adaptation::Icap::Xaction::noteInitiatorAborted()
{

    if (theInitiator.set()) {
        clearInitiator();
        mustStop("initiator aborted");
    }

}