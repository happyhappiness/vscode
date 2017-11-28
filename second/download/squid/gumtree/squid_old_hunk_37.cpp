    proxyingAb = opComplete;
}

void
Adaptation::Ecap::XactionRep::noteMoreBodyDataAvailable(RefCount<BodyPipe> bp)
{
    Must(proxyingVb == opOn);
    Must(theMaster);
    theMaster->noteVbContentAvailable();
}

void
Adaptation::Ecap::XactionRep::noteBodyProductionEnded(RefCount<BodyPipe> bp)
{
    Must(proxyingVb == opOn);
    Must(theMaster);
    theMaster->noteVbContentDone(true);
    proxyingVb = opComplete;
}

void
Adaptation::Ecap::XactionRep::noteBodyProducerAborted(RefCount<BodyPipe> bp)
{
    Must(proxyingVb == opOn);
    Must(theMaster);
    theMaster->noteVbContentDone(false);
    proxyingVb = opComplete;
}

void
Adaptation::Ecap::XactionRep::noteInitiatorAborted()
{
    mustStop("initiator aborted");
