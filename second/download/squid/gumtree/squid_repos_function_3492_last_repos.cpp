void
Adaptation::Ecap::XactionRep::noteBodyProducerAborted(RefCount<BodyPipe> bp)
{
    Must(makingVb == opOn); // or we would not be registered as a consumer
    Must(theMaster);
    theMaster->noteVbContentDone(false);
    vbProductionFinished = true;
}