void
Adaptation::Ecap::XactionRep::noteBodyProductionEnded(RefCount<BodyPipe> bp)
{
    Must(makingVb == opOn); // or we would not be registered as a consumer
    Must(theMaster);
    theMaster->noteVbContentDone(true);
    vbProductionFinished = true;
}