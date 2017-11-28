Adaptation::Ecap::XactionRep::adaptationAborted()
{
    tellQueryAborted(true); // should eCAP support retries?
    mustStop("adaptationAborted");
}

void
Adaptation::Ecap::XactionRep::noteMoreBodySpaceAvailable(RefCount<BodyPipe> bp)
{
    Must(proxyingAb == opOn);
    moveAbContent();
}
