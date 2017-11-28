    proxyingAb = opComplete;
}

void
Adaptation::Ecap::XactionRep::noteMoreBodyDataAvailable(RefCount<BodyPipe> bp)
{
    Must(makingVb == opOn); // or we would not be registered as a consumer
    Must(theMaster);
    theMaster->noteVbContentAvailable();
}

void
Adaptation::Ecap::XactionRep::noteBodyProductionEnded(RefCount<BodyPipe> bp)
{
    Must(makingVb == opOn); // or we would not be registered as a consumer
    Must(theMaster);
    theMaster->noteVbContentDone(true);
    vbProductionFinished = true;
}

void
Adaptation::Ecap::XactionRep::noteBodyProducerAborted(RefCount<BodyPipe> bp)
{
    Must(makingVb == opOn); // or we would not be registered as a consumer
    Must(theMaster);
    theMaster->noteVbContentDone(false);
    vbProductionFinished = true;
}

void
Adaptation::Ecap::XactionRep::noteInitiatorAborted()
{
    mustStop("initiator aborted");
