void
Adaptation::Ecap::XactionRep::noteMoreBodyDataAvailable(RefCount<BodyPipe> bp)
{
    Must(proxyingVb == opOn);
    Must(theMaster);
    theMaster->noteVbContentAvailable();
}