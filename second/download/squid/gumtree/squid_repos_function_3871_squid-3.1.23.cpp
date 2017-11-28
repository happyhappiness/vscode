void
Adaptation::Ecap::XactionRep::noteBodyProducerAborted(RefCount<BodyPipe> bp)
{
    Must(proxyingVb == opOn);
    Must(theMaster);
    theMaster->noteVbContentDone(false);
    proxyingVb = opComplete;
}