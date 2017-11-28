void
Adaptation::Ecap::XactionRep::noteBodyConsumerAborted(RefCount<BodyPipe> bp)
{
    Must(proxyingAb == opOn);
    stopProducingFor(answer().body_pipe, false);
    Must(theMaster);
    theMaster->abStopMaking();
    proxyingAb = opComplete;
}